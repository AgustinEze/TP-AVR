#include <ds18b20.h>
#include "typedefs.h"
#include "extern.h"

estado_t verificar_sensores (int hela[MAX_HELADERAS][3], unsigned char ds1820[MAX_DS1820][9], unsigned char *port){
	
	#asm("cli")//DESABILITAR PARA LEER 1WIRE
    hela [HELA_1][TEMP_ACTUAL]= ds18b20_temperature(&ds1820[HELA_1][0]);    //LEER SENSOR 1
    hela [HELA_2][TEMP_ACTUAL]= ds18b20_temperature(&ds1820[HELA_2][0]);    //LEER SENSOR 2
    hela [HELA_3][TEMP_ACTUAL]= ds18b20_temperature(&ds1820[HELA_3][0]);    //LEER SENSOR 3
    hela [HELA_4][TEMP_ACTUAL]= ds18b20_temperature(&ds1820[HELA_4][0]);    //LEER SENSOR 4
    #asm("sei")//INTERRUPCIONES HABILITADAS
	
    if (hela [HELA_1][TEMP_ACTUAL] > hela [HELA_1][TEMP_MAX]) (*port)|=0x02;//port.1=1;
    if (hela [HELA_2][TEMP_ACTUAL] > hela [HELA_2][TEMP_MAX]) (*port)|=0x04;//port.2=1;
    if (hela [HELA_3][TEMP_ACTUAL] > hela [HELA_3][TEMP_MAX]) (*port)|=0x08;//port.3=1;
    if (hela [HELA_4][TEMP_ACTUAL] > hela [HELA_4][TEMP_MAX]) (*port)|=0x10;//port.4=1;

    if (hela [HELA_1][TEMP_ACTUAL] < hela [HELA_1][TEMP_MIN]) (*port)&=~(0x02);//port.1=0;
    if (hela [HELA_2][TEMP_ACTUAL] < hela [HELA_2][TEMP_MIN]) (*port)&=~(0x04);//port.2=0;
    if (hela [HELA_3][TEMP_ACTUAL] < hela [HELA_3][TEMP_MIN]) (*port)&=~(0x08);//port.3=0;
    if (hela [HELA_4][TEMP_ACTUAL] < hela [HELA_4][TEMP_MIN]) (*port)&=~(0x10);//port.4=0;
    tiempo=0; //reinicializo el contador

    return OK;
}