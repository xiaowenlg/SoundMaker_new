/**
  ******************************************************************************
  * File Name          : TIM.c
  * Description        : This file provides code for the configuration
  *                      of the TIM instances.
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; Copyright (c) 2019 STMicroelectronics.
  * All rights reserved.</center></h2>
  *
  * This software component is licensed by ST under Ultimate Liberty license
  * SLA0044, the "License"; You may not use this file except in compliance with
  * the License. You may obtain a copy of the License at:
  *                             www.st.com/SLA0044
  *
  ******************************************************************************
  */

/* Includes ------------------------------------------------------------------*/
#include "tim.h"
#include "usart.h"
#include <stdlib.h>
#include "gpio.h"
#include "math.h"
#include "MainConfig.h"
#include "ToolAPP.h"
#include "queue.h"
/* USER CODE BEGIN 0 */

/* USER CODE END 0 */

TIM_HandleTypeDef htim2;
TIM_HandleTypeDef htim3;
uint16_t SportCount = 0;
uint16_t testcount = 0;
Customerinfo meSportInfo = {0};

_Bool BeginPlay = 0;
/* TIM2 init function */
void MX_TIM2_Init(uint16_t per)        //��ʱ��2             
{
	TIM_ClockConfigTypeDef sClockSourceConfig;
	TIM_MasterConfigTypeDef sMasterConfig;

	htim2.Instance = TIM2;
	htim2.Init.Prescaler = 71;
	htim2.Init.CounterMode = TIM_COUNTERMODE_UP;
	htim2.Init.Period = per;
	htim2.Init.ClockDivision = TIM_CLOCKDIVISION_DIV1;
	htim2.Init.AutoReloadPreload =TIM_AUTORELOAD_PRELOAD_ENABLE;
	if (HAL_TIM_Base_Init(&htim2) != HAL_OK)
	{
		Error_Handler();
	}

	sClockSourceConfig.ClockSource = TIM_CLOCKSOURCE_INTERNAL;
	if (HAL_TIM_ConfigClockSource(&htim2, &sClockSourceConfig) != HAL_OK)
	{
		Error_Handler();
	}

	sMasterConfig.MasterOutputTrigger = TIM_TRGO_RESET;
	sMasterConfig.MasterSlaveMode = TIM_MASTERSLAVEMODE_DISABLE;
	if (HAL_TIMEx_MasterConfigSynchronization(&htim2, &sMasterConfig) != HAL_OK)
	{
		Error_Handler();
	}

}
void MX_TIM3_Init(uint16_t per)
{
	TIM_ClockConfigTypeDef sClockSourceConfig;
	TIM_MasterConfigTypeDef sMasterConfig;

	htim3.Instance = TIM3;
	htim3.Init.Prescaler = 71;
	htim3.Init.CounterMode = TIM_COUNTERMODE_UP;
	htim3.Init.Period = per;
	htim3.Init.ClockDivision = TIM_CLOCKDIVISION_DIV1;
	htim3.Init.AutoReloadPreload = TIM_AUTORELOAD_PRELOAD_DISABLE;
	if (HAL_TIM_Base_Init(&htim3) != HAL_OK)
	{
		Error_Handler();
	}
	sClockSourceConfig.ClockSource = TIM_CLOCKSOURCE_INTERNAL;
	if (HAL_TIM_ConfigClockSource(&htim3,&sClockSourceConfig) != HAL_OK)
	{
		Error_Handler();
	}
	sMasterConfig.MasterOutputTrigger = TIM_TRGO_RESET;
	sMasterConfig.MasterSlaveMode = TIM_MASTERSLAVEMODE_DISABLE;
	if (HAL_TIMEx_MasterConfigSynchronization(&htim2, &sMasterConfig) != HAL_OK)
	{
		Error_Handler();
	}

}

