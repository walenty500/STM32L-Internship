/*
 * kontrolauart.h
 *
 *  Created on: Jul 5, 2021
 *      Author: Krzysiek
 */

#ifndef INC_KONTROLAUART_H_
#define INC_KONTROLAUART_H_

#include "stdint.h"

#define MY_BUFOR_BUFSIZE 100



void putCharRx(uint8_t);
void putCharTx(uint8_t,uint8_t*);
uint8_t sizeofRX();
uint8_t sizeofTx();
uint8_t getCharRX();
uint8_t getCharTX();

#endif /* INC_KONTROLAUART_H_ */
