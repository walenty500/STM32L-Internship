/*
 * TSfunctions.c
 *
 *  Created on: 14 lip 2021
 *      Author: Krzysiek
 */
#include <CycleLED.h>
#include "stdint.h"
#include "timer.h"
#include "gpio.h"
#include <stdio.h>
#include <stdlib.h>

TimeStamp_type Led[2];
uint32_t LedCycleTime[2];


void CycleLedInit()
{
	Led[0].Handler=&ToggleLedGreen;
	LedCycleTime[0]=500;
	Led[1].Handler=&ToggleLedBlue;
	LedCycleTime[1]=1000;
}

void AddLedCycle(LedType led_id,uint32_t cycle_time)
{
	LedCycleTime[led_id]=cycle_time;
	AddTimestamp(&Led[led_id],LedCycleTime[led_id]);
}

void ToggleLedGreen()
{
	HAL_GPIO_TogglePin(LD3_GPIO_Port,LD3_Pin);
	AddTimestamp(&Led[0],LedCycleTime[0]);
}

void ToggleLedBlue()
{
	HAL_GPIO_TogglePin(LD4_GPIO_Port,LD4_Pin);
	AddTimestamp(&Led[1],LedCycleTime[1]);
}

void LedBlueON_OF()
{
	HAL_GPIO_TogglePin(LD4_GPIO_Port,LD4_Pin);

}


