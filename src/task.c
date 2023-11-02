/*
 * task.c
 *
 *  Created on: 22-Aug-2023
 *      Author: TRIOX
 */

#include "r_smc_entry.h"
#include <string.h>
#include "Config_SCI1.h"
#include <stdint.h>
#include <stdbool.h>
#include <stdlib.h>

volatile int clock_100us ;                           /* Flag activated each mili second    */

void delay_100us(unsigned short val)
{
	unsigned short i = 0;

	R_Config_CMT0_Start(); 	// Generate interrupt each 1 ms
	for(i = 0; i < val; i++)
	{
		while (!clock_100us);
		{
		  clock_100us = 0;
		}
	}
	R_Config_CMT0_Stop();
}

void task(void);

void task (void)
{
	 R_Config_SCI1_Create();
	 R_Config_SCI1_Start();


	 static uint8_t *response;
	 uint8_t *AT[] = {
	     "AT\r",
	     "ATI\r",
	     "ATE=0\r",
	     "AT+BDADDR\r",
	     "AT+PIN=123456\r",
	     "AT+GAPSTATUS\r",
	     "AT+BAUD\r",
	     "AT+BINREQ\r",
//	     "+++",
	     NULL
 };

	 for (int i = 0; AT[i] != NULL; i++)
	 {
	     // Send AT command
		 R_Config_SCI1_Serial_Send( AT[i], strlen(AT[i]) );
		 response[0] = 0x00;
		 response[1] = 0x00;

		 // Read and process response
		  int bytes_read = R_Config_SCI1_Serial_Receive( response ,10);
		  if (bytes_read > 0)
		  {

		   if (response == "OK\r\n")
			 {
			   continue;
			 }
		  }

	          delay_100us(1000);
	     }

}


void commandmode (void);

void commandmode (void)
{
	 R_Config_SCI1_Create();
	 R_Config_SCI1_Start();


	 uint8_t *AT = "+++";
	 uint8_t *response;

	 R_Config_SCI1_Serial_Send( AT, strlen(AT) );
	 response[0] = 0x00;
	 response[1] = 0x00;

	 while(1){

		 R_Config_SCI1_Serial_Receive( response ,10);

		 if(strlen(response)>=2)
		 {
		  R_Config_SCI1_Serial_Send( AT, strlen(AT) );
		  response[0] = 0x00;
		  response[1] = 0x00;
		 }
              }
}

void communicate (void);

void communicate (void)
{
	 R_Config_SCI1_Create();
	 R_Config_SCI1_Start();


	 uint8_t *AT = "hello triox\r\n";
	 uint8_t *response;

	 R_Config_SCI1_Serial_Send( AT, strlen(AT) );
	 response[0] = 0x00;
	 response[1] = 0x00;

}
