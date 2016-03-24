#ifndef INTERPRETACIONTONO
#define INTERPRETACIONTONO


/*
 * Encuentra los dos valores de mayor magnitud de un arreglo
 */


void large (float* in, float* array, int* index); 

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

bool Umbral (float* in, float umbral);
/*
 * Prueba de Twist:
 *
 * Twist es la diferencia en dB entre los tonos de alta y baja frecuencia.
 * Tı́picamente el tono de mayor frecuencia es recibido a menor potencia ya que experimenta
 *  una mayor pérdida en el cable. Se puede compensar esta diferencia en la pérdida al
 * transmitir.
 *
*/

bool Twist (int* in);

/*
 * Prueba de Offset:
 *
 * Se realiza para evitar que ruidos de banda ancha sean detectados como
 * tonos. Se basa en la premisa que los niveles de potencia de los 2 tonos debe ser mucho
 * mayor al resto. Se verifica que la diferencia de potencias supere un umbral pre-establecido,
 * entre las frecuencias del mismo grupo (alta o baja frecuencia).
 *
*/

bool Offset (float* in, int* index, float umbralbajo, float umbralalto);

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

bool EnergiaTotal (float* in, float cb, float ca, float cs);

/*
 * Prueba de la 2 da armónica: 
 *
 * La segunda armónica de los tonos DTMF está incluida
 * en el espectro de voz y puede ser detectada por el algortimo de Goertzel. Esta detección
 * puede ser utilizada para discriminar tonos válidos de voz, ya que a diferencia de los tonos
 * senoidales ”puros”, la voz tiene significativa energı́a armónica.
 *
*/

bool Armonicas (float* Goertzel, float* segundaArmonica);

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

char Decoder (int* index);

#endif // INTERPRETACIONTONO





