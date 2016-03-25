/** @file thru_client.c
 *
 * @brief This simple through client demonstrates the basic features of JACK
 * as they would be used by many applications.
 */

#include <stdio.h>
#include <errno.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <signal.h>
#ifndef WIN32
#include <unistd.h>
#endif
#include <jack/jack.h>
#include <iomanip>
#include <iostream>

#include "Goertzel.h"
#include "interpretaciontono.h"

using namespace std;

jack_port_t **input_ports;
jack_port_t *output_port1, *output_port2;
jack_port_t **output_ports;
jack_client_t *client;



#ifndef M_PI
#define M_PI  (3.14159265)
#endif

#define TABLE_SIZE   (1024)


float sine[TABLE_SIZE];

typedef struct
{
    float sine[TABLE_SIZE];
    int left_phase;
    int right_phase;
}
paTestData;

static void signal_handler ( int sig )
{
    jack_client_close ( client );
    fprintf ( stderr, "signal received, exiting ...\n" );
    exit ( 0 );
}

/**
 * The process callback for this JACK application is called in a
 * special realtime thread once for each audio cycle.
 *
 * This client follows a simple rule: when the JACK transport is
 * running, copy the input port to the output.  When it stops, exit.
 */

int
process ( jack_nframes_t nframes, void *arg )
{
    int i;
    jack_default_audio_sample_t *in, *out;
    float GCoeffArray[8] = {0,0,0,0,0,0,0,0};
    float ToneFreq [8] = {697, 770, 852, 941, 1209, 1336, 1477, 1633};

    float toneCoeff [2] = {0,0};
    int index [2] = {0,0};

    bool Umbral_, Twist_, Offset_, EnergiaTotal_ = false;


//printf ("# of frames: %d\n", nframes);


    for ( i = 0; i < 2; i++ )
    {
      in = jack_port_get_buffer ( input_ports[i], nframes );
      out = jack_port_get_buffer ( output_ports[i], nframes );

      // Aqui se analiza el audio de entrada

      for (i = 0; i < 8; i++ )
      {
          GCoeffArray[i] = toneDetectionFunction (in,ToneFreq [i],44100);
      }
      
      
      large2 (GCoeffArray, toneCoeff, index);
      Umbral_ = Umbral(toneCoeff,10);
      Twist_ = Twist (index);
      Offset_ = Offset (toneCoeff,index,7,7);
      EnergiaTotal_ = EnergiaTotal (GCoeffArray,8000,8000,0.125);

      cout<<"\r"<<Umbral_<<" "<<Twist_<<" "<<Offset_<<" "<<toneCoeff[0] <<" "<<toneCoeff[1]<<" "<<EnergiaTotal_<<" "<< GCoeffArray[0] <<" "<< GCoeffArray[1] <<" "<< GCoeffArray[2] <<" "<< GCoeffArray[3] <<" "<< GCoeffArray[4] <<" "<< GCoeffArray[5] <<" "<< GCoeffArray[6] <<" "<< GCoeffArray[7] <<" "<<flush;
     //if (Umbral(toneCoeff,20) && Offset (toneCoeff,index,40,40) && EnergiaTotal (GCoeffArray,40000,40000,0.125)) cout<<"\r"<<Decoder(index)<<"	"<<toneCoeff[0]<<" "<<toneCoeff[1]<<flush;
      
//Umbral(toneCoeff,10) && Twist (index) && Offset (toneCoeff,index,0.1,0.1) && EnergiaTotal (GCoeffArray,400,400,0.125)
      //cout<<"\r"<<toneCoeff[0]<<" "<<toneCoeff[1]<<flush;

      // Aqui se termina el analisis de audio de entrada

      for( i=0; i<nframes; i++ )
	{

                in[i] = in[i];	//aqui se modifica el buffer de entrada

	}
  
        memcpy ( out, in, nframes * sizeof ( jack_default_audio_sample_t ) ); // se copia el buffer de entrada modificado a la salida
    }
    return 0;
}




/**
 * JACK calls this shutdown_callback if the server ever shuts down or
 * decides to disconnect the client.
 */
void
jack_shutdown ( void *arg )
{
    free ( input_ports );
    free ( output_ports );
    exit ( 1 );
}


