/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.c
  * @brief          : Main program body
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2024 STMicroelectronics.
  * All rights reserved.
  *
  * This software is licensed under terms that can be found in the LICENSE file
  * in the root directory of this software component.
  * If no LICENSE file comes with this software, it is provided AS-IS.
  *
  ******************************************************************************
  */
/* USER CODE END Header */
/* Includes ------------------------------------------------------------------*/
#include "main.h"
#include "adc.h"
#include "dma.h"
#include "tim.h"
#include "usart.h"
#include "gpio.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include "string.h"
#include "stdio.h"
/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */
#define PWM_PERIOD 3000  // PWM����Ϊ1000��������λ
#define KP 0.3 //8 0.3         // ��������
#define KI 0.0003 //  50 *0.002 /30   // ��������
#define KD 0.01
float voltage_ref = 6;  // �趨�������ѹ 
float voltage_fb = 0.0;   // ������ʵ�������ѹ
float duty_cycle = 0.0;   // ռ�ձ�
float error = 0.0;        // ���
float integral = 0.0;     // ������
float control_signal = 0.0;  // �����ź�
// ����ȫ�ֱ���
float last_error = 0.0;   // ��һ�ε����

float derivative = 0.0;   // ΢����
int sample_index = 0;  // ����������
float trueVoltage=0.0;     // ʵ�������ѹֵ
float VREF;
uint32_t time_counter = 0;  // ���ڼ�¼ʱ��ļ�����
uint8_t voltage_state = 0;  // 0 ��ʾ��ѹΪ8V��1 ��ʾ��ѹΪ10V
uint16_t ADValue;
float Voltage;
float i;

float light_value = 0.0;  // �ӹ⴫������ȡ�Ĺ�ǿֵ
#define MAX_LIGHT_SENSOR_VALUE 3.3  // ����⴫����������Ϊ 3.3V
#define MIN_LIGHT_SENSOR_VALUE 0.0  // ����⴫���������СΪ 0V

/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */
void SendHexNumbers(uint8_t hex1, uint8_t hex2)
{
    char message[10];  // Buffer to hold the formatted string
    snprintf(message, sizeof(message), "%02X %02X", hex1, hex2);  // Format as two hex numbers
    HAL_UART_Transmit(&huart1, (uint8_t *)message, strlen(message), 1000);  // Send the string
}
/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */
void control_buck(void)
{
	//��ȡADC��ֵ
	
	voltage_fb = (float)Read_ADC_PA4()*3.3/4096;
    // ����ʵ�ʵ�ѹ (�����ⲿ��·����)
    trueVoltage = voltage_fb*1050*20000/2500/1000*0.5;
    // �������
   error = voltage_ref*2500*1000/1050/20000*2- voltage_fb;

	// ���ּ���
   integral += error;
	// ΢�ּ���    
   derivative = error - last_error;
	//last_error=error;
	// PID�������
   control_signal = KP * error + KI * integral + KD * derivative;
   if (control_signal > 0.8)
   {
       control_signal = 0.8;
   }
   else if (control_signal < 0.2)
   {
       control_signal = 0.2;
   }
		// ����ռ�ձ�
   duty_cycle = control_signal * PWM_PERIOD;
	 i = (int)duty_cycle;
	 
	 //TIM2->CCR1 = (uint16_t)control_signal;
	 //TIM2->CCR1 = (uint16_t)duty_cycle;
	 //PWM_SetCompare1(i);
	 __HAL_TIM_SET_COMPARE(&htim2, TIM_CHANNEL_1, i);
	     //Serial_Printf("%d,%.2f\r\n", sample_index, trueVoltage);  // ����CSV��ʽ�����ݰ�
    sample_index++;
}

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/

/* USER CODE BEGIN PV */
// ���Ƶ����ȵĺ���
void control_light(void)
{
   
    light_value = (float)Read_ADC_PA7() * 3.3f / 4096;  
    

    duty_cycle = 500+( light_value) / 2*MAX_LIGHT_SENSOR_VALUE * PWM_PERIOD;
    
    if (duty_cycle > PWM_PERIOD)
    {
        duty_cycle = PWM_PERIOD;
    }
    else if (duty_cycle < 0)
    {
        duty_cycle = 0;
    }
    
   
    //PWM_SetCompare1((int)duty_cycle);
     __HAL_TIM_SET_COMPARE(&htim2, TIM_CHANNEL_1, (int)duty_cycle);
  
    sample_index++;
}
/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
/* USER CODE BEGIN PFP */

/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */

void SendHello(void)
{
    char message[] = "hello";  // Message to send
    HAL_UART_Transmit(&huart1, (uint8_t *)message, strlen(message), 1000);  // Send the message
}
 

// 
uint8_t rxBuffer[3]; 
uint8_t txBuffer[3] = "00"; 
int flag=0;
int sum=0;
// 
////��д�����жϷ�����
void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart)
{
    if (huart->Instance == USART1) // ȷ���� USART1
    {
        rxBuffer[2] = '\0'; // ȷ�����ջ��������ַ�����ʽ
        if (strcmp((char *)rxBuffer, "11") == 0) // �ж��Ƿ���յ� "11"
        {
					flag=1;
            HAL_UART_Transmit(&huart1, txBuffer, strlen((char *)txBuffer), 100); 
        }else if(strcmp((char *)rxBuffer, "00") == 0) // 
				{
					flag=0;

				}else if(strcmp((char *)rxBuffer, "22") == 0)
				{
					voltage_ref=5;
					
				}else if(strcmp((char *)rxBuffer, "20") == 0)
				{
				  voltage_ref=0;
				}else if(strcmp((char *)rxBuffer, "21") == 0)
				{
					voltage_ref=7;
				}else if(strcmp((char *)rxBuffer, "23") == 0)
				{
					flag=2;




				}
				if(flag==0 && strcmp((char *)rxBuffer, "01") == 0 )
				{
				voltage_ref+=0.1;
				}
				if(flag==0 && strcmp((char *)rxBuffer, "10") == 0 )
				voltage_ref-=0.2;

        // ���������жϽ���
        HAL_UART_Receive_IT(&huart1, rxBuffer, 2); // ���������ֽ�
    }
}

