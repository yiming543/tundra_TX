/**
  @Generated Pin Manager Header File

  @Company:
    Microchip Technology Inc.

  @File Name:
    pin_manager.h

  @Summary:
    This is the Pin Manager file generated using PIC10 / PIC12 / PIC16 / PIC18 MCUs

  @Description
    This header file provides APIs for driver for .
    Generation Information :
        Product Revision  :  PIC10 / PIC12 / PIC16 / PIC18 MCUs - 1.81.8
        Device            :  PIC16F1936
        Driver Version    :  2.11
    The generated drivers are tested against the following:
        Compiler          :  XC8 2.36 and above
        MPLAB 	          :  MPLAB X 6.00	
*/

/*
    (c) 2018 Microchip Technology Inc. and its subsidiaries. 
    
    Subject to your compliance with these terms, you may use Microchip software and any 
    derivatives exclusively with Microchip products. It is your responsibility to comply with third party 
    license terms applicable to your use of third party software (including open source software) that 
    may accompany Microchip software.
    
    THIS SOFTWARE IS SUPPLIED BY MICROCHIP "AS IS". NO WARRANTIES, WHETHER 
    EXPRESS, IMPLIED OR STATUTORY, APPLY TO THIS SOFTWARE, INCLUDING ANY 
    IMPLIED WARRANTIES OF NON-INFRINGEMENT, MERCHANTABILITY, AND FITNESS 
    FOR A PARTICULAR PURPOSE.
    
    IN NO EVENT WILL MICROCHIP BE LIABLE FOR ANY INDIRECT, SPECIAL, PUNITIVE, 
    INCIDENTAL OR CONSEQUENTIAL LOSS, DAMAGE, COST OR EXPENSE OF ANY KIND 
    WHATSOEVER RELATED TO THE SOFTWARE, HOWEVER CAUSED, EVEN IF MICROCHIP 
    HAS BEEN ADVISED OF THE POSSIBILITY OR THE DAMAGES ARE FORESEEABLE. TO 
    THE FULLEST EXTENT ALLOWED BY LAW, MICROCHIP'S TOTAL LIABILITY ON ALL 
    CLAIMS IN ANY WAY RELATED TO THIS SOFTWARE WILL NOT EXCEED THE AMOUNT 
    OF FEES, IF ANY, THAT YOU HAVE PAID DIRECTLY TO MICROCHIP FOR THIS 
    SOFTWARE.
*/

#ifndef PIN_MANAGER_H
#define PIN_MANAGER_H

/**
  Section: Included Files
*/

#include <xc.h>

#define INPUT   1
#define OUTPUT  0

#define HIGH    1
#define LOW     0

#define ANALOG      1
#define DIGITAL     0

#define PULL_UP_ENABLED      1
#define PULL_UP_DISABLED     0

// get/set SW1 aliases
#define SW1_TRIS                 TRISAbits.TRISA0
#define SW1_LAT                  LATAbits.LATA0
#define SW1_PORT                 PORTAbits.RA0
#define SW1_ANS                  ANSELAbits.ANSA0
#define SW1_SetHigh()            do { LATAbits.LATA0 = 1; } while(0)
#define SW1_SetLow()             do { LATAbits.LATA0 = 0; } while(0)
#define SW1_Toggle()             do { LATAbits.LATA0 = ~LATAbits.LATA0; } while(0)
#define SW1_GetValue()           PORTAbits.RA0
#define SW1_SetDigitalInput()    do { TRISAbits.TRISA0 = 1; } while(0)
#define SW1_SetDigitalOutput()   do { TRISAbits.TRISA0 = 0; } while(0)
#define SW1_SetAnalogMode()      do { ANSELAbits.ANSA0 = 1; } while(0)
#define SW1_SetDigitalMode()     do { ANSELAbits.ANSA0 = 0; } while(0)

// get/set SW2 aliases
#define SW2_TRIS                 TRISAbits.TRISA1
#define SW2_LAT                  LATAbits.LATA1
#define SW2_PORT                 PORTAbits.RA1
#define SW2_ANS                  ANSELAbits.ANSA1
#define SW2_SetHigh()            do { LATAbits.LATA1 = 1; } while(0)
#define SW2_SetLow()             do { LATAbits.LATA1 = 0; } while(0)
#define SW2_Toggle()             do { LATAbits.LATA1 = ~LATAbits.LATA1; } while(0)
#define SW2_GetValue()           PORTAbits.RA1
#define SW2_SetDigitalInput()    do { TRISAbits.TRISA1 = 1; } while(0)
#define SW2_SetDigitalOutput()   do { TRISAbits.TRISA1 = 0; } while(0)
#define SW2_SetAnalogMode()      do { ANSELAbits.ANSA1 = 1; } while(0)
#define SW2_SetDigitalMode()     do { ANSELAbits.ANSA1 = 0; } while(0)

