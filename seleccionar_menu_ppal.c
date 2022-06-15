#include <alcd.h>
#include <inttypes.h>
#include <io.h>
#include "typedefs.h"
#include "extern.h"

extern unsigned char seleccion=0;

estado_t seleccionar_menu_ppal(menu_t *menu, unsigned char *pin){
    unsigned int tiempo_der=0;
    unsigned int tiempo_izq=0;

    unsigned char izq=0;
    unsigned char der=0;



    while(!boton && tiempo < TIEMPO_CORTE){//LEER EL ENCODER
        
		
		if ((*pin)&0x04){//pin.2
			if ((*pin)&0x10)//pin.4
                tiempo_izq=tiempo;
            else
                tiempo_der=tiempo;

        }

        if (tiempo_izq && tiempo_der){//por lo menos tiene 2 lecturas
            if (tiempo_izq > tiempo_der){
                izq++;
                if (izq > FILTRO_ENCODER){
                    seleccion--;
                    lcd_gotoxy (18,(seleccion+1)%4);//posicion anterior
                    lcd_puts(" ");
                    lcd_gotoxy (18,seleccion%4);
                    lcd_puts("*");
                    izq=0;//reinicializo
                }
            }
            else if (tiempo_izq < tiempo_der){
                der++;
                if (der > FILTRO_ENCODER){
                    seleccion++;
                    lcd_gotoxy (18,(seleccion-1)%4);//en vez de 4 deberia ir macro num heladera
                    lcd_puts(" ");
                    lcd_gotoxy (18,seleccion%4);
                    lcd_puts("*");
                    der=0;
                }
            }
            tiempo_izq=0;
            tiempo_der=0;
            tiempo=0;
        }
    }

    if (boton){
        switch (seleccion%4){
            case 0:
                *menu=MENU_HELADERA_1;
                seleccion=0;
            break;

            case 1:
                *menu=MENU_HELADERA_2;
                seleccion=0;
            break;

            case 2:
                *menu=MENU_HELADERA_3;
                seleccion=0;
            break;

            default:
                *menu=MENU_HELADERA_4;
                seleccion=0;
            break;
        }
        boton=0;
    }

    encoder=0;

    return OK;
}