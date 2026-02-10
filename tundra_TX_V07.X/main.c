//**********************************************************************************
//          PIC16F1936 Pinout for this example
//                    ------------
//               MCLR |1       28| RB7 ->
//        SW1 ->  RA0 |2       27| RB6 ->
//        SW2 ->  RA1 |3       26| RB5 -> LED1
//        SW3 ->  RA2 |4       25| RB4 -> LED2
//        SW4 ->  RA3 |5       24| RB3 -> LED3
//        SW5 ->  RA4 |6       23| RB2 -> LED4
//            ->  RA5 |7       22| RB1 -> LED5
//                GND |8       21| RB0 -> LED6
//            ->  RA7 |9       20| VDD
//            ->  RA6 |10      19| VSS
//            ->  RC0 |11      18| RC7 -> RX //IN
//            ->  RC1 |12      17| RC6 -> TX //PWM3
//            ->  RC2 |13      16| RC5 ->
//        SW6 ->  RC3 |14      15| RC4 ->
//                    ------------
//
//***********************************************************************************
// #include <xc.h>
// #pragma config statements should precede project file includes.
// Use project enums instead of #define for ON and OFF.

// 20250722 TY1014_TX V01 CS:2556
// 右方改成行車特殊信號
// C8 8B 6 0 0 0 0 0 0 0 D5
// 左方改成CheckSum error
// C8 8B 0 0 0 0 0 0 0 0 D5

// 20280801 TY1014_TX V02 CS:2556
// 左方改成行車特殊信號
// C8 8B 6 0 0 0 0 0 0 0 D5
// 左方改成近遠燈(超車)同時送,搭配晝行測試(修正畫行+超車(近燈+遠燈)CheckSum)
// C8 8B 38 0 0 0 0 0 0 0 B1

// 20250806 TY1475_HIGH_TX V01 CS:CBAD
// SW5,SW6 改回方向燈信號

// 20250818 TY1475_HIGH_TX V02 CS:CC0D
// 修改CRC值
// 畫行+遠燈+近燈(超車)+右方
// 畫行+遠燈+近燈(超車)+左方
// 畫行+遠燈+近燈(超車)+警示
// 右方+左方(警示)
// 遠燈+近燈(超車)+左方
// 畫行+遠燈+近燈(超車)

// 20250912 V03 CS:113F
//  開機時右方開關==OFF 就測試左方向，否則測試右方向

// 20251023 V04 CS:861B
// 修正左方測試LED6恆亮 bug.

// 20251030 V05 CS:3DF4
// 修改CHECKSUM
// 恢復左右方向燈，取消UNLOCK信號.

// 20251031 V06 CS:967A
// 不用柯松資料
// 抓到所有資料(包括車子沒有的信號)

//20260210 V07 CS:95D4
//新增UNLOCK和CLEAR信號
//SW5 UNLOCK
//SW6 CLEAR

#include <pic16f1936.h>
#include <stdint.h>
#include <xc.h>

// CONFIG1
#pragma config FCMEN = OFF
#pragma config IESO = OFF
#pragma config CLKOUTEN = OFF // Clock Out Enable (CLKOUT function is disabled.
// I/O or oscillator function on the CLKOUT pin)
#pragma config BOREN = ON // Brown-out Reset Enable (Brown-out Reset enabled)
#pragma config CPD = ON
#pragma config CP = OFF // Flash Program Memory Code Protection (Program memory
// code protection is disabled)
#pragma config MCLRE =                                                         \
    OFF // MCLR Pin Function Select (MCLR/VPP pin function is digital input)
#pragma config PWRTE = OFF   // Power-up Timer Enable (PWRT enabled)
#pragma config WDTE = OFF    // Watchdog Timer Enable (WDT enabled)
#pragma config FOSC = INTOSC // Oscillator Selection Bits (INTOSC oscillator:
// I/O function on CLKIN pin)

// CONFIG2
#pragma config LVP =                                                           \
    OFF // Low-Voltage Programming Enable (Low-voltage programming enabled)
#pragma config BORV = LO // Brown-out Reset Voltage Selection (Brown-out Reset
// Voltage (Vbor), low trip point selected.)
#pragma config STVREN = ON // Stack Overflow/Underflow Reset Enable (Stack
// Overflow or Underflow will cause a Reset)
#pragma config PLLEN = ON // Phase Lock Loop enable (4x PLL is always enabled)
#pragma config VCAPEN = OFF
#pragma config WRT =                                                           \
    OFF // Flash Memory Self-Write Protection (Write protection off)
