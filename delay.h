/*
 delay_us(x) and delay_ms(x) for C30
 */
#ifndef __DELAY_H
#define __DELAY_H
#define FOSC  64000000LL  // clock-frequecy in Hz with suffix LL (64-bit-long), eg. 32000000LL for 32MHz
#define FCY       (FOSC/4)  // MCU is running at FCY MIPS
#define delay_us(x) __delay32(((x*FCY)/1000000L)) // delays x us
#define delay_ms(x) __delay32(((x*FCY)/1000L))  // delays x ms
#include <libpic30.h> // auto-included (built-in?)
#endif
