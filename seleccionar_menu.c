#include <alcd.h>
#include <stdio.h>

#include "typedefs.h"
#include "extern.h"

extern unsigned char seleccion;

estado_t seleccionar_temp (int *temp,  unsigned char *port, unsigned char linea);

estado_t seleccionar_menu(menu_t *menu, int heladera[3], const unsigned char *p){
    unsigned int t_der=0;
    unsigned int t_izq=0;

    unsigned char izq=0;
    unsigned char der=0;



    while(!boton && tiempo < TIEMPO_CORTE){//LEER EL ENCODER
        
        if ((*p)&0x04){//pin.2
            if ((*p)&0x10)//pin.4
                t_izq=tiempo;
            else
                t_der=tiempo;
        }

        if (t_izq && t_der){//por lo menos tiene 2 lecturas
            if (t_izq > t_der){
                izq++;
                if (izq > FILTRO_ENCODER){
                    seleccion--;
                    lcd_gotoxy (14,(seleccion+1)%4);//posicion anterior
                    lcd_puts(" ");
                    lcd_gotoxy (14,seleccion%4);
                    lcd_puts("*");
                    izq=0;//reinicializo
                }
            }
            else if (t_izq < t_der){
                der++;
                if (der > FILTRO_ENCODER){
                    seleccion++;
                    lcd_gotoxy (14,(seleccion-1)%4);
                    lcd_puts(" ");
                    lcd_gotoxy (14,seleccion%4);
                    lcd_puts("*");
                    der=0;
                }

            }
        t_der=0;
        t_izq=0;
        tiempo=0;
        }
    }

    if (boton){
        switch (seleccion%4){
            case 0:
                *menu=MENU_PRINCIPAL;
            break;

            case 2:

                while(!boton && tiempo < TIEMPO_CORTE){//LEER EL ENCODER
                    seleccionar_temp(&heladera [TEMP_MAX],p, seleccion%4);
                }

            break;

            case 3:

                while(!boton && tiempo < TIEMPO_CORTE){//LEER EL ENCODER
                    seleccionar_temp(&heladera [TEMP_MIN] ,p, seleccion%4);
                }
            break;

            default:

                lcd_gotoxy(0,0);
                lcd_puts("1 volver 3 Tmax 4 Tmin");
            break;
        }
        boton=0;
    }
    encoder=0;
    return OK;
}
	//extern unsigned int t_der =0;
    //extern unsigned int t_izq =0;

    //extern unsigned char izq =0;
    //extern unsigned char der =0;

//para evitar lecturas erroneas, las filtro con FILTRO_ENCODER

estado_t seleccionar_temp (int *temp, unsigned char *port, unsigned char linea){
    char temp_selec[20];

    extern unsigned int t_der;
    extern unsigned int t_izq;

    extern unsigned char izq;
    extern unsigned char der;

    if ((*port)&0x04){
        if ((*port)&0x10)
            t_izq=tiempo;
        else
            t_der=tiempo;
    }

    if (t_izq && t_der){	
        if (t_izq > t_der){
            izq++;
            if (izq > FILTRO_ENCODER){
                (*temp)--;
                lcd_gotoxy(15,linea);
                sprintf(temp_selec,"%3i", *temp);
                lcd_puts(temp_selec);
                izq=0;//reinicializo
            }
        }
        else if (t_izq < t_der){
            der++;
            if (der > FILTRO_ENCODER){
                (*temp)++;
                lcd_gotoxy(15,linea);
                sprintf(temp_selec,"%3i", *temp);
                lcd_puts(temp_selec);
                der=0;
            }
        }
    t_der=0;
    t_izq=0;
    tiempo=0;
    }
    return OK;
}