void boom_light()
{
	
				__HAL_TIM_SET_COMPARE(&htim2, TIM_CHANNEL_1,2400);
	HAL_Delay(250);
					__HAL_TIM_SET_COMPARE(&htim2, TIM_CHANNEL_1,500);

		HAL_Delay(250);

}
/* USER CODE END 0 */

/**
  * @brief  The application entry point.
  * @retval int
  */
int main(void)
{

  /* USER CODE BEGIN 1 */

  /* USER CODE END 1 */

  /* MCU Configuration--------------------------------------------------------*/

  /* Reset of all peripherals, Initializes the Flash interface and the Systick. */
  HAL_Init();

  /* USER CODE BEGIN Init */

  /* USER CODE END Init */

  /* Configure the system clock */
  SystemClock_Config();

  /* USER CODE BEGIN SysInit */

  /* USER CODE END SysInit */

  /* Initialize all configured peripherals */
  MX_GPIO_Init();
  MX_DMA_Init();
  MX_ADC1_Init();
  MX_TIM2_Init();
  MX_USART1_UART_Init();
  /* USER CODE BEGIN 2 */
HAL_TIM_PWM_Start(&htim2,TIM_CHANNEL_1);
//HAL_UART_Receive_IT(&huart1, &buf, 1);
//// 
//	HAL_UART_Transmit(&huart1, (uint8_t *)"hello world.", strlen("hello world."), 100);
/* ���������ж� */
    HAL_UART_Receive_IT(&huart1, rxBuffer, 2); // ���ý��������ֽ�
  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
  while (1)
  {
		//if(flag==2)
				//		{
			//		boom_light();
		//		}
				
		//SendHexNumbers(0x1A, 0xBC);
		//if(flag==0)//�ֶ�ģʽ
		
		//	control_buck();
			//else  if(flag==1)
		//		{
				control_light();
	//}
			

    /* USER CODE END WHILE */

    /* USER CODE BEGIN 3 */
		//__HAL_TIM_SET_COMPARE(&htim2, TIM_CHANNEL_1, 1800);
	//	SendHello();
			//���sta��λΪ1 ==�ܵ������е����� 
//		if((UART1_RX_STA & 0x8000)){
//			//��ӡ�յ������ݣ����ch�����sta
//			printf("recevied word: \r\n");
//			printf("%s",ch);
//			if(!strcmp((const char *)ch,"open")){
//				HAL_GPIO_WritePin(GPIOB,GPIO_PIN_8,GPIO_PIN_RESET);
//			}else if(!strcmp((const char *)ch,"close")){
//				HAL_GPIO_WritePin(GPIOB,GPIO_PIN_8,GPIO_PIN_SET);
//			}else{
//				printf("�������%s",ch);
//			}
//			UART1_RX_STA=0;
//			memset(ch,0,200);
//		}
//				//printf("hello world.\r\n");
//		HAL_Delay(10);
  }



  /* USER CODE END 3 */
}

/**
  * @brief System Clock Configuration
  * @retval None
  */
void SystemClock_Config(void)
{
  RCC_OscInitTypeDef RCC_OscInitStruct = {0};
  RCC_ClkInitTypeDef RCC_ClkInitStruct = {0};
  RCC_PeriphCLKInitTypeDef PeriphClkInit = {0};

  /** Initializes the RCC Oscillators according to the specified parameters
  * in the RCC_OscInitTypeDef structure.
  */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSE;
  RCC_OscInitStruct.HSEState = RCC_HSE_ON;
  RCC_OscInitStruct.HSEPredivValue = RCC_HSE_PREDIV_DIV1;
  RCC_OscInitStruct.HSIState = RCC_HSI_ON;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
  RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSE;
  RCC_OscInitStruct.PLL.PLLMUL = RCC_PLL_MUL9;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    Error_Handler();
  }

  /** Initializes the CPU, AHB and APB buses clocks
  */
  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
                              |RCC_CLOCKTYPE_PCLK1|RCC_CLOCKTYPE_PCLK2;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV2;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV1;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_2) != HAL_OK)
  {
    Error_Handler();
  }
  PeriphClkInit.PeriphClockSelection = RCC_PERIPHCLK_ADC;
  PeriphClkInit.AdcClockSelection = RCC_ADCPCLK2_DIV6;
  if (HAL_RCCEx_PeriphCLKConfig(&PeriphClkInit) != HAL_OK)
  {
    Error_Handler();
  }
}

/* USER CODE BEGIN 4 */

/* USER CODE END 4 */

/**
  * @brief  This function is executed in case of error occurrence.
  * @retval None
  */
void Error_Handler(void)
{
  /* USER CODE BEGIN Error_Handler_Debug */
  /* User can add his own implementation to report the HAL error return state */
  __disable_irq();
  while (1)
  {
  }
  /* USER CODE END Error_Handler_Debug */
}

#ifdef  USE_FULL_ASSERT
/**
  * @brief  Reports the name of the source file and the source line number
  *         where the assert_param error has occurred.
  * @param  file: pointer to the source file name
  * @param  line: assert_param error line source number
  * @retval None
  */
void assert_failed(uint8_t *file, uint32_t line)
{
  /* USER CODE BEGIN 6 */
  /* User can add his own implementation to report the file name and line number,
     ex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */
  /* USER CODE END 6 */
}
#endif /* USE_FULL_ASSERT */
