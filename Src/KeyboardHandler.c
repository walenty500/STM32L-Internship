/*
 * KeyboardHandler.c
 *
 *  Created on: Jul 14, 2021
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



TimeStamp_type Keyboard;
uint32_t KeyboardCycleTime;

uint8_t ReadPin;
uint8_t PreviousPin;
uint8_t NewKeyFlag;

void KeyboardHandlerInit()
{
	{
		Keyboard.Handler=&ReadKeyboard;
		KeyboardCycleTime=10;

		ReadPin=0;
		PreviousPin=0;
		NewKeyFlag=0;

	}

}

void AddReadKeyboardCycle(uint32_t cycle_time)
{
	KeyboardCycleTime=cycle_time;
	AddTimestamp(&Keyboard,KeyboardCycleTime);
}

void ReadKeyboard()
{
	ReadPin=ReadPin<<1;
	ReadPin+=HAL_GPIO_ReadPin(B1_GPIO_Port,B1_Pin);
	ReadPin=ReadPin&7;
	if(ReadPin==7)
	{
		if(PreviousPin==0)
		{
			PreviousPin=1;
			NewKeyFlag=1;

		}
	}
	if(ReadPin==0)
	{
		if(PreviousPin==1)
		{
			PreviousPin=0;
		}
	}
	AddTimestamp(&Keyboard,KeyboardCycleTime);
}

uint8_t TestKeyboard()
{
	if(NewKeyFlag==0)
	{
		return 0;
	}
	if(NewKeyFlag==1)
	{
		NewKeyFlag=0;
		KeyboardAction();
		return 1;
	}
	return 0;
}



// Zapasowe funkcje czytania klawiatury działające ale nie polecane do użytku

////Flaga ustawiana przy przerwaniu
//uint8_t KeyboardITFlag;
////Pamięć odczytanych co 10 ms przycisków
//uint8_t KeyboardMemory[3];
////index pamięci
//uint8_t KeyboardMem_id;
////zmienna służąca do badania zawartości pamięci po 3 odczytaniach
//uint8_t Check_Key;
////odczytany klawisz
//uint8_t returned_key;


//void ReadKeyboard2()
//{
//	//odczytanie stanu pina do pamięci
//	KeyboardMemory[KeyboardMem_id]=HAL_GPIO_ReadPin(B1_GPIO_Port,B1_Pin);
//
//	//inkrementacja zmiennej do sprawdzania pamięci
//	Check_Key=KeyboardMem_id+1;
//
//	//inkrementacja indeksu
//	KeyboardMem_id=Check_Key%3;
//
//	//jeżeli Check_Key == 3 to sprawdzamy zawartosc pamieci
//	//bo odczytalismy juz 3 razy
//	if(Check_Key>=3)
//	{
////		if(KeyboardMemory[0]==KeyboardMemory[1] && KeyboardMemory[1]==KeyboardMemory[2])
//		if(KeyboardMemory[0]==1 && KeyboardMemory[1]==1 &&  KeyboardMemory[2]==1)
//		{
//			//obsluga klawiatury (włączenie LED'a) oraz czyszczenie zmiennych
//			// można zrobić osobną funkcję KeyboardHandle();
//			LedBlueON_OF();
//			returned_key=1;
//			Check_Key=0;
//			KeyboardMem_id=0;
//			KeyboardMemory[0]=0;
//			KeyboardMemory[1]=0;
//			KeyboardMemory[2]=0;
//
//		}
//		//		else
//		//		{
//		//			//jeżeli nie odczytalismy 3 takich samych, to czytamy następne
//		//			//mozliwe ze tutaj poprostu nic nie mamy robić (?)
//		//				AddTimestamp(&Keyboard,KeyboardCycleTime);
//		//		}
//	}
//	else
//	{
//		//jeżeli jeszcze nie przeczytaliśmy klawiatury 3 razy, to czytamy dalej
//		AddTimestamp(&Keyboard,KeyboardCycleTime);
//	}
//}
//
//uint8_t HandleKeyboard()
//{
//	//jeżeli przyszła flaga informujaca o wciśnięciu przycisku
//	if(KeyboardITFlag)
//	{
//		//zerujemy flagę i odczytujemy klawiaturę
//		KeyboardITFlag=0;
//		ReadKeyboard();
//	}
//	//zwracamy ustawiony przez ReadKeyboard() klawisz
//	uint8_t lcl_return=returned_key;
//
//	//i zerujemy żeby pętla główna się nie zacięła
//	returned_key=0;
//
//	return lcl_return;
//}
//
//
//void SetKeyboardFlag()
//{
//	KeyboardITFlag=1;
//}