#define _XTAL_FREQ 32000000

// Hardware_IO_定義
// #define  PORTBbits.RB7
// #define  PORTBbits.RB6
#define LED1 PORTBbits.RB5
#define LED2 PORTBbits.RB4
#define LED3 PORTBbits.RB3
#define LED4 PORTBbits.RB2
#define LED5 PORTBbits.RB1
#define LED6 PORTBbits.RB0
// #define  PORTCbits.RC7
// #define  PORTCbits.RC6
// #define  PORTCbits.RC5
// #define  PORTCbits.RC4
#define SW6 PORTCbits.RC3
// #define  PORTCbits.RC2
// #define  PORTCbits.RC1
// #define  PORTCbits.RC0
// #define  PORTAbits.RA6
// #define  PORTAbits.RA7
// #define  PORTAbits.RA5
#define SW5 PORTAbits.RA4
#define SW4 PORTAbits.RA3
#define SW3 PORTAbits.RA2
#define SW2 PORTAbits.RA1
#define SW1 PORTAbits.RA0
#define ON 1
#define OFF 0
#define LOBEAMbits 0B00010000
#define LOBEAMbits_DRLbits 0B00011000
#define HIBEAMbits 0B00100000

typedef union {
  struct {
    _Bool b0 : 1;
    _Bool b1 : 1;
    _Bool RunLight : 1;
    _Bool DRL : 1;
    _Bool LoBeam : 1;
    _Bool HiBeam : 1;
    _Bool b6 : 1;
    _Bool b7 : 1;
  };
  uint8_t Byte;
} flag_D2;

typedef union {

  struct {
    _Bool b0 : 1;
    _Bool b1 : 1;
    _Bool b2 : 1;
    _Bool b3 : 1;
    _Bool b4 : 1;
    _Bool turnLight_L : 1;
    _Bool trunLight_R : 1;
    _Bool b7 : 1;
  };
  uint8_t Byte;
} flag_D3;

typedef union {

  struct {
    _Bool turnLight_R : 1;
    _Bool turnLight_L : 1;
    _Bool HiBeam : 1;
    _Bool LoBeam : 1;
    _Bool DRL : 1;
    _Bool RunLight : 1;
    _Bool b6 : 1;
    _Bool b7 : 1;
  };
  uint8_t Byte;
} flag_CS_index;

// Function declaration
void LED_OFF(void);
void wait_for_pwm_cycle_complete(void);
void PWM(unsigned char num);
void Hardware_Init(void);
void Check_Input(void);

// Variable declaration
flag_D2 D2;
flag_D3 D3;
flag_CS_index csFlag;
_Bool fException = 0;
_Bool fException2 = 0;

