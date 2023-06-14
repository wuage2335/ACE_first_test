#ifndef __REALIZE_H
#define __REALIZE_H

#include "bsp_tim.h"
#include "bsp_usart.h"

#define USART1_DR__ADDRESS (USART1_BASE+0x04)
#define USART2_DR__ADDRESS (USART2_BASE+0x04)

void bsp_config(void);
void function_realize(void);


#endif