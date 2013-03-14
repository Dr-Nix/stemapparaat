/*
 * File:   main.c
 *
 * Created on February 9, 2010, 10:53 AM
 */

#include <stdio.h>
#include <stdlib.h>
#include <p30Fxxxx.h>
#include <dsp.h>
#include "types.h"
#include "delay.h"

fractional waardes[16];
fractional gemiddeld;

union Period_union periods[88];
unsigned int residue_accu;
int tone;                   // current tone (1-88)
int base;                   // current base (around 440 Hz)

//unsigned int PR3hist[50];
//unsigned int residue_accu_hist[50];
//int hist_cur;

void handle_buttons() {
    int octave;
    int tone_in_octave;

    delay_ms(1);
    while (BUTTON_UP == 1 || BUTTON_DOWN == 1) {
        //handle the buttons.
        if (BUTTON_UP == 1) {
            if (tone < 87) {
                tone += 1;
            }
        }
        if (BUTTON_DOWN == 1) {
            if (tone > 0) {
                tone -= 1;
            }
        }
        //make a pattern to show which tone is chosen
        octave = 1;
        tone_in_octave = tone;
        while (tone_in_octave > 11) {
            octave += 1;
            tone_in_octave -= 12;
        }
        LED1 = 0;
        LED2 = 0;
        LED3 = 0;
        LED4 = 0;
        LED5 = 0;
        LED6 = 0;
        LED7 = 0;
        LED8 = 0;
        LED9 = 0;
        LED10 = 0;
        LED11 = 0;
        LED12 = 0;
        LED13 = 0;
        LED14 = 0;
        LED15 = 0;
        LED16 = 0;
        switch (tone_in_octave) {
            case 0:
                LED1 = 1;
                break;
            case 1:
                LED2 = 1;
                break;
            case 2:
                LED3 = 1;
                break;
            case 3:
                LED4 = 1;
                break;
            case 4:
                LED5 = 1;
                break;
            case 5:
                LED6 = 1;
                break;
            case 6:
                LED7 = 1;
                break;
            case 7:
                LED8 = 1;
                break;
            case 8:
                LED9 = 1;
                break;
            case 9:
                LED10 = 1;
                break;
            case 10:
                LED11 = 1;
                break;
            case 11:
                LED12 = 1;
                break;
            default:
                break;
        }
        LED16 = octave & 1;
        LED15 = (octave & 2) > 1;
        LED14 = (octave & 4) > 2;
        LED13 = (octave & 8) > 3;
        delay_ms(500);
    }
    IFS1bits.INT1IF = 0;
    IFS1bits.INT2IF = 0;
}

void __attribute__((interrupt,auto_psv)) _INT1Interrupt() {
    handle_buttons();
}

void __attribute__((interrupt,auto_psv)) _INT2Interrupt() {
    handle_buttons();
}

void __attribute__((interrupt,auto_psv)) _T3Interrupt() {
    INT_LED1 = 1;
    IFS0bits.T3IF = 0;

    residue_accu += periods[tone].i.residue;
    if (residue_accu < periods[tone].i.residue) {
        PR3 = periods[tone].i.period + 1;
    } else {
        PR3 = periods[tone].i.period;
    }
    /*
    residue_accu_hist[hist_cur] = residue_accu;
    PR3hist[hist_cur] = PR3;
    hist_cur++;
    if (hist_cur > 49) {
        hist_cur = 0;
    }
     */
    INT_LED1 = 0;
}


void __attribute__((interrupt,auto_psv)) _ADCInterrupt() {
    volatile fractional *ADC16ptr;
    long int gemiddeld_long;
    int count;
    
    INT_LED2 = 1;                           // feedback on how busy the PIC is
    IFS0bits.ADIF = 0;                          // Clear interrupt flag

    ADC16ptr = (fractional *)&ADCBUF0;
    //ADC16ptr = &ADCBUF0;
    gemiddeld_long = 0;
    for (count = 0; count < 16; count++) {
        waardes[count] = *ADC16ptr;
        gemiddeld_long = gemiddeld_long + *ADC16ptr++;
    }
    gemiddeld = gemiddeld_long >> 4;

    LED1  = (waardes[0]  > gemiddeld);
    LED2  = (waardes[1]  > gemiddeld);
    LED3  = (waardes[2]  > gemiddeld);
    LED4  = (waardes[3]  > gemiddeld);
    LED5  = (waardes[4]  > gemiddeld);
    LED6  = (waardes[5]  > gemiddeld);
    LED7  = (waardes[6]  > gemiddeld);
    LED8  = (waardes[7]  > gemiddeld);
    LED9  = (waardes[8]  > gemiddeld);
    LED10 = (waardes[9]  > gemiddeld);
    LED11 = (waardes[10] > gemiddeld);
    LED12 = (waardes[11] > gemiddeld);
    LED13 = (waardes[12] > gemiddeld);
    LED14 = (waardes[13] > gemiddeld);
    LED15 = (waardes[14] > gemiddeld);
    LED16 = (waardes[15] > gemiddeld);

    INT_LED2 = 0;
}


