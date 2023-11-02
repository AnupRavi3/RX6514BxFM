/*
 * trx65.h
 *
 *  Created on: 19-Aug-2023
 *      Author: Dell
 */

#ifndef TRX65_H_
#define TRX65_H_

volatile int clock_100us ;

void delay_100us(unsigned short val);
void task(void);
void command(void);

#endif /* TRX65_H_ */
