//#include "drv_usart.h"
//#include  "main.h"
//extern UART_HandleTypeDef huart1;
//	
//#define USART1_RX_DATA_FRAME_LEN	(18u)	// ����3����֡����
//#define USART1_RX_BUF_LEN			(USART1_RX_DATA_FRAME_LEN + 6u)	// ����3���ջ���������
//uint8_t usart1_dma_rxbuf[2][USART1_RX_BUF_LEN];


 
//main�����д���
//�ڴ��ڳ�ʼ����
	//�򿪴���1�����ж�  ���յ����ַ�����buf���һ����? 

//void USART1_Init(void)
//{
//    __HAL_UART_CLEAR_IDLEFLAG(&huart1);       // ��������жϱ�־λ
//    __HAL_UART_ENABLE_IT(&huart1, UART_IT_IDLE); // ʹ�ܿ����ж�

//    // Enable the DMA transfer for the receiver request
//    SET_BIT(huart1.Instance->CR3, USART_CR3_DMAR); // �����ڶ�Ӧ��DMA��

//    DMAEx_MultiBufferStart_NoIT(huart1.hdmarx,
//                                (uint32_t)&huart1.Instance->DR,
//                                (uint32_t)usart1_dma_rxbuf[0],
//                                (uint32_t)usart1_dma_rxbuf[1],
//                                USART1_RX_DATA_FRAME_LEN);     // ����DMA˫����ģʽ
//}

//void DRV_USART1_IRQHandler(UART_HandleTypeDef *huart)  //��stm32f4xx_it.c�ļ�USART3_IRQHandler����
//{
//    // �ж��Ƿ�Ϊ�����ж�
//	if( __HAL_UART_GET_FLAG(huart, UART_FLAG_IDLE) &&
//		__HAL_UART_GET_IT_SOURCE(huart, UART_IT_IDLE))
//	{
//		uart_rx_idle_callback(huart); //�����жϻص�����
//	}
//}
//static HAL_StatusTypeDef DMAEx_MultiBufferStart_NoIT(DMA_HandleTypeDef *hdma,
//                                                     uint32_t SrcAddress,
//                                                     uint32_t DstAddress,
//                                                     uint32_t SecondMemAddress,
//                                                     uint32_t DataLength)
//{
//    // ȷ�������������ʵ�����������ʵ�֡�
//    // ��ʼ�������е�������Ҫ���ݾ����DMAͨ�������á�
//    // �ú����еĴ���ṹ���䣬����ȷ��DMAʵ����ȷָ��USART1���DMAͨ����
//}

//// DMA�жϷ������ͻص������ľ���ʵ����Ҫ����������������ơ�
//// ����Ϊ�ص�����ʵ��ʾ����
//static void dma_m0_rxcplt_callback(DMA_HandleTypeDef *hdma)
//{
//    if(hdma == huart1.hdmarx)
//    {
//        hdma->Instance->CR |= DMA_SxCR_CT_Msk;  // �л�������1
//        USART1_rxDataHandler(usart1_dma_rxbuf[0]);  // ������յ�������
//    }
//}

//static void dma_m1_rxcplt_callback(DMA_HandleTypeDef *hdma)
//{
//    if(hdma == huart1.hdmarx)
//    {
//        hdma->Instance->CR &= ~DMA_SxCR_CT_Msk;  // �л�������0
//        USART1_rxDataHandler(usart1_dma_rxbuf[1]);  // ������յ�������
//    }
//}