// get/set SW3 aliases
#define SW3_TRIS                 TRISAbits.TRISA2
#define SW3_LAT                  LATAbits.LATA2
#define SW3_PORT                 PORTAbits.RA2
#define SW3_ANS                  ANSELAbits.ANSA2
#define SW3_SetHigh()            do { LATAbits.LATA2 = 1; } while(0)
#define SW3_SetLow()             do { LATAbits.LATA2 = 0; } while(0)
#define SW3_Toggle()             do { LATAbits.LATA2 = ~LATAbits.LATA2; } while(0)
#define SW3_GetValue()           PORTAbits.RA2
#define SW3_SetDigitalInput()    do { TRISAbits.TRISA2 = 1; } while(0)
#define SW3_SetDigitalOutput()   do { TRISAbits.TRISA2 = 0; } while(0)
#define SW3_SetAnalogMode()      do { ANSELAbits.ANSA2 = 1; } while(0)
#define SW3_SetDigitalMode()     do { ANSELAbits.ANSA2 = 0; } while(0)

// get/set SW4 aliases
#define SW4_TRIS                 TRISAbits.TRISA3
#define SW4_LAT                  LATAbits.LATA3
#define SW4_PORT                 PORTAbits.RA3
#define SW4_ANS                  ANSELAbits.ANSA3
#define SW4_SetHigh()            do { LATAbits.LATA3 = 1; } while(0)
#define SW4_SetLow()             do { LATAbits.LATA3 = 0; } while(0)
#define SW4_Toggle()             do { LATAbits.LATA3 = ~LATAbits.LATA3; } while(0)
#define SW4_GetValue()           PORTAbits.RA3
#define SW4_SetDigitalInput()    do { TRISAbits.TRISA3 = 1; } while(0)
#define SW4_SetDigitalOutput()   do { TRISAbits.TRISA3 = 0; } while(0)
#define SW4_SetAnalogMode()      do { ANSELAbits.ANSA3 = 1; } while(0)
#define SW4_SetDigitalMode()     do { ANSELAbits.ANSA3 = 0; } while(0)

// get/set SW5 aliases
#define SW5_TRIS                 TRISAbits.TRISA4
#define SW5_LAT                  LATAbits.LATA4
#define SW5_PORT                 PORTAbits.RA4
#define SW5_ANS                  ANSELAbits.ANSA4
#define SW5_SetHigh()            do { LATAbits.LATA4 = 1; } while(0)
#define SW5_SetLow()             do { LATAbits.LATA4 = 0; } while(0)
#define SW5_Toggle()             do { LATAbits.LATA4 = ~LATAbits.LATA4; } while(0)
#define SW5_GetValue()           PORTAbits.RA4
#define SW5_SetDigitalInput()    do { TRISAbits.TRISA4 = 1; } while(0)
#define SW5_SetDigitalOutput()   do { TRISAbits.TRISA4 = 0; } while(0)
#define SW5_SetAnalogMode()      do { ANSELAbits.ANSA4 = 1; } while(0)
#define SW5_SetDigitalMode()     do { ANSELAbits.ANSA4 = 0; } while(0)

// get/set LED6 aliases
#define LED6_TRIS                 TRISBbits.TRISB0
#define LED6_LAT                  LATBbits.LATB0
#define LED6_PORT                 PORTBbits.RB0
#define LED6_WPU                  WPUBbits.WPUB0
#define LED6_ANS                  ANSELBbits.ANSB0
#define LED6_SetHigh()            do { LATBbits.LATB0 = 1; } while(0)
#define LED6_SetLow()             do { LATBbits.LATB0 = 0; } while(0)
#define LED6_Toggle()             do { LATBbits.LATB0 = ~LATBbits.LATB0; } while(0)
#define LED6_GetValue()           PORTBbits.RB0
#define LED6_SetDigitalInput()    do { TRISBbits.TRISB0 = 1; } while(0)
#define LED6_SetDigitalOutput()   do { TRISBbits.TRISB0 = 0; } while(0)
#define LED6_SetPullup()          do { WPUBbits.WPUB0 = 1; } while(0)
#define LED6_ResetPullup()        do { WPUBbits.WPUB0 = 0; } while(0)
#define LED6_SetAnalogMode()      do { ANSELBbits.ANSB0 = 1; } while(0)
#define LED6_SetDigitalMode()     do { ANSELBbits.ANSB0 = 0; } while(0)

