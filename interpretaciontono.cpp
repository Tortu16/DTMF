#include "interpretaciontono.h"
#include <cmath>
#include <iostream>


/*
 * Encuentra los dos valores de mayor magnitud en un array
 */


void large (float* in, float* array, int* index)
{

for (int i = 0; i < 8; i++)
  {
    if (in[i] > array[0])
    {
        array[1] = array[0];
        index[1] = index[0];
        array[0] = in[i];
        index[0] = i;
    }
    else if (in[i] > array[1])
    {
        array[1] = in[i];
        index[1] = i;
    }
  }
}

/*
 * Encuentra los dos valores de mayor magnitud en las frecuencias bajas y en las altas por separado
 */


void large2 (float* in, float* array, int* index)
{

for (int i = 0; i < 4; i++)
  {
    if (in[i] > array[0])
    {
        array[0] = in[i];
        index[0] = i;
    }
  }
for (int i = 4; i < 8; i++)
  {
    if (in[i] > array[1])
    {
        array[1] = in[i];
        index[1] = i;
    }
  }
}

/*
 *
 * Prueba de magnitud:
 *
 * Según ITU (International Telecommunication Union) el nivel
 * máximo de señal por ser transmitido a una red pública es −9 ≤ 1 dBm. Esto se traduce
 * en que el receptor DTMF debe trabajar en el rango de −29 a +1 dBm. Un tono cuyo
 * magnitud |X(k)| 2 sea menor a −29 dBm debe ser ignorado.
 *
*/

bool Umbral (float* in, float umbral){
    return (in[0] > umbral && in [1] > umbral);
}

/*
 * Prueba de Twist:
 *
 * Twist es la diferencia en dB entre los tonos de alta y baja frecuencia.
 * Tı́picamente el tono de mayor frecuencia es recibido a menor potencia ya que experimenta
 *  una mayor pérdida en el cable. Se puede compensar esta diferencia en la pérdida al
 * transmitir.
 *
 * La especificación Bellcore indica un Twist aceptable de -8 a 4 dB. Se toma como referencia
 * la potencia de la frecuencia baja y se calcula el dB de la alta: 0.15 para -8 y 2.5 para 4 dB.
 *
*/

bool Twist (float* in)
{
    float ratio = 0;
    ratio = in[1]/in[0];
    if (ratio > 0.15 && ratio < 2.5) return true;
    else return false;
}

/*
 * Prueba de Offset:
 *
 * Se realiza para evitar que ruidos de banda ancha sean detectados como
 * tonos. Se basa en la premisa que los niveles de potencia de los 2 tonos debe ser mucho
 * mayor al resto. Se verifica que la diferencia de potencias supere un umbral pre-establecido,
 * entre las frecuencias del mismo grupo (alta o baja frecuencia).
 *
*/

bool Offset (float* in, int* index, float umbralbajo, float umbralalto){
    for (int i = 0; i < 4; i++){
        if (i != index[0] && in[i] > in[index[0]]*umbralbajo) return false;

    }
    for (int i = 4; i < 8; i++){
        if (i != index[1] && in[i] > in[index[1]]*umbralalto) return false;
    }
    return true;
}


/*
 * Prueba de la Energia Total:
 *
 * Está prueba pretende dar robustez a la detección, incluso
 * ante la presencia de voz. El principio es el siguiente:
 * Se asigna un coeficiente para el tono de baja frecuencia cb , un coeficiente para el tono
 * de alta frecuencia ca y un coeficiente para la suma cs
 * Se calcula la energia total de los 8 tonos: Suma = |X(k)|^2, k=0,1,2,...8
 * Cada uno de las energı́as por separado con los pesos pre-seleccionados, debe ser mayor
 * a la suma total de energia.
 *
 * Esta prueba tiene la siguiente limitacion:
 * La ponderacion falla si el coeficiente es 0
 *
*/

bool EnergiaTotal (float* in, float cb, float ca, float cs){
    float suma = 0;
    for (int i = 0; i < 8; i++){
        suma = suma + in[i];        // Calcula la suma de todas las energias: La energia total.
    }
    suma = suma * cs;               // Pondera la energia total con el coeficiente indicado.
    for (int i = 0; i < 4; i++){
        if ( cb * in[i] < suma) {
            return false;
        }
    }
    for (int i = 4; i < 8; i++){
        if ( ca * in [i] < suma) {
            return false;
        }
    }
    return true;
}


/*
 * Prueba de la 2 da armónica: 
 *
 * La segunda armónica de los tonos DTMF está incluida
 * en el espectro de voz y puede ser detectada por el algortimo de Goertzel. Esta detección
 * puede ser utilizada para discriminar tonos válidos de voz, ya que a diferencia de los tonos
 * senoidales ”puros”, la voz tiene significativa energı́a armónica.
 *
*/

bool Armonicas (float* Goertzel, float* segundaArmonica){
    for (int i = 0; i < 2; i++){
        if (segundaArmonica[i] > 0.5*(Goertzel[i]+1)) return false;
    }
    return true;
}


/*
 * Decodificador del digito:
 *
 * Una vez pasadas las 5 pruebas anteriores, un digito es
 * decodificado para el instante m a partir del tono de fila R (Row) y columna C (Column):
 * D(m) = C + 4(R − 1). Para una detección exitosa, el tono se valida 2 veces con la
 * intensión de disminuir la susceptibilidad al ruido y la voz. Además debe de existir lógica
 * adicional para no retornar un dı́gito con cada detección exitosa, que puede deberse a varias
 * detecciones ocurridas en el mismo periodo de transmisión de un código.
 *
*/

char Decoder (int* index){
    if (index[0] > 3 || index[1] < 4) return '\0';
    char LUT[16] {'1','2','3','A','4','5','6','B','7','8','9','C','*','0','#','D'};
    return LUT[4*index[0]+index[1]-4];
}
