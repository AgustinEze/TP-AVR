#include <alcd.h>
#include <stdio.h>

#include "typedefs.h"

estado_t menu_heladera (int hela[3]){
    char temp[20];

    lcd_gotoxy(0,1);
    lcd_puts(MENSAJE_TEMP_ACTUAL);  //"TEMP ACTUAL        C"
    lcd_gotoxy(15,1);
    sprintf(temp,"%3i", hela[TEMP_ACTUAL]);
    lcd_puts(temp);

    lcd_gotoxy(0,2);
    lcd_puts(MENSAJE_TEMP_MAX);     //"TEMP MAX           C"
    lcd_gotoxy(15,2);
    sprintf(temp,"%3i", hela[TEMP_MAX]);
    lcd_puts(temp);

    lcd_gotoxy(0,3);
    lcd_puts(MENSAJE_TEMP_MIN);     //"TEMP MIN           C"
    lcd_gotoxy(15,3);
    sprintf(temp,"%3i", hela[TEMP_MIN]);
    lcd_puts(temp);

    return OK;
}