// get/set LED5 aliases
#define LED5_TRIS                 TRISBbits.TRISB1
#define LED5_LAT                  LATBbits.LATB1
#define LED5_PORT                 PORTBbits.RB1
#define LED5_WPU                  WPUBbits.WPUB1
#define LED5_ANS                  ANSELBbits.ANSB1
#define LED5_SetHigh()            do { LATBbits.LATB1 = 1; } while(0)
#define LED5_SetLow()             do { LATBbits.LATB1 = 0; } while(0)
#define LED5_Toggle()             do { LATBbits.LATB1 = ~LATBbits.LATB1; } while(0)
#define LED5_GetValue()           PORTBbits.RB1
#define LED5_SetDigitalInput()    do { TRISBbits.TRISB1 = 1; } while(0)
#define LED5_SetDigitalOutput()   do { TRISBbits.TRISB1 = 0; } while(0)
#define LED5_SetPullup()          do { WPUBbits.WPUB1 = 1; } while(0)
#define LED5_ResetPullup()        do { WPUBbits.WPUB1 = 0; } while(0)
#define LED5_SetAnalogMode()      do { ANSELBbits.ANSB1 = 1; } while(0)
#define LED5_SetDigitalMode()     do { ANSELBbits.ANSB1 = 0; } while(0)

// get/set LED4 aliases
#define LED4_TRIS                 TRISBbits.TRISB2
#define LED4_LAT                  LATBbits.LATB2
#define LED4_PORT                 PORTBbits.RB2
#define LED4_WPU                  WPUBbits.WPUB2
#define LED4_ANS                  ANSELBbits.ANSB2
#define LED4_SetHigh()            do { LATBbits.LATB2 = 1; } while(0)
#define LED4_SetLow()             do { LATBbits.LATB2 = 0; } while(0)
#define LED4_Toggle()             do { LATBbits.LATB2 = ~LATBbits.LATB2; } while(0)
#define LED4_GetValue()           PORTBbits.RB2
#define LED4_SetDigitalInput()    do { TRISBbits.TRISB2 = 1; } while(0)
#define LED4_SetDigitalOutput()   do { TRISBbits.TRISB2 = 0; } while(0)
#define LED4_SetPullup()          do { WPUBbits.WPUB2 = 1; } while(0)
#define LED4_ResetPullup()        do { WPUBbits.WPUB2 = 0; } while(0)
#define LED4_SetAnalogMode()      do { ANSELBbits.ANSB2 = 1; } while(0)
#define LED4_SetDigitalMode()     do { ANSELBbits.ANSB2 = 0; } while(0)

// get/set LED3 aliases
#define LED3_TRIS                 TRISBbits.TRISB3
#define LED3_LAT                  LATBbits.LATB3
#define LED3_PORT                 PORTBbits.RB3
#define LED3_WPU                  WPUBbits.WPUB3
#define LED3_ANS                  ANSELBbits.ANSB3
#define LED3_SetHigh()            do { LATBbits.LATB3 = 1; } while(0)
#define LED3_SetLow()             do { LATBbits.LATB3 = 0; } while(0)
#define LED3_Toggle()             do { LATBbits.LATB3 = ~LATBbits.LATB3; } while(0)
#define LED3_GetValue()           PORTBbits.RB3
#define LED3_SetDigitalInput()    do { TRISBbits.TRISB3 = 1; } while(0)
#define LED3_SetDigitalOutput()   do { TRISBbits.TRISB3 = 0; } while(0)
#define LED3_SetPullup()          do { WPUBbits.WPUB3 = 1; } while(0)
#define LED3_ResetPullup()        do { WPUBbits.WPUB3 = 0; } while(0)
#define LED3_SetAnalogMode()      do { ANSELBbits.ANSB3 = 1; } while(0)
#define LED3_SetDigitalMode()     do { ANSELBbits.ANSB3 = 0; } while(0)

