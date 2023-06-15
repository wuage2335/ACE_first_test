**谨记: 切勿眼高手低**

# 题目内容

你好，这是一个简单的关于stm32的小任务。可以练练手。

内容：使用**STM32任意开发板**官方固件库（标准固件库），每隔**一秒**通过**串口**向上位机发送“**ACE**”，并使一颗LED亮灭状态反转。串口接收到上位机任意数据后重新开始一秒钟的发送计时。

任务点：

1. 点亮一颗LED
2. 和上位机的串口通讯。
3. 精确计时一秒钟。

可选任务：

1. 使LED亮灭反转变为通过呼吸灯反转。

2. 使用DMA发送接收串口数据。


请于**六月十八号23:59**前，将你的整个项目内容打包成压缩包，文件命修改为你的名字，发送至邮箱 *** @outlook.com。邮箱主题为：软件first_test。

>  温馨提示：有任何问题或者不明白的地方，请及时在群聊中进行沟通。积极地进行沟通，是团队合作中重要的内容。如果你最近比较忙没时间弄可以跟我私聊。

----

## first_test

芯片: STM32f103c8t6

| 引脚使用 | 启用功能  |
| -------- | --------- |
| PA2      | TIM2_CH3  |
| PA9      | USART1_TX |
| PA3      | USART2_RX |

DMA使用:

| 启用外设  | DMA通道  |
| --------- | -------- |
| USART1_TX | DMA1_CH4 |
| USART2_RX | DMA1_CH5 |

---

main函数中的GPIO_ResetBits和 GPIO_SetBits 函数用于测试是否发送完成, 而非题目内容, 因此电源灯旁边的小灯亮灭一次仅表示函数执行一次

具体的功能实现位于 function_realize() 函数中, 传入的参数用于选择是否使用DMA

---

更新了, 重构了一点点, 去除了一些屎山, 但仍然很屎山.



由于手头的LED灯都不知道被薅到哪里去了, 因此没有测试呼吸灯





又是堆屎山的一天呢

警惕复制粘贴陷阱

指某人(没错说的就是我) 将 APB2 总线的时钟使能函数到了 粘贴成了 APB1 的 , 导致浪费了四个小时用于调试
