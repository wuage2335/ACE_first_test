#include "bsp_tim.h"
#include "stm32f10x.h"

void TIM2_init(void);


void TIM_config(void)
{
		TIM2_init();
}

void TIM2_init(void)
{
    TIM_TimeBaseInitTypeDef TIM_TimeBaseStructure;
    TIM_OCInitTypeDef TIM_OCInitStructure;

    RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2, ENABLE);

    TIM_TimeBaseStructure.TIM_Prescaler = 7200 - 1;
    TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;
    TIM_TimeBaseStructure.TIM_Period = 10000 - 1;
    TIM_TimeBaseStructure.TIM_ClockDivision = 0;
    TIM_TimeBaseStructure.TIM_RepetitionCounter = 0;

		TIM_TimeBaseInit(TIM2, &TIM_TimeBaseStructure);

    TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM1;
    TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;
    TIM_OCInitStructure.TIM_OutputNState = TIM_OutputNState_Disable;
    TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_High;
    TIM_OCInitStructure.TIM_OCNPolarity = TIM_OCNPolarity_Low;
    TIM_OCInitStructure.TIM_OCIdleState = TIM_OCIdleState_Reset;
    TIM_OCInitStructure.TIM_OCNIdleState = TIM_OCNIdleState_Reset;

		TIM_OC3Init(TIM2, &TIM_OCInitStructure);
    TIM_OC3PreloadConfig(TIM2, TIM_OCPreload_Enable);
    TIM_ARRPreloadConfig(TIM2, ENABLE);
		TIM_Cmd(TIM2,DISABLE);
}

void breath_light(uint8_t v)
{
		uint8_t j = 0;
    if(v)
    {
        for(int i = 0; i <= 500; i++)
        {
            TIM_SetCompare3(TIM2,i);
						if(USART_GetITStatus(USART2, USART_IT_RXNE) != RESET)
						{
							USART_ClearITPendingBit(USART2, USART_IT_RXNE);				
							return ;
						}				
        }
    }
    else
    {
        for(int i = 500; i >= 0; i--)
        {
            TIM_SetCompare3(TIM2,i);
						if(USART_GetITStatus(USART2, USART_IT_RXNE) != RESET)
						{
							USART_ClearITPendingBit(USART2, USART_IT_RXNE);				
							return ;
						}
        }
    }
}