int
main ( int argc, char *argv[] )
{
    int i;
    const char **ports;
    const char *client_name;
    const char *server_name = NULL;
    jack_options_t options = JackNullOption;
    jack_status_t status;
	paTestData data;

    
    //toneDetection Power; /* Define a tone Detection object*/

    if ( argc >= 2 )        /* client name specified? */
    {
        client_name = argv[1];
        if ( argc >= 3 )    /* server name specified? */
        {
            server_name = argv[2];
            options |= JackServerName;
        }
    }
    else              /* use basename of argv[0] */
    {
        client_name = strrchr ( argv[0], '/' );
        if ( client_name == 0 )
        {
            client_name = argv[0];
        }
        else
        {
            client_name++;
        }
    }





//Create Sine table
for( i=0; i<TABLE_SIZE; i++ )
    {
        sine[i] = (float) sin( ((double)i/(double)TABLE_SIZE) * M_PI * 2. );
	//printf ("# of frames: %f\n",sine[i]);
    }



    /* open a client connection to the JACK server */

    client = jack_client_open ( client_name, options, &status, server_name );
    if ( client == NULL )
    {
        fprintf ( stderr, "jack_client_open() failed, "
                  "status = 0x%2.0x\n", status );
        if ( status & JackServerFailed )
        {
            fprintf ( stderr, "Unable to connect to JACK server\n" );
        }
        exit ( 1 );
    }
    if ( status & JackServerStarted )
    {
        fprintf ( stderr, "JACK server started\n" );
    }
    if ( status & JackNameNotUnique )
    {
        client_name = jack_get_client_name ( client );
        fprintf ( stderr, "unique name `%s' assigned\n", client_name );
    }

    /* tell the JACK server to call `process()' whenever
       there is work to be done.
    */

    jack_set_process_callback ( client, process, 0 );

    /* tell the JACK server to call `jack_shutdown()' if
       it ever shuts down, either entirely, or if it
       just decides to stop calling us.
    */

    jack_on_shutdown ( client, jack_shutdown, 0 );

    /* create two ports pairs*/
    input_ports = ( jack_port_t** ) calloc ( 2, sizeof ( jack_port_t* ) );
    output_ports = ( jack_port_t** ) calloc ( 2, sizeof ( jack_port_t* ) );

    char port_name[16];
    for ( i = 0; i < 2; i++ )
    {
        sprintf ( port_name, "input_%d", i + 1 );
        input_ports[i] = jack_port_register ( client, port_name, JACK_DEFAULT_AUDIO_TYPE, JackPortIsInput, 0 );
        sprintf ( port_name, "output_%d", i + 1 );
        output_ports[i] = jack_port_register ( client, port_name, JACK_DEFAULT_AUDIO_TYPE, JackPortIsOutput, 0 );
        if ( ( input_ports[i] == NULL ) || ( output_ports[i] == NULL ) )
        {
            fprintf ( stderr, "no more JACK ports available\n" );
            exit ( 1 );
        }
    }

    /* Tell the JACK server that we are ready to roll.  Our
     * process() callback will start running now. */

    if ( jack_activate ( client ) )
    {
        fprintf ( stderr, "cannot activate client" );
        exit ( 1 );
    }

    /* Connect the ports.  You can't do this before the client is
     * activated, because we can't make connections to clients
     * that aren't running.  Note the confusing (but necessary)
     * orientation of the driver backend ports: playback ports are
     * "input" to the backend, and capture ports are "output" from
     * it.
     */

    ports = jack_get_ports ( client, NULL, NULL, JackPortIsPhysical|JackPortIsOutput );
    if ( ports == NULL )
    {
        fprintf ( stderr, "no physical capture ports\n" );
        exit ( 1 );
    }

    for ( i = 0; i < 2; i++ )
        if ( jack_connect ( client, ports[i], jack_port_name ( input_ports[i] ) ) )
            fprintf ( stderr, "cannot connect input ports\n" );

    free ( ports );

    ports = jack_get_ports ( client, NULL, NULL, JackPortIsPhysical|JackPortIsInput );
    if ( ports == NULL )
    {
        fprintf ( stderr, "no physical playback ports\n" );
        exit ( 1 );
    }

    for ( i = 0; i < 2; i++ )
        if ( jack_connect ( client, jack_port_name ( output_ports[i] ), ports[i] ) )
            fprintf ( stderr, "cannot connect input ports\n" );

    free ( ports );

    /* install a signal handler to properly quits jack client */
#ifdef WIN32
    signal ( SIGINT, signal_handler );
    signal ( SIGABRT, signal_handler );
    signal ( SIGTERM, signal_handler );
#else
    signal ( SIGQUIT, signal_handler );
    signal ( SIGTERM, signal_handler );
    signal ( SIGHUP, signal_handler );
    signal ( SIGINT, signal_handler );
#endif

    /* keep running until the transport stops */

    while (1)
    {
#ifdef WIN32
        Sleep ( 1000 );
#else
        sleep ( 1 );
#endif
    }

    jack_client_close ( client );
    exit ( 0 );
}
