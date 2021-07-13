/*
 * timer.h
 *
 *  Created on: Jul 9, 2021
 *      Author: Krzysiek
 */

#ifndef INC_TIMER_H_
#define INC_TIMER_H_
#include "stdint.h"

typedef struct TimeStamp
{
	uint32_t timeOut;
	struct TimeStamp * next;
	void (*Handler)(void);
}TimeStamp_type;


////function declarations
void AddTimestamp(TimeStamp_type*,uint32_t);
//void AddTimestampFunc(TimeStamp_type*,uint32_t,void (*func)());
void DelTimeStamp(TimeStamp_type*);
void Del_First_TimeStamp();
uint8_t UpdateTimeStamp();
void DelTimeStamp(TimeStamp_type*);
void IncrementTSCounter();


#endif /* INC_TIMER_H_ */
