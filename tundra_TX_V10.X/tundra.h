
/* 
 * File:   tundra.h
 * Author: T00904
 * Comments: Main header file for the Tundra project
 * Revision history: V1.0 May 11, 2026
 */

// This is a guard condition so that contents of this file are not included
// more than once.  
#ifndef TUNDRA_H
#define	TUNDRA_H

#include <stdint.h>
#include <stdbool.h>

// define led1~led6
#define LED1 LED1_LAT
#define LED2 LED2_LAT
#define LED3 LED3_LAT
#define LED4 LED4_LAT
#define LED5 LED5_LAT
#define LED6 LED6_LAT
// Define led status
#define LED_ON 1
#define LED_OFF 0

// define sw1~sw6
#define SW1 SW1_PORT
#define SW2 SW2_PORT
#define SW3 SW3_PORT
#define SW4 SW4_PORT
#define SW5 SW5_PORT
#define SW6 SW6_PORT
// define switch status
#define SW_ON 0
#define SW_OFF 1

typedef union {
  struct {
    unsigned : 2;
    unsigned RunLight : 1;
    unsigned DRL : 1;
    unsigned LoBeam : 1;
    unsigned HiBeam : 1;
    unsigned : 2;
  };
  struct {
    unsigned Byte : 8;
  };
} flag_D2;

typedef union {

  struct {
    unsigned : 5;
    unsigned turnLight_L : 1;
    unsigned trunLight_R : 1;
    unsigned : 1;
  };
  struct {
    unsigned Byte : 8;
  };
} flag_D3;

typedef union {
  struct {
    uint8_t id;
    uint8_t length;
    uint8_t data[8];
    uint8_t crc;
  };
  struct {
    uint8_t buf[11];
  };
} DATA_FRAME;

#define data_length 8
#define buf_length 11
#define PWM_HIGH_PULSE 30
#define PWM_LOW_PULSE 55
#define PWM_TRAIL_PULSE 30
#define PWM_BITS 8


#endif	/* TUNDRA_H */