_Bool flamp_left = 0;
uint8_t tx_Data[11] = {0};
static uint8_t CS[64] = {
    // 行車,晝行,近燈,遠燈,左方,右方
    0x4C, // 000000 關
    0x9F, // 000001 右方
    0xED, // 000010 左方
    0x3E, // 000011 右方+左方(警示)

    // 0x9A, // 000100 遠燈 (KOSO)
    0x66, // 000100 遠燈
    0xB5, // 000101 遠燈+右方
    0xC7, // 000110 遠燈+左方
    0x14, // 000111 遠燈+右方+左方(警示)

    //     0x27, // 001000 近燈 (KOSO)
    0x59, // 001000 近燈
    0x8A, // 001001 近燈+右方
    0xF8, // 001010 近燈+左方
    0x2B, // 001011 近燈+右方+左方(警示)

    //    0xF1, // 001100 遠燈+近燈(超車) (KOSO)
    0x73, // 001100 遠燈+近燈(超車)
    0xA0, // 001101 遠燈+近燈(超車)+右方
    0xD2, // 001110 遠燈+近燈(超車)+左方
    0x01, // 001111 遠燈+近燈(超車)+右方+左方(警示)

    // 0xB1, // 010000 晝行 (KOSO)
    0x8E, // 010000 晝行
    0x5D, // 010001 晝行+右方
    0x2F, // 010010 晝行+左方
    0xFC, // 010011 晝行+右方+左方(警示)

    //    0x67, // 010100 晝行+遠燈 (KOSO)
    0xA4, // 010100 晝行+遠燈
    0x77, // 010101 晝行+遠燈+右方
    0x05, // 010110 晝行+遠燈+左方
    0xD6, // 010111 晝行+遠燈+右方+左方(警示)

    //    0xDA, // 011000 晝行+近燈 (KOSO)
    0x9B, // 011000 晝行+近燈
    0x48, // 011001 晝行+近燈+右方
    0x3A, // 011010 晝行+近燈+左方
    0xE9, // 011011 晝行+近燈+右方+左方(警示)

    //    0x0C, // 011100 畫行+遠燈+近燈(超車) (KOSO)
    0xB1, // 011100 畫行+遠燈+近燈(超車)
    0x62, // 011101 畫行+遠燈+近燈(超車)+右方
    0x10, // 011110 畫行+遠燈+近燈(超車)+左方
    0xC3, // 011111 晝行+遠燈+近燈(超車)+右方+左方(警示)

    // 0xFA, // 100000 行車 (KOSO)
    0x2D, // 100000 行車
    0xFE, // 100001 行車+右方
    0x8C, // 100010 行車+左方
    0x5F, // 100011 行車+右方+左方(警示)

    //    0x2C, // 100100 行車+遠燈 (KOSO)
    0x07, // 100100 行車+遠燈
    0xD4, // 100101 行車+遠燈+右方
    0xA6, // 100110 行車+遠燈+左方
    0x75, // 100111 行車+遠燈+右方+左方(警示)

    // 0x91, // 101000 行車+近燈 (KOSO)
    0x38, // 101000 行車+近燈
    0xEB, // 101001 行車+近燈+右方
    0x99, // 101010 行車+近燈+左方
    0x4A, // 101011 行車+近燈+右方+左方(警示)

    //    0x47, // 101100 行車+遠燈+近燈(超車) (KOSO)
    0x12, // 101100 行車+遠燈+近燈(超車)
    0xC1, // 101101 行車+遠燈+近燈(超車)+右方
    0xB3, // 101110 行車+遠燈+近燈(超車)+左方
    0x60, // 101111 行車+遠燈+近燈(超車)+右方+左方(警示)

    // 0x07, // 110000 行車+晝行 (KOSO)
    0xEF, // 110000 行車+晝行
    0x3C, // 110001 行車+晝行+右方
    0x4E, // 110010 行車+晝行+左方
    0x9D, // 110011 行車+晝行+右方+左方(警示)

    //    0xD1, // 110100 行車+晝行+遠燈 (KOSO)
    0xC5, // 110100 行車+晝行+遠燈
    0x16, // 110101 行車+晝行+遠燈+右方
    0x64, // 110110 行車+晝行+遠燈+左方
    0xB7, // 110111 行車+晝行+遠燈+右方+左方(警示)

    //    0x6C, // 111000 行車+晝行+近燈 (KOSO)
    0xFA, // 111000 行車+晝行+近燈
    0x29, // 111001 行車+晝行+近燈+右方
    0x5B, // 111010 行車+晝行+近燈+左方
    0x88, // 111011 行車+晝行+近燈+右方+左方(警示)

    //    0xBA, // 111100 行車+晝行+遠燈+近燈 (KOSO)
    0xD0, // 111100 行車+晝行+遠燈+近燈
    0x03, // 111101 行車+晝行+遠燈+近燈+右方
    0x71, // 111110 行車+晝行+遠燈+近燈+左方
    0xA2, // 111111 行車+晝行+遠燈+近燈(超車)+右方+左方(警示)
};

