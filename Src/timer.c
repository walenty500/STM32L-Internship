/*
 * timer.c
 *
 *  Created on: Jul 9, 2021
 *      Author: Krzysiek
 */

#include "stdint.h"
#include "timer.h"
#include <stdio.h>
#include<stdlib.h>

TimeStamp_type *head;
volatile uint32_t TS_counter;
//	TimeStamp_type* head=NULL;

void AddTimestamp(TimeStamp_type* new_TimeStamp,uint32_t timeOut_value)
{
	//lokalna wartość timeOutu TimeStamp'a do wstawienia
	uint32_t local_value=timeOut_value;

	//nowy timeuot na początku wskazuje NULL
	new_TimeStamp->next=NULL;

	//wskaznik na wskaźnik wskazujący na nastepny TimeStamp
	TimeStamp_type **current_TimeStamp=&head;

	//jeżeli lista jest pusta, dodajemy na początku
	if(head==NULL)
	{
		new_TimeStamp->timeOut=local_value;
		*current_TimeStamp=new_TimeStamp;
	}
	else
	{
		//jak nie to przechodzimy przez listę do momentu wykrycia NULL
		//oraz dopóki nie znajdziemy mniejszej wartości niż ta którą
		//chcemy dodac
		while((*current_TimeStamp)!=NULL && (*current_TimeStamp)->timeOut<local_value)
		{
			local_value-=(*current_TimeStamp)->timeOut;
			current_TimeStamp=&((*current_TimeStamp)->next);
		}

		//update wartosc
		new_TimeStamp->timeOut=local_value;

		//new -> next (tam gdzie wskazuje wskaznik)
		new_TimeStamp->next=*current_TimeStamp;

		//prev (wartosc obiektu) -> new
		*current_TimeStamp=new_TimeStamp;

		//przejscie do nastepnego elementu
		current_TimeStamp=&((*current_TimeStamp)->next);

		//uaktualnienie wartosci timeOuta nastepnego elementu
		(*current_TimeStamp)->timeOut-=local_value;

	}
}

void Del_First_TimeStamp()
{
	//wskaznik na wskaźnik wskazujący na nastepny TimeStamp
	TimeStamp_type **current_TimeStamp=&head;

	//przejscie do nastepnego elementu
	*current_TimeStamp=(*current_TimeStamp)->next;

}

uint8_t UpdateTimeStamp()
{
	//wskaznik na wskaźnik wskazujący na aktualny TimeStamp
	TimeStamp_type **current_TimeStamp=&head;

	TimeStamp_type *temp_TS;
	//zmienna mowiaca o wykonaniu pierwszego TimeStampa
	uint8_t first_TS_executed=0;

	//czy ten while w moim przypadku musi tutaj być
	//chyba tak, żeby jak w trakcie wykonywania przyjdzie przerwanie z inkrementacją counter'a
	//to żeby potem się cały while w mainie nie wykonywał (?)
	while(TS_counter)
	{
		//lokalna wartosc pierwszego timeOuta z listy
		uint32_t lcl_TimeOut= (*current_TimeStamp)->timeOut;

		if(TS_counter<lcl_TimeOut)
		{
			//tylko odejmujemy TS_counter
			(*current_TimeStamp)->timeOut-=TS_counter;
			TS_counter-=TS_counter;
		}
		else
		{
			//odejmujemy tylko timeOut
			(*current_TimeStamp)->timeOut-=lcl_TimeOut;
			TS_counter-=lcl_TimeOut;

			temp_TS=(*current_TimeStamp);

			//usuwamy pierwszy element z listy
			Del_First_TimeStamp();

			//obsluga funkcji
			temp_TS->Handler();


			//ustawiamy zmienna mowiaca o wykonaniu pierwszego TimeStampa na 1
			first_TS_executed=1;
			return first_TS_executed;
		}

	}

	return first_TS_executed;

}

void DelTimeStamp(TimeStamp_type* TimeStamp_addr)
{
	//wskaznik na wskaźnik wskazujący na aktualny TimeStamp
	TimeStamp_type **current_TimeStamp=&head;

	//jeżeli aktualny to nie NULL
	while((*current_TimeStamp)!=NULL)
	{
		//sprawdzamy czy aktualny to ten co chcemy usunąć
		if((*current_TimeStamp)==TimeStamp_addr)
		{
			//jak tak to zapisujemy jego timeOut
			uint32_t deleted_value=(*current_TimeStamp)->timeOut;

			//ustawiamy wskaźnik na aktualny, żeby wskazywał na następny
			(*current_TimeStamp)=(*current_TimeStamp)->next;

			//jeżeli teraz nie jesteśmy w ostatnim elemencie listy
			if((*current_TimeStamp)!=NULL)
			{
				//dodajemy wartość usuniętego timeOuta do aktualnego
				(*current_TimeStamp)->timeOut+=deleted_value;
			}
			break;
		}
		else
		{
			//jeżeli aktualny to nie ten co chcemy usunąć, to przechodzimy do nastepnego
			current_TimeStamp=&((*current_TimeStamp)->next);
		}
	}

}

void IncrementTSCounter()
{
	TS_counter++;
}






//void AddTimestampFunc(TimeStamp_type* new_TimeStamp, uint32_t timeOut_value, void (*func)())
//{
//	//lokalna wartość timeOutu TimeStamp'a do wstawienia
//	uint32_t local_value=timeOut_value;
//
//	//nowy timeuot na początku wskazuje NULL
//	new_TimeStamp->next=NULL;
//
//	new_TimeStamp->Handler=func;
//
//	//wskaznik na wskaźnik wskazujący na nastepny TimeStamp
//	TimeStamp_type **current_TimeStamp=&head;
//
//	//jeżeli lista jest pusta, dodajemy na początku
//	if(head==NULL)
//	{
//		new_TimeStamp->timeOut=local_value;
//		*current_TimeStamp=new_TimeStamp;
//	}
//	else
//	{
//		//jak nie to przechodzimy przez listę do momentu wykrycia NULL
//		//oraz dopóki nie znajdziemy mniejszej wartości niż ta którą
//		//chcemy dodac
//		while((*current_TimeStamp)!=NULL && (*current_TimeStamp)->timeOut<local_value)
//		{
//			local_value-=(*current_TimeStamp)->timeOut;
//			current_TimeStamp=&((*current_TimeStamp)->next);
//		}
//
//		//update wartosc
//		new_TimeStamp->timeOut=local_value;
//
//		//new -> next (tam gdzie wskazuje wskaznik)
//		new_TimeStamp->next=*current_TimeStamp;
//
//		//prev (wartosc obiektu) -> new
//		*current_TimeStamp=new_TimeStamp;
//
//		//przejscie do nastepnego elementu
//		current_TimeStamp=&((*current_TimeStamp)->next);
//
//			(*current_TimeStamp)->timeOut-=local_value;
//
//	}
//}
