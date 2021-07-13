/*
 * obslugaOdbierania.c
 *
 *  Created on: 7 lip 2021
 *      Author: Krzysiek
 */
#include <obslugaUART.h>
#include "kontrolauart.h"
#include "stdint.h"
#include "usart.h"

	uint8_t dataBufor[MY_BUFOR_BUFSIZE];

void handleData()
{
	uint8_t dataInRxBuf=sizeofRX();
	uint8_t data=0;
	getCharRX(dataInRxBuf,dataBufor);
	putCharTx(dataInRxBuf,dataBufor);
	uint8_t dataInTxBuf=sizeofTx();
	if(dataInTxBuf!=0)
	{
		getCharTX(1,&data);
		HAL_UART_Transmit_IT(&huart1, &data, 1);
	}

}