void HAL_TIM_Base_MspInit(TIM_HandleTypeDef* tim_baseHandle)
{

  if(tim_baseHandle->Instance==TIM2)
  {
 
	__HAL_RCC_TIM2_CLK_ENABLE();
	HAL_NVIC_SetPriority(TIM2_IRQn, 5,4);
	HAL_NVIC_EnableIRQ(TIM2_IRQn);
  }
  else if (tim_baseHandle->Instance == TIM3) //��ʱ��3
  {
	  __HAL_RCC_TIM3_CLK_ENABLE();
	  HAL_NVIC_SetPriority(TIM3_IRQn, 2, 3);
	  HAL_NVIC_EnableIRQ(TIM3_IRQn);

  }
}

void HAL_TIM_Base_MspDeInit(TIM_HandleTypeDef* tim_baseHandle)
{
  if(tim_baseHandle->Instance==TIM2)
  {
    __HAL_RCC_TIM2_CLK_DISABLE();
	HAL_NVIC_DisableIRQ(TIM2_IRQn);
  }
  else if (tim_baseHandle->Instance == TIM3)
  {
	  __HAL_RCC_TIM3_CLK_DISABLE();
	  HAL_NVIC_DisableIRQ(TIM3_IRQn);
  }
} 

//************************************
// ����:    HAL_TIM_PeriodElapsedCallback
// ����ȫ��:  HAL_TIM_PeriodElapsedCallback
// ��������:    public 
// ����ֵ:   void
// Qualifier:��ʱ���жϴ�������
// ����: TIM_HandleTypeDef * htim
//************************************
void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim)
{
	static uint16_t timer2_T_i,timer2_beginplay  =0,timer2_Message_T,timer2_Test;
	BaseType_t xResult;
	BaseType_t xHigherPriorityTaskWoken = pdFALSE;
	Customerinfo   *ptMsg;
	ptMsg = &meSportInfo;
	if (htim->Instance == TIM4) 
	{
		HAL_IncTick();  //HAL���ڲ���ʱ��
	}
	if (htim->Instance == TIM2)
	{
		if (timer2_T_i++>TIMER2_T)
		{
			timer2_T_i = 0;
			ptMsg->freq = TempCount;
			TempCount = 0;
			
			if (ptMsg->freq>0)
			{
				ptMsg->tim++;
			}
		}
		if (ptMsg->freq <= 0)
		{
			if (timer2_beginplay++>TIMER2_PLAY_WAIT)
			{
				timer2_beginplay = 0;  
				if (SportCount!=0)
				{
					ptMsg->playstate = 1;//��ʼ����
				}
				BeginPlay = 1;
				//ptMsg->playstate = 1;//��ʼ����
			}
			//��������������
			if (playisover)//�������
			{
				playisover = 0;
				SportCount = 0;
				ptMsg->tim = 0;
			}
		}
		else
		{
			ptMsg->playstate = 0;//ֹͣ����
			iscolsesystem = 0;
		}
		
		
		//�����˶���Ϣ
		if (timer2_Message_T++>=50)
		{
			timer2_Message_T = 0;
			ptMsg->count = SportCount;
			ptMsg->hot = SportCount*coefficient;
			
			
			if (xQueuel_tim!=NULL)
			{

				xQueueSendFromISR(xQueuel_tim, (void *)&ptMsg, &xHigherPriorityTaskWoken);//������Ϣ
				portYIELD_FROM_ISR(xHigherPriorityTaskWoken);
			}
		}
		if (timer2_Test++ > 100)
		{
			timer2_Test = 0;
			uart_flag = 1;
		}
		//���Դ����--------------------------------
	/*	if (timer2_Test++>500)
		{
			timer2_Test = 0;
			SportCount++;
			if (SportCount<50)
			{
				TempCount++;
			}
			
			if (SportCount >= 65536)
			{
				SportCount = 0;
			}
		}*/
		//���Դ����--------------------------------
	}
}
/* USER CODE BEGIN 1 */

/* USER CODE END 1 */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/