void initPorts() {
    /* set LEDs drive state low */
    LATA = 0x0000;
    LATB = 0x0000;
    LATD = 0x0000;
    LATF = 0x0000;

    LED1_TRIS = 0;
    LED2_TRIS = 0;
    LED3_TRIS = 0;
    LED4_TRIS = 0;
    LED5_TRIS = 0;
    LED6_TRIS = 0;
    LED7_TRIS = 0;
    LED8_TRIS = 0;
    LED9_TRIS = 0;
    LED10_TRIS = 0;
    LED11_TRIS = 0;
    LED12_TRIS = 0;
    LED13_TRIS = 0;
    LED14_TRIS = 0;
    LED15_TRIS = 0;
    LED16_TRIS = 0;
    INT_LED1_TRIS = 0;
    INT_LED2_TRIS = 0;
    BUTTON_UP_TRIS = 1;
    BUTTON_DOWN_TRIS = 1;

    TRISBbits.TRISB0 = 1;        // RB0-2 used for ADC, so 'input'
    TRISBbits.TRISB1 = 1;        // RB0-2 used for ADC, so 'input'
    TRISBbits.TRISB2 = 1;        // RB0-2 used for ADC, so 'input'
    
    ADPCFG = 0b1111111111111000;        // AN0-AN1 are vref+-, AN2 is input, rest 'digital'
}

void initButtons() {
    IFS1bits.INT1IF = 0;        // flags off
    IFS1bits.INT2IF = 0;
    IEC1bits.INT1IE = 1;        // enable interrupts
    IEC1bits.INT2IE = 1;
    IPC4bits.INT1IP = 3;        // interrupt priority
    IPC5bits.INT2IP = 3;
}

void initTimer3()
{
    TMR3 = 0x0000;
    PR3 = periods[tone].i.period;
    
    IFS0bits.T3IF = 0;                  // interrupt flag off
    IEC0bits.T3IE = 1;                  // enable interrupt
    IPC1bits.T3IP = 2;                  // interrupt priority

    //start
    T3CONbits.TON = 1;
}

void initADC(void)
{

    ADCON1bits.FORM = 3;		// Data Output Format: Signed Fraction (Q15 format)
    ADCON1bits.SSRC = 2;		// Sample Clock Source: GP Timer starts conversion
    ADCON1bits.ASAM = 1;		// ADC Sample Control: Sampling begins immediately after conversion

    ADCON2bits.VCFG = 3;		// use VREF- and VREF+
    ADCON2bits.SMPI = 15;               // interrupt after 16 conversions
    ADCON2bits.BUFM = 0;                // No buffer swapping
    ADCON2bits.ALTS = 0;                // always into bufA
    ADCON2bits.CSCNA = 0;               // no scanning over analog inputs

    ADCON3bits.ADRC = 0;		// ADC Clock is derived from Systems Clock
    ADCON3bits.ADCS = 10;		// ADC Conversion Clock Tad=0.5*Tcy*(ADCS+1)= (0.5*1/16M)*(10+1) = 344ns
					// ADC Conversion Time for 10-bit Tc=14*Tad = 4.8125us

    //ADCHS: A/D Input Select Register
    ADCHSbits.CH0NA=0;                 // MUXA -ve input selection (Vref-) for CH0
    ADCHSbits.CH0SA=2;                 // MUXA +ve input selection (AN5) for CH0

    IFS0bits.ADIF = 0;			// Clear the A/D interrupt flag bit
    IEC0bits.ADIE = 1;			// Enable A/D interrupt
    IPC2bits.ADIP = 1;                  // Interrupt priority
    ADCON1bits.ADON = 1;		// Turn on the A/D converter
}
    
void generate_tones(int base) {

    const float increase_factor = 1.059463094359295;      // 2^(1/12), the frequency increase between tones
    const unsigned long long timebase = Fcy << 16; // derived from frequency upscaled to long long
    
    float cur_tone;
    unsigned long long long_period;
    int count;
    
    cur_tone = (float)base;                 // ah ah! The lowest note on the piano is 16 times below the base,
                                            // and we have 16 leds so we need 16 times this frequency! Ergo equal.
    // generate the first octave
    for (count = 0; count < 12; count++) {  
        long_period = timebase / cur_tone;    // 'simple' division yields the number of instructions per T (*2^16), where T=1/f_in
        periods[count].l = (unsigned long)long_period;  //truncate result to 32 bit
        cur_tone = cur_tone*increase_factor;  // next tone is this factor higher
    }
    // generate the rest of the tones
    for (count = 12; count < 88; count++) {
        periods[count].l = periods[count - 12].l >> 1;   // all other tones can be derived by dividing the period in half.
    }
    for (count = 0; count < 88; count++) {
        periods[count].l -= 0x00010001;       // Period and residue need to be 1 less, as the timer has an actual period of 'var+1'
    }
}

int main(int argc, char** argv) {

    generate_tones(440);            //start with a base of 440 Hz
    tone = 48;                      // start at middle A
    
    initPorts();
    initButtons();
    initADC();
    initTimer3();

    while(1) {
      
    }
    return (EXIT_SUCCESS);
}
