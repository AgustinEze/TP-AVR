#ifndef TYPEDEFS_H
    #define TYPEDEFS_H

	#define MAX_DS1820 4            // maximum number of DS1820 devices connected to the 1 Wire bus
    

    #define MAX_HELADERAS   4

    #define HELA_1          0
    #define HELA_2          1
    #define HELA_3          2
    #define HELA_4          3
	
	#define T_MAX_DEFAULT 8	
	#define T_MIN_DEFAULT 0

	
    #define TEMP_ACTUAL     0
    #define TEMP_MAX        1
    #define TEMP_MIN        2

    #define TIEMPO_CORTE    7500
    #define TIEMPO_LECTURA  15000

    #define FILTRO_ENCODER  2

    #define MENSAJE_HELADERA_1      "HELADERA 1       [ ]"
    #define MENSAJE_HELADERA_2      "HELADERA 2       [ ]"
    #define MENSAJE_HELADERA_3      "HELADERA 3       [ ]"
    #define MENSAJE_HELADERA_4      "HELADERA 4       [ ]"

    #define MENSAJE_MENU_HELADERA   "VOLVER              "

    #define MENSAJE_TEMP_ACTUAL     "TEMP ACTUAL        C"
    #define MENSAJE_TEMP_MAX        "TEMP MAX           C"
    #define MENSAJE_TEMP_MIN        "TEMP MIN           C"

	typedef enum{
        MENU_PRINCIPAL=99,
        MENU_HELADERA_1=0,
        MENU_HELADERA_2,
        MENU_HELADERA_3,
        MENU_HELADERA_4,
        MENU_TEMP_MAX,
        MENU_TEMP_MIN
    }menu_t;

    typedef enum{
        OK,

        ERROR_
    }estado_t;

#endif
