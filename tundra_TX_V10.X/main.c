/**
  Generated Main Source File

  Company:
    Microchip Technology Inc.

  File Name:
    main.c

  Summary:
    This is the main file generated using PIC10 / PIC12 / PIC16 / PIC18 MCUs

  Description:
    This header file provides implementations for driver APIs for all modules
  selected in the GUI. Generation Information : Product Revision  :  PIC10 /
  PIC12 / PIC16 / PIC18 MCUs - 1.81.8 Device            :  PIC16F1936 Driver
  Version    :  2.00
 */

// 20260511 TUNDRA_TX V10 CS:7F19
// 使用CRC8校驗(table)
// D4=D2
// D5=D2
// D6=D3
// D7=D3
//SW1:行車燈
//SW2:晝行燈
//SW3:近燈
//SW4:遠燈
//SW5:左方向燈
//SW6:右方向燈

#include "mcc_generated_files/mcc.h"
#include "tundra.h"
#include "tundra_crc8.h"


// Variable declaration
flag_D2 D2 = {.Byte = 0};
flag_D3 D3 = {.Byte = 0};
DATA_FRAME tx_data = {
    .id = 0xC8,     // 車燈信號
    .length = 0x8B, // 8 byte
    .data = {0},
    .crc = 0x04C // check sum
};

void wait_for_pwm_cycle_complete(void) {
  while (!TMR2IF)
    ;

  TMR2IF = 0;
}

void PWM(unsigned char num) {
  // Initial reset pulse
  wait_for_pwm_cycle_complete();
  CCPR3L = PWM_LOW_PULSE;

  // Transmit each bit as corresponding pulse width
  for (unsigned char i = 0; i < PWM_BITS; i++) {
    wait_for_pwm_cycle_complete();
    CCPR3L = ((num >> i) & 0x01) ? PWM_HIGH_PULSE : PWM_LOW_PULSE;
  }

  // Trailing pulses
  for (unsigned char i = 0; i < PWM_BITS; i++) {
    wait_for_pwm_cycle_complete();
    CCPR3L = PWM_TRAIL_PULSE;
  }
}

void Check_Input(void) {
  // initionzation flag
  D2.Byte = 0;
  D3.Byte = 0;

  // 行車
  if (SW1 == SW_ON) {
    LED1 = LED_ON;
    D2.RunLight = 1;
  } else {
    LED1 = LED_OFF;
    D2.RunLight = 0;
  }

  // 晝行
  if (SW2 == SW_ON) {
    LED2 = LED_ON;
    D2.DRL = 1;
  } else {
    LED2 = LED_OFF;
    D2.DRL = 0;
  }

  // 近燈
  if (SW3 == SW_ON) {
    LED3 = LED_ON;
    D2.LoBeam = 1;
  } else {
    LED3 = LED_OFF;
    D2.LoBeam = 0;
  }

  // 遠燈
  if (SW4 == SW_ON) {
    LED4 = LED_ON;
    D2.HiBeam = 1;
  } else {
    LED4 = LED_OFF;
    D2.HiBeam = 0;
  }

  // 左方向燈
  if (SW5 == SW_ON) {
    LED5 = LED_ON;
    D3.turnLight_L = 1;
  } else {
    LED5 = LED_OFF;
    D3.turnLight_L = 0;
  }

  // 右方向燈
  if (SW6 == SW_ON) {
    LED6 = LED_ON;
    D3.trunLight_R = 1;
  } else {
    LED6 = LED_OFF;
    D3.trunLight_R = 0;
  }
}

/*
                         Main application
 */
int main(void) {
  // initialize the device
  SYSTEM_Initialize();

  while (1) {
    // Add your application code
    Check_Input();

    // Prepare data for transmission
    tx_data.data[0] = D2.Byte; // D0
    tx_data.data[1] = D3.Byte; // D1
    // D4~D7 are 0 by D2
    tx_data.data[4] = D2.Byte; // D4
    tx_data.data[5] = D2.Byte; // D5
    tx_data.data[6] = D3.Byte; // D6
    tx_data.data[7] = D3.Byte; // D7
    tx_data.crc = calculate_crc8_real(tx_data.data, data_length);

    // Transmit data via PWM
    // PWM(tx_data.id); // ID
    // PWM(tx_data.length); // Length

    // for (unsigned char i = 0; i < data_length; i++) {
    //   PWM(tx_data.data[i]); // D1~D8
    // }
    // PWM(tx_data.crc); // CRC
    for (uint8_t i = 0; i < buf_length; i++) {
      PWM(tx_data.buf[i]);
    }

    __delay_ms(20); // Optional delay between transmissions
  }
  return 0;
}
/**
 End of File
 */