/*
unsigned char data0[4] = {0, 0, 0, 76};    // 關
unsigned char data38[4] = {0, 64, 0, 159}; // 關+右方
unsigned char data37[4] = {0, 32, 0, 237}; // 關+左方
unsigned char data39[4] = {0, 96, 0, 62};  // 關+警示燈

unsigned char data1[4] = {4, 0, 4, 250};    // 行車
unsigned char data2[4] = {4, 0, 0, 45};     // 行
unsigned char data4[4] = {4, 64, 0, 254};   // 行+右方
unsigned char data3[4] = {4, 32, 0, 140};   // 行+左方
unsigned char data40[4] = {4, 96, 0, 95};   // 行+警示燈
unsigned char data47[4] = {6, 0, 0, 213};   // P2 解鎖-1 (TY1489高配-行車會緩亮)

unsigned char data5[4] = {8, 0, 8, 177}; // 晝行
unsigned char data6[4] = {8, 0, 0, 142}; // 晝行
unsigned char data8[4] = {8, 64, 0, 93}; // 晝行+右方
unsigned char data7[4] = {8, 32, 0, 47}; // 晝行+左方
unsigned char data41[4] = {8, 96, 0, 252};  // 晝+警示燈

unsigned char data13[4] = {16, 0, 16, 39}; // 近燈
//缺右方
//缺左方
//缺警示

unsigned char data20[4] = {32, 0, 32, 154}; // 遠燈
//缺右方
//缺左方
//缺警示

unsigned char data9[4] = {12, 0, 12, 7};   // 行+晝
unsigned char data10[4] = {12, 0, 0, 239}; // 行+晝
unsigned char data12[4] = {12, 64, 0, 60}; // 行+晝+右方
unsigned char data11[4] = {12, 32, 0, 78}; // 行+晝+左方
unsigned char data42[4] = {12, 96, 0, 157}; // 行+晝+警示燈

unsigned char data14[4] = {20, 0, 20, 145}; // 行+近
unsigned char data15[4] = {20, 0, 0, 56};   // 行+近
unsigned char data17[4] = {20, 64, 0, 235}; // 行+近+右方
unsigned char data16[4] = {20, 32, 0, 153}; // 行+近+左方
unsigned char data43[4] = {20, 96, 0, 74};  // 行+近+警示燈

unsigned char data21[4] = {36, 0, 36, 44};  // 行+遠
//缺右方
//缺左方
//缺警示

unsigned char data18[4] = {24, 0, 24, 218}; // 晝+近
//缺右方
//缺左方
//缺警示

unsigned char data22[4] = {40, 0, 40, 103}; // 晝+遠
//缺右方
//缺左方
//缺警示

unsigned char data24[4] = {48, 0, 48, 241}; // 近+遠
unsigned char data25[4] = {48, 0, 0, 115};  // 近燈+遠燈(超車)
unsigned char data27[4] = {48, 64, 0, 160}; // 超車+右方 (近+遠+右方)
unsigned char data26[4] = {48, 32, 0, 113}; // 超車+左方 (近+遠+左方)
unsigned char data45[4] = {48, 96, 0, 1};   // 超車+警示燈 (近+遠+警示燈)

unsigned char data19[4] = {28, 0, 28, 108}; // 行+晝+近
//缺右方
//缺左方
//缺警示

unsigned char data23[4] = {44, 0, 44, 209}; // 行+晝+遠
//缺右方
//缺左方
//缺警示

unsigned char data28[4] = {52, 0, 52, 71};  // 行+近+遠
unsigned char data29[4] = {52, 0, 0, 18};   // 行+近+遠
unsigned char data31[4] = {52, 64, 0, 193}; // 行+近+遠+右方
unsigned char data30[4] = {52, 32, 0, 179}; // 行+近+遠+左方
unsigned char data44[4] = {52, 96, 0, 96};  // 行+近+遠+警示燈

unsigned char data32[4] = {56, 0, 56, 12}; // 晝+近+遠
//缺右方
//缺左方
//缺警示

unsigned char data33[4] = {60, 0, 60, 186}; // 行+晝+近+遠
unsigned char data34[4] = {60, 0, 0, 208};  // 行+超車 (行+晝+近+遠)
unsigned char data36[4] = {60, 64, 0, 3};   // 行+超車+右方 (行+晝+近+遠+右方)
unsigned char data35[4] = {60, 32, 0, 113}; // 行+超車+左方 (行+晝+近+遠+左方)
unsigned char data46[4] = {60, 96, 0, 162}; // 行+超車+警示燈
(行+晝+近+遠+警示燈)
 */

unsigned char data48[4] = {2, 0, 0, 180}; // 解鎖-2 (KD無任何動作)
unsigned char a = 0, b = 0;
// unsigned char i = 0, j = 0, mode = 0, x = 0;

void LED_OFF(void) { LATB = 0; }

void wait_for_pwm_cycle_complete(void) {
  while (1) {
    if (TMR2IF) {
      TMR2IF = 0; // 清除 TMR2 溢出中断标志位
      break;
    }
  } // 等待 PWM 周期完成
}

