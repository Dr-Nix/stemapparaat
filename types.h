#ifndef TYPES_H
#define TYPES_H

_FOSC(CSW_FSCM_OFF & XT_PLL16);         /* XT with 16xPLL oscillator, Failsafe clock off */
//_FOSC(CSW_FSCM_OFF & ECIO_PLL4);         /* XT with 16xPLL oscillator, Failsafe clock off */
_FWDT(WDT_OFF);                         /* Watchdog timer disabled */
_FBORPOR(PBOR_OFF & MCLR_EN);           /* Brown-out reset disabled, MCLR reset enabled */
_FGS(CODE_PROT_OFF);                    /* Code protect disabled */

#define Fosc ( 4000000LL * 16 )
#define Fcy ( Fosc / 4 )

#define LED1      LATBbits.LATB3
#define LED1_TRIS TRISBbits.TRISB3
#define LED2      LATBbits.LATB4
#define LED2_TRIS TRISBbits.TRISB4
#define LED3      LATBbits.LATB5
#define LED3_TRIS TRISBbits.TRISB5
#define LED4      LATBbits.LATB6
#define LED4_TRIS TRISBbits.TRISB6
#define LED5      LATBbits.LATB7
#define LED5_TRIS TRISBbits.TRISB7
#define LED6      LATBbits.LATB8
#define LED6_TRIS TRISBbits.TRISB8
#define LED7      LATBbits.LATB9
#define LED7_TRIS TRISBbits.TRISB9
#define LED8      LATBbits.LATB10
#define LED8_TRIS TRISBbits.TRISB10
#define LED9      LATBbits.LATB11
#define LED9_TRIS TRISBbits.TRISB11
#define LED10      LATBbits.LATB12
#define LED10_TRIS TRISBbits.TRISB12
#define LED11      LATDbits.LATD0
#define LED11_TRIS TRISDbits.TRISD0
#define LED12      LATDbits.LATD1
#define LED12_TRIS TRISDbits.TRISD1
#define LED13      LATFbits.LATF0
#define LED13_TRIS TRISFbits.TRISF0
#define LED14      LATFbits.LATF1
#define LED14_TRIS TRISFbits.TRISF1
#define LED15      LATFbits.LATF4
#define LED15_TRIS TRISFbits.TRISF4
#define LED16      LATAbits.LATA11
#define LED16_TRIS TRISAbits.TRISA11
#define INT_LED1         LATFbits.LATF5
#define INT_LED1_TRIS    TRISFbits.TRISF5
#define INT_LED2         LATFbits.LATF2
#define INT_LED2_TRIS    TRISFbits.TRISF2
#define BUTTON_UP        PORTDbits.RD8
#define BUTTON_UP_TRIS   TRISDbits.TRISD8
#define BUTTON_DOWN      PORTDbits.RD9
#define BUTTON_DOWN_TRIS TRISDbits.TRISD9

union Period_union {            // union to access long value of the period or the individual parts
   unsigned long l;
   struct period_struct {
       unsigned int residue;    // swap when endianness changes
       unsigned int period;
   }i;
};

#endif
