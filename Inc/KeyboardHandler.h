/*
 * KeyboardHandler.h
 *
 *  Created on: Jul 14, 2021
 *      Author: Krzysiek
 */

#ifndef INC_KEYBOARDHANDLER_H_
#define INC_KEYBOARDHANDLER_H_


void AddReadKeyboardCycle(uint32_t);
void ReadKeyboard();
//void ReadKeyboard2();
void SetKeyboardFlag();
uint8_t TestKeyboard();
void KeyboardHandlerInit();
//uint8_t HandleKeyboard();
#endif /* INC_KEYBOARDHANDLER_H_ */
