#include "realize.h"

 int main(void)
 {
		bsp_config();
	 
		while (1)
		{
			TIM_Cmd(TIM2,ENABLE);
			function_realize();
		}
 }
