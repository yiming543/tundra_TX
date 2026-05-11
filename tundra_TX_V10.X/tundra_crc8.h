
/* 
 * File:  turndra_crc8.c
 * Author: T00904
 * Comments: CRC8 calculation function
 * Revision history: V1.0 May 11, 2026
 */

// This is a guard condition so that contents of this file are not included
// more than once.  
#ifndef TUNDRA_CRC8_H
#define	TUNDRA_CRC8_H

#include <stdint.h>

extern uint8_t calculate_crc8_real(const uint8_t *data, uint8_t length);



#endif	/* TUNDRA_CRC8_H */

