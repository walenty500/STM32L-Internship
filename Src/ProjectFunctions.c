/*
 * ProjectFunctions.c
 *
 *  Created on: Jul 15, 2021
 *      Author: Krzysiek
 */

#include <CycleLED.h>
#include "KeyboardHandler.h"
#include <ProjectFunctions.h>
#include <kontrolauart.h>
#include "stdint.h"
#include "timer.h"
#include "gpio.h"
#include <stdio.h>
#include <stdlib.h>

uint8_t message[] = "Hello World";
uint8_t rcvd_msg[13];

void KeyboardAction()
{
	uint8_t UARTFrame[13];
	uint8_t UARTFrame_size=sizeof(UARTFrame);

	uint8_t message_size=sizeof(message)-1;
	uint8_t parity=0;

	for(int i  = 0; i <= message_size; i++)
	{
		parity=(parity^message[i]);
		UARTFrame[i+1]=message[i];
	}

	UARTFrame[0]=message_size;
	parity=(parity^UARTFrame[0]);
	UARTFrame[12]=parity;

	LedBlueON_OF();
	putCharTx(UARTFrame_size, UARTFrame);


//	//ustawienie licznika
//	if(message_size>=10)
//	{
//		msg_size_b0=message_size/10;
//		msg_size_b1=message_size%10;
//	}
//	else
//	{
//		msg_size_b1=message_size;
//	}

	//parity check
}

uint8_t HandleRx()
{
	if(UART_FLAG_IDLE == 1)
	{
		if(sizeofRX()>2)
		{
			uint8_t clc_parity=0;
			uint8_t rcvd_parity=0;
			uint8_t size_of_msg=0;

			size_of_msg=getCharRX();
			clc_parity=(clc_parity^size_of_msg);
	//		size_of_msg*=10;
	//		size_of_msg+=getCharRX();

			for(int i=0; i<size_of_msg; i++)
			{
				rcvd_msg[i]=getCharRX();
				clc_parity=(clc_parity^rcvd_msg[i]);
			}
			rcvd_parity=getCharRX();
			if(rcvd_parity==clc_parity)
			{
				return 1;
			}
			else
			{
				return 0;
			}
		}
	}
	else
	{
		return 0;
	}
}
