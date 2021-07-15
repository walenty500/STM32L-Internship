/*
 * TSFunctions.h
 *
 *  Created on: 14 lip 2021
 *      Author: Krzysiek
 */

#ifndef INC_CYCLELED_H_
#define INC_CYCLELED_H_

#include "stdint.h"

typedef enum
{
	greenLed = 0,
	blueLed = 1
}LedType;

void CycleLedInit();
void AddLedCycle(LedType,uint32_t);
void ToggleLedGreen();
void ToggleLedBlue();
void LedBlueON_OF();
void ReadKeyboard();
void SetKeyboardFlag();

#endif /* INC_CYCLELED_H_ */
