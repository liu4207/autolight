//#include "drv_usart.h"
//#include  "main.h"
//extern UART_HandleTypeDef huart1;
//	
//#define USART1_RX_DATA_FRAME_LEN	(18u)	// 串口3数据帧长度
//#define USART1_RX_BUF_LEN			(USART1_RX_DATA_FRAME_LEN + 6u)	// 串口3接收缓冲区长度
//uint8_t usart1_dma_rxbuf[2][USART1_RX_BUF_LEN];


 
//main函数中代码
//在串口初始化后
	//打开串口1接收中断  接收到的字符存在buf里，有一个字? 

//void USART1_Init(void)
//{
//    __HAL_UART_CLEAR_IDLEFLAG(&huart1);       // 清除空闲中断标志位
//    __HAL_UART_ENABLE_IT(&huart1, UART_IT_IDLE); // 使能空闲中断

//    // Enable the DMA transfer for the receiver request
//    SET_BIT(huart1.Instance->CR3, USART_CR3_DMAR); // 将串口对应的DMA打开

//    DMAEx_MultiBufferStart_NoIT(huart1.hdmarx,
//                                (uint32_t)&huart1.Instance->DR,
//                                (uint32_t)usart1_dma_rxbuf[0],
//                                (uint32_t)usart1_dma_rxbuf[1],
//                                USART1_RX_DATA_FRAME_LEN);     // 开启DMA双缓冲模式
//}

//void DRV_USART1_IRQHandler(UART_HandleTypeDef *huart)  //在stm32f4xx_it.c文件USART3_IRQHandler调用
//{
//    // 判断是否为空闲中断
//	if( __HAL_UART_GET_FLAG(huart, UART_FLAG_IDLE) &&
//		__HAL_UART_GET_IT_SOURCE(huart, UART_IT_IDLE))
//	{
//		uart_rx_idle_callback(huart); //空闲中断回调函数
//	}
//}
//static HAL_StatusTypeDef DMAEx_MultiBufferStart_NoIT(DMA_HandleTypeDef *hdma,
//                                                     uint32_t SrcAddress,
//                                                     uint32_t DstAddress,
//                                                     uint32_t SecondMemAddress,
//                                                     uint32_t DataLength)
//{
//    // 确认这个函数是你实际情况的适用实现。
//    // 初始化过程中的设置需要依据具体的DMA通道和配置。
//    // 该函数中的代码结构不变，仅需确保DMA实例正确指向USART1相关DMA通道。
//}

//// DMA中断服务程序和回调函数的具体实现需要根据你的需求来定制。
//// 以下为回调函数实现示例：
//static void dma_m0_rxcplt_callback(DMA_HandleTypeDef *hdma)
//{
//    if(hdma == huart1.hdmarx)
//    {
//        hdma->Instance->CR |= DMA_SxCR_CT_Msk;  // 切换到缓冲1
//        USART1_rxDataHandler(usart1_dma_rxbuf[0]);  // 处理接收到的数据
//    }
//}

//static void dma_m1_rxcplt_callback(DMA_HandleTypeDef *hdma)
//{
//    if(hdma == huart1.hdmarx)
//    {
//        hdma->Instance->CR &= ~DMA_SxCR_CT_Msk;  // 切换到缓冲0
//        USART1_rxDataHandler(usart1_dma_rxbuf[1]);  // 处理接收到的数据
//    }
//}