// get/set LED2 aliases
#define LED2_TRIS                 TRISBbits.TRISB4
#define LED2_LAT                  LATBbits.LATB4
#define LED2_PORT                 PORTBbits.RB4
#define LED2_WPU                  WPUBbits.WPUB4
#define LED2_ANS                  ANSELBbits.ANSB4
#define LED2_SetHigh()            do { LATBbits.LATB4 = 1; } while(0)
#define LED2_SetLow()             do { LATBbits.LATB4 = 0; } while(0)
#define LED2_Toggle()             do { LATBbits.LATB4 = ~LATBbits.LATB4; } while(0)
#define LED2_GetValue()           PORTBbits.RB4
#define LED2_SetDigitalInput()    do { TRISBbits.TRISB4 = 1; } while(0)
#define LED2_SetDigitalOutput()   do { TRISBbits.TRISB4 = 0; } while(0)
#define LED2_SetPullup()          do { WPUBbits.WPUB4 = 1; } while(0)
#define LED2_ResetPullup()        do { WPUBbits.WPUB4 = 0; } while(0)
#define LED2_SetAnalogMode()      do { ANSELBbits.ANSB4 = 1; } while(0)
#define LED2_SetDigitalMode()     do { ANSELBbits.ANSB4 = 0; } while(0)

// get/set LED1 aliases
#define LED1_TRIS                 TRISBbits.TRISB5
#define LED1_LAT                  LATBbits.LATB5
#define LED1_PORT                 PORTBbits.RB5
#define LED1_WPU                  WPUBbits.WPUB5
#define LED1_ANS                  ANSELBbits.ANSB5
#define LED1_SetHigh()            do { LATBbits.LATB5 = 1; } while(0)
#define LED1_SetLow()             do { LATBbits.LATB5 = 0; } while(0)
#define LED1_Toggle()             do { LATBbits.LATB5 = ~LATBbits.LATB5; } while(0)
#define LED1_GetValue()           PORTBbits.RB5
#define LED1_SetDigitalInput()    do { TRISBbits.TRISB5 = 1; } while(0)
#define LED1_SetDigitalOutput()   do { TRISBbits.TRISB5 = 0; } while(0)
#define LED1_SetPullup()          do { WPUBbits.WPUB5 = 1; } while(0)
#define LED1_ResetPullup()        do { WPUBbits.WPUB5 = 0; } while(0)
#define LED1_SetAnalogMode()      do { ANSELBbits.ANSB5 = 1; } while(0)
#define LED1_SetDigitalMode()     do { ANSELBbits.ANSB5 = 0; } while(0)

// get/set SW6 aliases
#define SW6_TRIS                 TRISCbits.TRISC3
#define SW6_LAT                  LATCbits.LATC3
#define SW6_PORT                 PORTCbits.RC3
#define SW6_SetHigh()            do { LATCbits.LATC3 = 1; } while(0)
#define SW6_SetLow()             do { LATCbits.LATC3 = 0; } while(0)
#define SW6_Toggle()             do { LATCbits.LATC3 = ~LATCbits.LATC3; } while(0)
#define SW6_GetValue()           PORTCbits.RC3
#define SW6_SetDigitalInput()    do { TRISCbits.TRISC3 = 1; } while(0)
#define SW6_SetDigitalOutput()   do { TRISCbits.TRISC3 = 0; } while(0)

// get/set RC6 procedures
#define RC6_SetHigh()            do { LATCbits.LATC6 = 1; } while(0)
#define RC6_SetLow()             do { LATCbits.LATC6 = 0; } while(0)
#define RC6_Toggle()             do { LATCbits.LATC6 = ~LATCbits.LATC6; } while(0)
#define RC6_GetValue()              PORTCbits.RC6
#define RC6_SetDigitalInput()    do { TRISCbits.TRISC6 = 1; } while(0)
#define RC6_SetDigitalOutput()   do { TRISCbits.TRISC6 = 0; } while(0)

/**
   @Param
    none
   @Returns
    none
   @Description
    GPIO and peripheral I/O initialization
   @Example
    PIN_MANAGER_Initialize();
 */
void PIN_MANAGER_Initialize (void);

/**
 * @Param
    none
 * @Returns
    none
 * @Description
    Interrupt on Change Handling routine
 * @Example
    PIN_MANAGER_IOC();
 */
void PIN_MANAGER_IOC(void);



#endif // PIN_MANAGER_H
/**
 End of File
*/