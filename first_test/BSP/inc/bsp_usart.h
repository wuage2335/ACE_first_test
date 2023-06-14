#ifndef __BSP_USART_H
#define __BSP_USART_H

#include "stm32f10x.h"
#include "struct_typedef.h" 

void usart_config(void);
void usart_send_dma_init(uint32_t paddr, uint32_t maddr, uint32_t len);
void usart_receive_dma_init(uint32_t paddr, uint32_t maddr, uint32_t len);


#endif