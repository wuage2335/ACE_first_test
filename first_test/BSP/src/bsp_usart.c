#include "bsp_usart.h"
#include "realize.h"

void Usart_GPIO_Config(void);
void Usart1_Configuration(void);
void Usart2_Configuration(void);

void usart_config(void)
{
		Usart_GPIO_Config();
		Usart1_Configuration();
		Usart2_Configuration();
}

void Usart_GPIO_Config(void)
{
    GPIO_InitTypeDef GPIO_InitStructure;

    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);
	
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_9;
    GPIO_Init(GPIOA, &GPIO_InitStructure);
		GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_3;

    GPIO_Init(GPIOA, &GPIO_InitStructure);	
}

void Usart1_Configuration(void)
{
    USART_InitTypeDef USART_InitStruct;

		RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART1, ENABLE);

    USART_InitStruct.USART_BaudRate = 9600;                  
    USART_InitStruct.USART_WordLength = USART_WordLength_8b;    
    USART_InitStruct.USART_StopBits = USART_StopBits_1;          
    USART_InitStruct.USART_Parity = USART_Parity_No;               
    USART_InitStruct.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
    USART_InitStruct.USART_Mode = USART_Mode_Tx;       
    USART_Init(USART1, &USART_InitStruct);
  
    USART_Cmd(USART1, ENABLE);
}

void Usart2_Configuration(void)
{
    USART_InitTypeDef USART_InitStruct;

		RCC_APB1PeriphClockCmd(RCC_APB1Periph_USART2, ENABLE);

    USART_InitStruct.USART_BaudRate = 9600;
		USART_InitStruct.USART_WordLength = USART_WordLength_8b;
    USART_InitStruct.USART_StopBits = USART_StopBits_1;
    USART_InitStruct.USART_Parity = USART_Parity_No;
    USART_InitStruct.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
    USART_InitStruct.USART_Mode = USART_Mode_Rx;
    USART_Init(USART2, &USART_InitStruct);
  
    USART_Cmd(USART2, ENABLE);
    USART_ITConfig(USART2, USART_IT_TC, DISABLE);
    USART_ITConfig(USART2, USART_IT_RXNE, ENABLE);
    USART_ITConfig(USART2, USART_IT_IDLE, ENABLE);	
}

void usart_send_dma_init(uint32_t paddr, uint32_t maddr, uint32_t len)
{
			DMA_Cmd(DMA1_Channel4,DISABLE); 
      DMA_InitTypeDef dma_init_struct;
      RCC_AHBPeriphClockCmd(RCC_AHBPeriph_DMA1, ENABLE);                
      dma_init_struct.DMA_PeripheralBaseAddr = paddr;
      dma_init_struct.DMA_MemoryBaseAddr = maddr;
      dma_init_struct.DMA_DIR = DMA_DIR_PeripheralDST;                   //????????
      dma_init_struct.DMA_BufferSize = len;      //????????????
      dma_init_struct.DMA_PeripheralInc = DMA_PeripheralInc_Disable; //????????,??????DR??
      dma_init_struct.DMA_MemoryInc = DMA_MemoryInc_Enable;
      dma_init_struct.DMA_PeripheralDataSize = DMA_PeripheralDataSize_Byte;
      dma_init_struct.DMA_MemoryDataSize = DMA_MemoryDataSize_Byte;
      dma_init_struct.DMA_Mode = DMA_Mode_Normal;                         //dma???NOMAL??
      dma_init_struct.DMA_Priority = DMA_Priority_Medium;                   //dma?????
      dma_init_struct.DMA_M2M = DMA_M2M_Disable;                          //??????????,?????
      DMA_Init(DMA1_Channel4, &dma_init_struct);   
      DMA_Cmd(DMA1_Channel4, ENABLE);                                         //??DMA??,?????,DMA1??4????
			USART_DMACmd(USART1,USART_DMAReq_Tx,ENABLE);
}

void usart_receive_dma_init(uint32_t paddr, uint32_t maddr, uint32_t len)
{
			DMA_Cmd(DMA1_Channel6,DISABLE); 
      DMA_InitTypeDef dma_init_struct;
      RCC_AHBPeriphClockCmd(RCC_AHBPeriph_DMA1, ENABLE);                
      dma_init_struct.DMA_PeripheralBaseAddr = paddr;
      dma_init_struct.DMA_MemoryBaseAddr = maddr;
      dma_init_struct.DMA_DIR = DMA_DIR_PeripheralSRC;                   //????????
      dma_init_struct.DMA_BufferSize = len;      //????????????
      dma_init_struct.DMA_PeripheralInc = DMA_PeripheralInc_Disable; //????????,??????DR??
      dma_init_struct.DMA_MemoryInc = DMA_MemoryInc_Enable;
      dma_init_struct.DMA_PeripheralDataSize = DMA_PeripheralDataSize_Byte;
      dma_init_struct.DMA_MemoryDataSize = DMA_MemoryDataSize_Byte;
      dma_init_struct.DMA_Mode = DMA_Mode_Normal;                         //dma???NOMAL??
      dma_init_struct.DMA_Priority = DMA_Priority_High;                   //dma?????
      dma_init_struct.DMA_M2M = DMA_M2M_Disable;
      DMA_Init(DMA1_Channel6, &dma_init_struct);   
      DMA_Cmd(DMA1_Channel6, ENABLE);    	//??DMA??,?????,DMA1??4????
			USART_DMACmd(USART2, USART_DMAReq_Rx, ENABLE); 
}


