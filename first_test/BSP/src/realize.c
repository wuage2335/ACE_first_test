#include "realize.h"

uint8_t ch[3] = {'A','C','E'};
uint8_t ch_1[10] = {0};
uint8_t ch_2[2] = {0};

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
		//breath_light(v);
	if(ch_1[0] == 0x0f || ch_1[0] == 0xff || ch_1[0] ==  0xf0)
			ch_2[0] = ch_1[0];
		while(1)
		{
			if( (TIM2->CNT == 9999) || (USART_GetITStatus(USART2, USART_IT_RXNE) != RESET))
			{
					if(ch_2[0] == 0x0f || ch_2[0] == 0xff || ch_2[0] ==  0xf0)
							GPIO_ResetBits(GPIOC,GPIO_Pin_13);
					else
							GPIO_SetBits(GPIOC,GPIO_Pin_13);
					
					TIM_Cmd(TIM2,DISABLE);
					USART_ClearFlag(USART2, USART_IT_RXNE);				
					return ;
			}
		}	
}