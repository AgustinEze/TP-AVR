/*******************************************************
This program was created by the CodeWizardAVR V3.28
Automatic Program Generator
© Copyright 1998-2016 Pavel Haiduc, HP InfoTech s.r.l.
http://www.hpinfotech.com

Project : TP
Version : 1.0
Date    : 03/11/2016
Author  : Seba&Agus
Company :
Comments:


Chip type               : ATmega328
Program type            : Application
AVR Core Clock frequency: 8,000000 MHz
Memory model            : Small
External RAM size       : 0
Data Stack size         : 512
*******************************************************/

#include <io.h>

#include <stdio.h>
#include <1wire.h>              // 1 Wire Bus interface functions
#include <ds18b20.h>             // DS1820 Temperature Sensor functions>
#include <alcd.h>               // Alphanumeric LCD functions
#include "typedefs.h"
#include "prototipos.h"


bit encoder = 0;
bit boton=0;
unsigned int tiempo = 0;

interrupt [EXT_INT0] void ext_int0_isr(void){
        encoder = 1;
}

interrupt [EXT_INT1] void ext_int1_isr(void){
        boton = 1;
}


interrupt [TIM0_OVF] void timer0_ovf_isr(void){
    TCNT0=0x06;
    tiempo++;
}

void main(void){
    int heladeras [MAX_HELADERAS][3];    //Temp Actual, Tmax, Tmin
    unsigned char seleccion=0;
    unsigned char ds18b20_rom_codes[MAX_DS1820][9];  // DS1820 devices ROM code storage area, 9 bits for each one
    menu_t menu = MENU_PRINCIPAL;

    #pragma optsize-
    CLKPR=(1<<CLKPCE);
    CLKPR=(0<<CLKPCE) | (0<<CLKPS3) | (0<<CLKPS2) | (0<<CLKPS1) | (0<<CLKPS0);
    #ifdef _OPTIMIZE_SIZE_
    #pragma optsize+
    #endif

    DDRB=(1<<DDB7) | (1<<DDB6) | (1<<DDB5) | (1<<DDB4) | (1<<DDB3) | (1<<DDB2) | (1<<DDB1) | (1<<DDB0);
    PORTB=(0<<PORTB7) | (0<<PORTB6) | (0<<PORTB5) | (0<<PORTB4) | (0<<PORTB3) | (0<<PORTB2) | (0<<PORTB1) | (0<<PORTB0);

    DDRC=(1<<DDC6) | (1<<DDC5) | (1<<DDC4) | (1<<DDC3) | (1<<DDC2) | (1<<DDC1) | (1<<DDC0);
    PORTC=(0<<PORTC6) | (0<<PORTC5) | (0<<PORTC4) | (0<<PORTC3) | (0<<PORTC2) | (0<<PORTC1) | (0<<PORTC0);

    DDRD=(1<<DDD7) | (1<<DDD6) | (1<<DDD5) | (0<<DDD4) | (0<<DDD3) | (0<<DDD2) | (1<<DDD1) | (1<<DDD0);
    PORTD=(0<<PORTD7) | (0<<PORTD6) | (0<<PORTD5) | (0<<PORTD4) | (0<<PORTD3) | (0<<PORTD2) | (0<<PORTD1) | (0<<PORTD0);

    // Timer 0, 8 ms
    TCCR0A=(0<<COM0A1) | (0<<COM0A0) | (0<<COM0B1) | (0<<COM0B0) | (0<<WGM01) | (0<<WGM00);
    TCCR0B=(0<<WGM02) | (1<<CS02) | (0<<CS01) | (0<<CS00);
    TCNT0=0x06;
    OCR0A=0x00;
    OCR0B=0x00;

    TCCR1A=(0<<COM1A1) | (0<<COM1A0) | (0<<COM1B1) | (0<<COM1B0) | (0<<WGM11) | (0<<WGM10);
    TCCR1B=(0<<ICNC1) | (0<<ICES1) | (0<<WGM13) | (0<<WGM12) | (0<<CS12) | (0<<CS11) | (0<<CS10);
    TCNT1H=0x00;
    TCNT1L=0x00;
    ICR1H=0x00;
    ICR1L=0x00;
    OCR1AH=0x00;
    OCR1AL=0x00;
    OCR1BH=0x00;
    OCR1BL=0x00;

    ASSR=(0<<EXCLK) | (0<<AS2);
    TCCR2A=(0<<COM2A1) | (0<<COM2A0) | (0<<COM2B1) | (0<<COM2B0) | (0<<WGM21) | (0<<WGM20);
    TCCR2B=(0<<WGM22) | (0<<CS22) | (0<<CS21) | (0<<CS20);
    TCNT2=0x00;
    OCR2A=0x00;
    OCR2B=0x00;


    TIMSK0=(0<<OCIE0B) | (0<<OCIE0A) | (1<<TOIE0);      // Timer 0 Interrupt
    TIMSK1=(0<<ICIE1) | (0<<OCIE1B) | (0<<OCIE1A) | (0<<TOIE1);
    TIMSK2=(0<<OCIE2B) | (0<<OCIE2A) | (0<<TOIE2);

    // External Interrupt INT0 & INT1  : On
    EICRA=(0<<ISC11) | (1<<ISC10) | (0<<ISC01) | (1<<ISC00);
    EIMSK=(1<<INT1) | (1<<INT0);
    EIFR=(1<<INTF1) | (1<<INTF0);
    PCICR=(0<<PCIE2) | (0<<PCIE1) | (0<<PCIE0);

    UCSR0B=(0<<RXCIE0) | (0<<TXCIE0) | (0<<UDRIE0) | (0<<RXEN0) | (0<<TXEN0) | (0<<UCSZ02) | (0<<RXB80) | (0<<TXB80);

    // Analog Comparator: Off
    ACSR=(1<<ACD) | (0<<ACBG) | (0<<ACO) | (0<<ACI) | (0<<ACIE) | (0<<ACIC) | (0<<ACIS1) | (0<<ACIS0);
    ADCSRB=(0<<ACME);
    DIDR1=(0<<AIN0D) | (0<<AIN1D);

    // ADC disabled
    ADCSRA=(0<<ADEN) | (0<<ADSC) | (0<<ADATE) | (0<<ADIF) | (0<<ADIE) | (0<<ADPS2) | (0<<ADPS1) | (0<<ADPS0);

    // SPI disabled
    SPCR=(0<<SPIE) | (0<<SPE) | (0<<DORD) | (0<<MSTR) | (0<<CPOL) | (0<<CPHA) | (0<<SPR1) | (0<<SPR0);

    // TWI disabled
    TWCR=(0<<TWEA) | (0<<TWSTA) | (0<<TWSTO) | (0<<TWEN) | (0<<TWIE);

    // LCD characters/line: 20
    lcd_init(20);

    // 1 Wire Bus initialization
    // 1 Wire Data port: PORTB
    // 1 Wire Data bit: 0
    // Note: 1 Wire port settings are specified in the
    // Project|Configure|C Compiler|Libraries|1 Wire menu.
    w1_init();
    
    w1_search(0xf0,ds18b20_rom_codes);


    //Cargo los valores por defecto de las variables
    
    heladeras [HELA_1][TEMP_ACTUAL]= ds18b20_temperature(&ds18b20_rom_codes[HELA_1][0]); //LEER SENSOR 1
    heladeras [HELA_2][TEMP_ACTUAL]= ds18b20_temperature(&ds18b20_rom_codes[HELA_2][0]); //LEER SENSOR 2
    heladeras [HELA_3][TEMP_ACTUAL]= ds18b20_temperature(&ds18b20_rom_codes[HELA_3][0]); //LEER SENSOR 3
    heladeras [HELA_4][TEMP_ACTUAL]= ds18b20_temperature(&ds18b20_rom_codes[HELA_4][0]); //LEER SENSOR 4
    
    heladeras [HELA_1][TEMP_MAX]=T_MAX_DEFAULT;
    heladeras [HELA_2][TEMP_MAX]=T_MAX_DEFAULT;
    heladeras [HELA_3][TEMP_MAX]=T_MAX_DEFAULT;
    heladeras [HELA_4][TEMP_MAX]=T_MAX_DEFAULT;

    heladeras [HELA_1][TEMP_MIN]=T_MIN_DEFAULT;
    heladeras [HELA_2][TEMP_MIN]=T_MIN_DEFAULT;
    heladeras [HELA_3][TEMP_MIN]=T_MIN_DEFAULT;
    heladeras [HELA_4][TEMP_MIN]=T_MIN_DEFAULT;

    // Globally enable interrupts

    #asm("sei")//DESHABILITAR PARA LEER 1WIRE


    while (1){
        switch (menu){
            case MENU_PRINCIPAL:
                if(tiempo > TIEMPO_LECTURA){//LEE CADA 2 MINS
                   verificar_sensores(heladeras, ds18b20_rom_codes, &PORTC);
                }

                lcd_gotoxy(0,0);
                lcd_puts (MENSAJE_HELADERA_1);
                lcd_gotoxy(18,0);
                lcd_puts("*");
                lcd_gotoxy(0,1);
                lcd_puts (MENSAJE_HELADERA_2);
                lcd_gotoxy(0,2);
                lcd_puts (MENSAJE_HELADERA_3);
                lcd_gotoxy(0,3);
                lcd_puts (MENSAJE_HELADERA_4);
                         //lectura encoder
                if(encoder){
                   seleccionar_menu_ppal (&menu, &PIND);
                }
				
            break;

            case MENU_HELADERA_1: 

                lcd_gotoxy(0,0);
                lcd_puts(MENSAJE_MENU_HELADERA);  

                menu_heladera (heladeras [HELA_1]);
                if (tiempo > TIEMPO_CORTE)
                    menu=MENU_PRINCIPAL;

                if(encoder){
                    seleccionar_menu(&menu, heladeras [HELA_1], &PIND);
                }

            break;

            case MENU_HELADERA_2:

                lcd_gotoxy(0,0);
                lcd_puts(MENSAJE_MENU_HELADERA);  

                menu_heladera (heladeras [HELA_2]);
                if (tiempo > TIEMPO_CORTE)
                    menu=MENU_PRINCIPAL;

                if(encoder){
                    seleccionar_menu(&menu, heladeras [HELA_2], &PIND);
                }
            break;

            case MENU_HELADERA_3:

                lcd_gotoxy(0,0);
                lcd_puts(MENSAJE_MENU_HELADERA);   

                menu_heladera (heladeras [HELA_3]);
                if (tiempo > TIEMPO_CORTE)
                    menu=MENU_PRINCIPAL;

                if(encoder){
                    seleccionar_menu(&menu, heladeras [HELA_3], &PIND);
                }
            break;

            case MENU_HELADERA_4:

                lcd_gotoxy(0,0);
                lcd_puts(MENSAJE_MENU_HELADERA);   

                menu_heladera (heladeras [HELA_4]);
                if (tiempo > TIEMPO_CORTE)
                    menu=MENU_PRINCIPAL;

                if(encoder){
                    seleccionar_menu(&menu, heladeras [HELA_4], &PIND);
                }
            break;

        }

    }
}
