#ifndef PROTOTIPOS_H
    #define PROTOTIPOS_H
	#include <inttypes.h>
	
    estado_t verificar_sensores (int [MAX_HELADERAS][3], unsigned char [MAX_DS1820][9], unsigned char *);
    estado_t seleccionar_menu_ppal(menu_t *, volatile uint8_t *);
    estado_t menu_heladera (int [3]);
    estado_t seleccionar_menu(menu_t *, int [3], const unsigned char *);

#endif
