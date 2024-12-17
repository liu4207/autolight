/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file    adc.c
  * @brief   This file provides code for the configuration
  *          of the ADC instances.
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
#include "adc.h"

/* USER CODE BEGIN 0 */

/* USER CODE END 0 */

ADC_HandleTypeDef hadc1;

/* ADC1 init function */
void MX_ADC1_Init(void)
{

  /* USER CODE BEGIN ADC1_Init 0 */

  /* USER CODE END ADC1_Init 0 */

  ADC_ChannelConfTypeDef sConfig = {0};

  /* USER CODE BEGIN ADC1_Init 1 */

  /* USER CODE END ADC1_Init 1 */

  /** Common config
  */
  hadc1.Instance = ADC1;
  hadc1.Init.ScanConvMode = ADC_SCAN_ENABLE;
  hadc1.Init.ContinuousConvMode = ENABLE;
  hadc1.Init.DiscontinuousConvMode = DISABLE;
  hadc1.Init.ExternalTrigConv = ADC_SOFTWARE_START;
  hadc1.Init.DataAlign = ADC_DATAALIGN_RIGHT;
  hadc1.Init.NbrOfConversion = 4;
  if (HAL_ADC_Init(&hadc1) != HAL_OK)
  {
    Error_Handler();
  }

  /** Configure Regular Channel
  */
  sConfig.Channel = ADC_CHANNEL_4;
  sConfig.Rank = ADC_REGULAR_RANK_1;
  sConfig.SamplingTime = ADC_SAMPLETIME_55CYCLES_5;
	 //sConfig.SamplingTime = ADC_SAMPLETIME_55CYCLES_5; // 采样时间设置
  if (HAL_ADC_ConfigChannel(&hadc1, &sConfig) != HAL_OK)
  {
    Error_Handler();
  }

  /** Configure Regular Channel
  */
  sConfig.Rank = ADC_REGULAR_RANK_2;
  if (HAL_ADC_ConfigChannel(&hadc1, &sConfig) != HAL_OK)
  {
    Error_Handler();
  }

  /** Configure Regular Channel
  */
  sConfig.Rank = ADC_REGULAR_RANK_3;
  if (HAL_ADC_ConfigChannel(&hadc1, &sConfig) != HAL_OK)
  {
    Error_Handler();
  }

  /** Configure Regular Channel
  */
  sConfig.Rank = ADC_REGULAR_RANK_4;
  if (HAL_ADC_ConfigChannel(&hadc1, &sConfig) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN ADC1_Init 2 */

  /* USER CODE END ADC1_Init 2 */

}

void HAL_ADC_MspInit(ADC_HandleTypeDef* adcHandle)
{

  GPIO_InitTypeDef GPIO_InitStruct = {0};
  if(adcHandle->Instance==ADC1)
  {
  /* USER CODE BEGIN ADC1_MspInit 0 */

  /* USER CODE END ADC1_MspInit 0 */
    /* ADC1 clock enable */
    __HAL_RCC_ADC1_CLK_ENABLE();

    __HAL_RCC_GPIOA_CLK_ENABLE();
    /**ADC1 GPIO Configuration
    PA4     ------> ADC1_IN4
    PA5     ------> ADC1_IN5
    PA6     ------> ADC1_IN6
    PA7     ------> ADC1_IN7
    */
    GPIO_InitStruct.Pin = GPIO_PIN_4|GPIO_PIN_5|GPIO_PIN_6|GPIO_PIN_7;
    GPIO_InitStruct.Mode = GPIO_MODE_ANALOG;
    HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

  /* USER CODE BEGIN ADC1_MspInit 1 */

  /* USER CODE END ADC1_MspInit 1 */
  }
}

void HAL_ADC_MspDeInit(ADC_HandleTypeDef* adcHandle)
{

  if(adcHandle->Instance==ADC1)
  {
  /* USER CODE BEGIN ADC1_MspDeInit 0 */

  /* USER CODE END ADC1_MspDeInit 0 */
    /* Peripheral clock disable */
    __HAL_RCC_ADC1_CLK_DISABLE();

    /**ADC1 GPIO Configuration
    PA4     ------> ADC1_IN4
    PA5     ------> ADC1_IN5
    PA6     ------> ADC1_IN6
    PA7     ------> ADC1_IN7
    */
    HAL_GPIO_DeInit(GPIOA, GPIO_PIN_4|GPIO_PIN_5|GPIO_PIN_6|GPIO_PIN_7);

  /* USER CODE BEGIN ADC1_MspDeInit 1 */

  /* USER CODE END ADC1_MspDeInit 1 */
  }
}

/* USER CODE BEGIN 1 */
uint32_t Read_ADC_PA4(void)
{
  ADC_ChannelConfTypeDef sConfig = {0};
  sConfig.Channel = ADC_CHANNEL_4;  // ѡ��ͨ��4��PA4��
  sConfig.Rank = ADC_REGULAR_RANK_1;
  HAL_ADC_ConfigChannel(&hadc1, &sConfig);

  // ���� ADC ת��
  if (HAL_ADC_Start(&hadc1) != HAL_OK)
  {
    Error_Handler();
  }

  // �ȴ�ת�����
  if (HAL_ADC_PollForConversion(&hadc1, 100) != HAL_OK)
  {
    Error_Handler();
  }

  // ��ȡ ADC ת�����
  uint32_t adcValue = HAL_ADC_GetValue(&hadc1);

  // ֹͣ ADC ת��
 // HAL_ADC_Stop(&hadc1);

  return adcValue;
}
uint32_t Read_ADC_PA5(void)
{
  ADC_ChannelConfTypeDef sConfig = {0};
  sConfig.Channel = ADC_CHANNEL_5;  // ѡ��ͨ��5��PA5��
  sConfig.Rank = ADC_REGULAR_RANK_1;
  HAL_ADC_ConfigChannel(&hadc1, &sConfig);

  // ���� ADC ת��
  if (HAL_ADC_Start(&hadc1) != HAL_OK)
  {
    Error_Handler();
  }

  // �ȴ�ת�����
  if (HAL_ADC_PollForConversion(&hadc1, 100) != HAL_OK)
  {
    Error_Handler();
  }

  // ��ȡ ADC ת�����
  uint32_t adcValue = HAL_ADC_GetValue(&hadc1);

  // ֹͣ ADC ת��
 // HAL_ADC_Stop(&hadc1);

  return adcValue;
}
uint32_t Read_ADC_PA6(void)
{
  ADC_ChannelConfTypeDef sConfig = {0};
  sConfig.Channel = ADC_CHANNEL_6;  // ѡ��ͨ��6��PA6��
  sConfig.Rank = ADC_REGULAR_RANK_1;
  HAL_ADC_ConfigChannel(&hadc1, &sConfig);

  // ���� ADC ת��
  if (HAL_ADC_Start(&hadc1) != HAL_OK)
  {
    Error_Handler();
  }

  // �ȴ�ת�����
  if (HAL_ADC_PollForConversion(&hadc1, 100) != HAL_OK)
  {
    Error_Handler();
  }

  // ��ȡ ADC ת�����
  uint32_t adcValue = HAL_ADC_GetValue(&hadc1);

  // ֹͣ ADC ת��
  //HAL_ADC_Stop(&hadc1);

  return adcValue;
}
uint32_t Read_ADC_PA7(void)
{
  ADC_ChannelConfTypeDef sConfig = {0};
  sConfig.Channel = ADC_CHANNEL_7;  // ѡ��ͨ��7��PA7��
  sConfig.Rank = ADC_REGULAR_RANK_1;
  HAL_ADC_ConfigChannel(&hadc1, &sConfig);

  // ���� ADC ת��
  if (HAL_ADC_Start(&hadc1) != HAL_OK)
  {
    Error_Handler();
  }

  // �ȴ�ת�����
  if (HAL_ADC_PollForConversion(&hadc1, 100) != HAL_OK)
  {
    Error_Handler();
  }

  // ��ȡ ADC ת�����
  uint32_t adcValue = HAL_ADC_GetValue(&hadc1);

  // ֹͣ ADC ת��
  //HAL_ADC_Stop(&hadc1);

  return adcValue;
}

/* USER CODE END 1 */