void PWM(unsigned char num) {
  unsigned char Dbit[8] = {0};
  Dbit[0] = (num >> 0) & 0x01;
  Dbit[1] = (num >> 1) & 0x01;
  Dbit[2] = (num >> 2) & 0x01;
  Dbit[3] = (num >> 3) & 0x01;
  Dbit[4] = (num >> 4) & 0x01;
  Dbit[5] = (num >> 5) & 0x01;
  Dbit[6] = (num >> 6) & 0x01;
  Dbit[7] = (num >> 7) & 0x01;
  wait_for_pwm_cycle_complete(); // 截止
  CCPR3L = 55;

  for (uint8_t i = 0; i < 8; i++) {
    if (Dbit[i] == 1) {
      Dbit[i] = 30;
    } else {
      Dbit[i] = 55;
    }
    wait_for_pwm_cycle_complete(); // 等待 PWM 周期完成
    CCPR3L = Dbit[i];
  }

  for (uint8_t i = 0; i < 8; i++) {
    wait_for_pwm_cycle_complete(); // 截止
    CCPR3L = 30;
  }
}

void Hardware_Init(void) {
  OSCCON = 0b11110000; // 32Mhz (PLLEN = ON / FOSC = INTOSC)
  // //OSCCON=0b01111010;  //16MHz // 0b01011010(1MHZ)
  OSCTUNE = 0b00111111; // 振盪器頻率微調 (降速1) //PWM 接近19.2kHz
  ANSELA = 0b00000000;  // 設定全部為數位
  PORTA = 0;
  TRISA = 0b00011111; // RA0~4 為輸入
  LATA = 0b00000000;
  ANSELB = 0b00000000; // 設定全部為數位
  PORTB = 0;
  TRISB = 0b00000000; // RB 為輸出
  LATB = 0b00000000;
  PORTC = 0;
  TRISC = 0b10001010; // RC1,3,7 為輸入
  LATC = 0b00000000;
  PORTE = 0;
  TRISE = 0b00000000;
  LATE = 0b00000000;
  __delay_ms(100);
  CCP3CON = 0b00001100; // 啟動PWM3，負緣觸發
  CCP3SEL = 0;          // 0:PWM3=RC6  // 1:PWM3=RB5
  PR2 = 103;            // 週期
  CCPR3L = 30;          // 負工作值
  TMR2ON = 1;           // 啟動Timer2
  T2CKPS1 = 0;          // 分頻值,00=1,01=4,10=16,11=64
  T2CKPS0 = 1;
}

void Check_Input(void) {
  // initionzation flag
  D2.Byte = 0;
  D3.Byte = 0;
  csFlag.Byte = 0;

  // 行車
  if (SW1 == OFF) {
    LED1 = ON;
    D2.RunLight = 1;
    csFlag.RunLight = 1;
  } else {
    LED1 = OFF;
    D2.RunLight = 0;
    csFlag.RunLight = 0;
  }

  // 晝行
  if (SW2 == OFF) {
    LED2 = ON;
    D2.DRL = 1;
    csFlag.DRL = 1;
  } else {
    LED2 = OFF;
    D2.DRL = 0;
    csFlag.DRL = 0;
  }

  // 近燈
  if (SW3 == OFF) {
    LED3 = ON;
    D2.LoBeam = 1;
    csFlag.LoBeam = 1;
  } else {
    LED3 = OFF;
    D2.LoBeam = 0;
    csFlag.LoBeam = 0;
  }

  // 遠燈
  if (SW4 == OFF) {
    LED4 = ON;
    D2.HiBeam = 1;
    csFlag.HiBeam = 1;
  } else {
    LED4 = OFF;
    D2.HiBeam = 0;
    csFlag.HiBeam = 0;
  }

  // 左方向燈
  // if (SW5 == OFF) {
  //   LED5 = ON;
  //   D3.turnLight_L = 1;
  //   csFlag.turnLight_L = 1;
  // } else {
  //   LED5 = OFF;
  //   D3.turnLight_L = 0;
  //   csFlag.turnLight_L = 0;
  // }

  // 右方向燈
  // if (SW6 == OFF) {
  //   LED6 = ON;
  //   D3.trunLight_R = 1;
  //   csFlag.turnLight_R = 1;
  // } else {
  //   LED6 = OFF;
  //   D3.trunLight_R = 0;
  //   csFlag.turnLight_R = 0;
  // }

  
  // 行車特殊信號
  if (SW5 == OFF) {
    LED5 = ON;
    D2.Byte = 6;
    D3.Byte = 0;
    fException = 1;
  } else {
    LED5 = OFF;
    fException = 0;
  }

  // 行車特殊信號
  if (SW6 == OFF) {
    LED6 = ON;
    D2.Byte = 2;
    D3.Byte = 0;
    fException2 = 1;
  } else {
    LED6 = OFF;
    fException2 = 0;
  }
}

