/*
 * kontrolauart.c
 *
 *  Created on: Jul 5, 2021
 *      Author: Krzysiek
 */
#include "kontrolauart.h"
#include "stdint.h"
#include "usart.h"

	uint8_t UART_Rx_cyclic_bufor[MY_BUFOR_BUFSIZE];
	uint8_t *Rx_writing_ptr=UART_Rx_cyclic_bufor;
	uint8_t *Rx_reading_ptr=UART_Rx_cyclic_bufor;

	uint8_t UART_Tx_cyclic_bufor[MY_BUFOR_BUFSIZE];
	uint8_t *Tx_writing_ptr=UART_Tx_cyclic_bufor;
	uint8_t *Tx_reading_ptr=UART_Tx_cyclic_bufor;


void putCharRx(uint8_t rcvd_byte)
{
	uint8_t *lcl_w_ptr=Rx_writing_ptr;

	lcl_w_ptr++;

	if(lcl_w_ptr>=UART_Rx_cyclic_bufor+MY_BUFOR_BUFSIZE)
	{
		lcl_w_ptr=UART_Rx_cyclic_bufor;
	}
	if(lcl_w_ptr!=Rx_reading_ptr)
	{
		*lcl_w_ptr=rcvd_byte;
		Rx_writing_ptr=lcl_w_ptr;
	}

//	__HAL_UART_ENABLE_IT(&huart1, UART_IT_RXNE);

}

void putCharTx(uint8_t licznik, uint8_t* array)
{
	uint8_t *lcl_w_ptr=Tx_writing_ptr;

	for(int i=0;i<licznik;i++)
	{
		lcl_w_ptr++;

		if(lcl_w_ptr>=UART_Tx_cyclic_bufor+MY_BUFOR_BUFSIZE)
		{
			lcl_w_ptr=UART_Tx_cyclic_bufor;
		}
		if(lcl_w_ptr!=Tx_reading_ptr)
		{
			*lcl_w_ptr=*array;
			array++;
			Tx_writing_ptr=lcl_w_ptr;
		}
	}
	__HAL_UART_ENABLE_IT(&huart1, UART_IT_TXE);
}

uint8_t sizeofRX()
{

		uint8_t *lcl_w_ptr=Rx_writing_ptr;
		uint8_t*lcl_r_ptr=Rx_reading_ptr;


	if(lcl_w_ptr>=lcl_r_ptr)
	{
		return lcl_w_ptr-lcl_r_ptr;
	}
	else
	{
		uint8_t size=lcl_w_ptr-lcl_r_ptr+MY_BUFOR_BUFSIZE;

		return size;
	}
}

uint8_t sizeofTx()
{
	uint8_t *lcl_w_ptr=Tx_writing_ptr;
	uint8_t*lcl_r_ptr=Tx_reading_ptr;


if(lcl_w_ptr>=lcl_r_ptr)
{
	return lcl_w_ptr-lcl_r_ptr;
}
else
{

	uint8_t size=lcl_w_ptr-lcl_r_ptr+MY_BUFOR_BUFSIZE;


	return size;
}
}


uint8_t getCharRX()
{
	uint8_t *lcl_r_ptr=Rx_reading_ptr;
//	uint8_t actual_size=sizeofRX();
	uint8_t zwrot=0;

		lcl_r_ptr++;
			if(lcl_r_ptr>=UART_Rx_cyclic_bufor+MY_BUFOR_BUFSIZE)
			{
				lcl_r_ptr=UART_Rx_cyclic_bufor;
			}
		zwrot=*lcl_r_ptr;
//		array++;
		Rx_reading_ptr=lcl_r_ptr;
		return zwrot;

}



uint8_t getCharTX()
{
	uint8_t *lcl_r_ptr=Tx_reading_ptr;
	uint8_t zwrot=0;

			lcl_r_ptr++;
				if(lcl_r_ptr>=UART_Tx_cyclic_bufor+MY_BUFOR_BUFSIZE)
				{
					lcl_r_ptr=UART_Tx_cyclic_bufor;
				}
			zwrot=*lcl_r_ptr;
			Tx_reading_ptr=lcl_r_ptr;
		return zwrot;
}


