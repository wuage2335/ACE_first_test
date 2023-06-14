#include "realize.h"

uint8_t ch[3] = {'A','C','E'};
uint8_t ch_1[10] = {0};

void bsp_config(void)
{
		TIM_config();
		usart_config();
}


void function_realize(void)
{
		static uint8_t v = 0;
		usart_send_dma_init(USART1_DR__ADDRESS,(u32)ch,3);
		usart_receive_dma_init(USART2_DR__ADDRESS,(u32)ch_1,1);
		v = ~v;
		breath_light(v);
		
		while(1)
		{
			if( (TIM2->CNT == 9999) || (USART_GetITStatus(USART2, USART_IT_RXNE) != RESET))
			{
					TIM2->CNT = 0;
					TIM_Cmd(TIM2,DISABLE);
					USART_ClearFlag(USART2, USART_IT_RXNE);				
					return ;
			}
		}	
}