// #define debug 1

int main(void) {
  Hardware_Init();
  // if (SW6 == OFF)
  //   flamp_left = 1;

  // tx data initialzation
  tx_Data[0] = 0xC8; // 車燈信號
  tx_Data[1] = 0x8B; // 8 byte
  tx_Data[2] = 0x00; // 7 6  5   4     3   2   1 0
  // X X 遠燈 近燈 晝行 行車 X X
  tx_Data[3] = 0x00; // 7  6    5  4 3 2 1 0
  // X 右方 左方 X X X X X
  tx_Data[4] = 0x00;
  tx_Data[5] = 0x00;
  tx_Data[6] = 0x00;
  tx_Data[7] = 0x00;
  tx_Data[8] = 0x00;
  tx_Data[9] = 0x00;
  tx_Data[10] = 0x04C; // check sum

  while (1) {
    Check_Input();

    tx_Data[2] = D2.Byte;
    tx_Data[3] = D3.Byte;

    // 特列使用KOSO的CS
    // 近燈
    //  if(D3.Byte==0){
    //    if((D2.Byte==LOBEAMbits)||
    //    //遠燈
    //    (D2.Byte==HIBEAMbits) ||
    //    //近燈+畫行
    //    (D2.Byte==LOBEAMbits_DRLbits))

    //   {
    //     tx_Data[6] = D2.Byte;
    //     tx_Data[7] = D2.Byte;
    //     tx_Data[8] = D2.Byte;
    //     tx_Data[9] = D2.Byte;
    //   }
    // }

    if (fException == 1) {
      tx_Data[10] = 0xD5;
    } else {
      tx_Data[10] = CS[csFlag.Byte];
    }

    if (fException2 == 1) {
      tx_Data[10] = 0xB4;
    }

// #define test
#ifdef test
    for (int j = 0xA0; j < 256; j++) {
      tx_Data[10] = j;
      for (uint8_t i = 0; i < 11; i++) {
        PWM(tx_Data[i]);
      }

      CCPR3L = 30;
      // __delay_ms(20);
      __delay_ms(200);
    }
#else
    //     for (int j = 0x00; j < 256; j++) {
    //       tx_Data[0] = 0xC8; // 車燈信號
    //       tx_Data[1] = 0x8B; // 8 byte
    //       tx_Data[2] = 0x00; // 7 6  5   4     3   2   1 0
    //       // X X 遠燈 近燈 晝行 行車 X X
    //       tx_Data[3] = 0x00; // 7  6    5  4 3 2 1 0
    //       // X 右方 左方 X X X X X
    //       tx_Data[4] = 0x00;
    //       tx_Data[5] = 0x00;
    //       tx_Data[6] = 0x00;
    //       tx_Data[7] = 0x00;
    //       tx_Data[8] = 0x00;
    //       tx_Data[9] = 0x00;
    //       tx_Data[10] = 0x04C; // check sum
    //       for (uint8_t i = 0; i < 11; i++) {
    //         PWM(tx_Data[i]);
    //       }
    //       CCPR3L = 30;
    //       __delay_ms(20);
    //
    //       tx_Data[0] = 0xC8; // 車燈信號
    //       tx_Data[1] = 0x8B; // 8 byte
    //       tx_Data[2] = 0x1C; // 7 6  5   4     3   2   1 0
    //       // X X 遠燈 近燈 晝行 行車 X X
    //       tx_Data[3] = 0x60; // 7  6    5  4 3 2 1 0
    //       // X 右方 左方 X X X X X
    //       tx_Data[4] = 0x00;
    //       tx_Data[5] = 0x00;
    //       tx_Data[6] = 0x00;
    //       tx_Data[7] = 0x00;
    //       tx_Data[8] = 0x00;
    //       tx_Data[9] = 0x00;
    //       tx_Data[10] = j; // check sum
    for (uint8_t i = 0; i < 11; i++) {
      PWM(tx_Data[i]);
    }
    CCPR3L = 30;
    __delay_ms(20);
//     }
#endif
    NOP();
  }

  return 0;
}
