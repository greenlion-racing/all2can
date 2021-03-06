/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * File Name          : freertos.c
  * Description        : Code for freertos applications
  ******************************************************************************
  * This notice applies to any and all portions of this file
  * that are not between comment pairs USER CODE BEGIN and
  * USER CODE END. Other portions of this file, whether 
  * inserted by the user or by software development tools
  * are owned by their respective copyright owners.
  *
  * Copyright (c) 2018 STMicroelectronics International N.V. 
  * All rights reserved.
  *
  * Redistribution and use in source and binary forms, with or without 
  * modification, are permitted, provided that the following conditions are met:
  *
  * 1. Redistribution of source code must retain the above copyright notice, 
  *    this list of conditions and the following disclaimer.
  * 2. Redistributions in binary form must reproduce the above copyright notice,
  *    this list of conditions and the following disclaimer in the documentation
  *    and/or other materials provided with the distribution.
  * 3. Neither the name of STMicroelectronics nor the names of other 
  *    contributors to this software may be used to endorse or promote products 
  *    derived from this software without specific written permission.
  * 4. This software, including modifications and/or derivative works of this 
  *    software, must execute solely and exclusively on microcontroller or
  *    microprocessor devices manufactured by or for STMicroelectronics.
  * 5. Redistribution and use of this software other than as permitted under 
  *    this license is void and will automatically terminate your rights under 
  *    this license. 
  *
  * THIS SOFTWARE IS PROVIDED BY STMICROELECTRONICS AND CONTRIBUTORS "AS IS" 
  * AND ANY EXPRESS, IMPLIED OR STATUTORY WARRANTIES, INCLUDING, BUT NOT 
  * LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY, FITNESS FOR A 
  * PARTICULAR PURPOSE AND NON-INFRINGEMENT OF THIRD PARTY INTELLECTUAL PROPERTY
  * RIGHTS ARE DISCLAIMED TO THE FULLEST EXTENT PERMITTED BY LAW. IN NO EVENT 
  * SHALL STMICROELECTRONICS OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT,
  * INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
  * LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, 
  * OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF 
  * LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING 
  * NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE,
  * EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
  *
  ******************************************************************************
  */
/* USER CODE END Header */

/* Includes ------------------------------------------------------------------*/
#include "FreeRTOS.h"
#include "task.h"
#include "main.h"
#include "cmsis_os.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */     
#include "can.h"
/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */

/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */
//#define ph_debug
/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/
/* USER CODE BEGIN Variables */
volatile uint8_t nCM =0;

/* USER CODE END Variables */
osThreadId defaultTaskHandle;
osThreadId TaskSendCanHandle;
osThreadId TaskGetCanHandle;
osThreadId TaskGetSuspensiHandle;

/* Private function prototypes -----------------------------------------------*/
/* USER CODE BEGIN FunctionPrototypes */
   void newCanMessage(void);
/* USER CODE END FunctionPrototypes */

void StartDefaultTask(void const * argument);
void TaskSend(void const * argument);
void TaskGet(void const * argument);
void TaskGetS(void const * argument);

void MX_FREERTOS_Init(void); /* (MISRA C 2004 rule 8.1) */

/**
  * @brief  FreeRTOS initialization
  * @param  None
  * @retval None
  */
void MX_FREERTOS_Init(void) {
  /* USER CODE BEGIN Init */
       

  /* USER CODE END Init */

  /* USER CODE BEGIN RTOS_MUTEX */
  /* add mutexes, ... */
  /* USER CODE END RTOS_MUTEX */

  /* USER CODE BEGIN RTOS_SEMAPHORES */
  /* add semaphores, ... */
  /* USER CODE END RTOS_SEMAPHORES */

  /* USER CODE BEGIN RTOS_TIMERS */
  /* start timers, add new ones, ... */
  /* USER CODE END RTOS_TIMERS */

  /* USER CODE BEGIN RTOS_QUEUES */
  /* add queues, ... */
  /* USER CODE END RTOS_QUEUES */

  /* Create the thread(s) */
  /* definition and creation of defaultTask */
  osThreadDef(defaultTask, StartDefaultTask, osPriorityNormal, 0, 128);
  defaultTaskHandle = osThreadCreate(osThread(defaultTask), NULL);

  /* definition and creation of TaskSendCan */
  osThreadDef(TaskSendCan, TaskSend, osPriorityLow, 0, 128);
  TaskSendCanHandle = osThreadCreate(osThread(TaskSendCan), NULL);

  /* definition and creation of TaskGetCan */
  osThreadDef(TaskGetCan, TaskGet, osPriorityNormal, 0, 128);
  TaskGetCanHandle = osThreadCreate(osThread(TaskGetCan), NULL);

  /* definition and creation of TaskGetSuspensi */
  osThreadDef(TaskGetSuspensi, TaskGetS, osPriorityBelowNormal, 0, 128);
  TaskGetSuspensiHandle = osThreadCreate(osThread(TaskGetSuspensi), NULL);

  /* USER CODE BEGIN RTOS_THREADS */
  /* add threads, ... */
  /* USER CODE END RTOS_THREADS */

}

/* USER CODE BEGIN Header_StartDefaultTask */
/**
  * @brief  Function implementing the defaultTask thread.
  * @param  argument: Not used 
  * @retval None
  */
/* USER CODE END Header_StartDefaultTask */
void StartDefaultTask(void const * argument)
{

  /* USER CODE BEGIN StartDefaultTask */
  /* Infinite loop */
  for(;;)
  {
  //  osDelay(500);
 //   JDO_SendCan();
 //   JDO_GetCan();
  }
  /* USER CODE END StartDefaultTask */
}

/* USER CODE BEGIN Header_TaskSend */
/**
* @brief Function implementing the TaskSendCan thread.
* @param argument: Not used
* @retval None
*/
/* USER CODE END Header_TaskSend */
void TaskSend(void const * argument)
{
  /* USER CODE BEGIN TaskSend */
  /* Infinite loop */
  for(;;)
  {
	  osDelay(500);
	#ifdef ph_debug
	  JDO_SendCan();
	#endif //debug
  }
  /* USER CODE END TaskSend */
}

/* USER CODE BEGIN Header_TaskGet */
/**
* @brief Function implementing the TaskGetCan thread.
* @param argument: Not used
* @retval None
*/
/* USER CODE END Header_TaskGet */
void TaskGet(void const * argument)
{
  /* USER CODE BEGIN TaskGet */
  /* Infinite loop */
  for(;;)
  {
	  osDelay(1);
	  if(nCM == 1){
		  JDO_GetCan();
	  }
	  nCM =0;
  }
  /* USER CODE END TaskGet */
}

/* USER CODE BEGIN Header_TaskGetS */
/**
* @brief Function implementing the TaskGetSuspensi thread.
* @param argument: Not used
* @retval None
*/
/* USER CODE END Header_TaskGetS */
void TaskGetS(void const * argument)
{
  /* USER CODE BEGIN TaskGetS */
  /* Infinite loop */
  for(;;)
  { //TODO: Check if usage of HAL_ADC PollForConversion and GetValue are used correctly (inteded function is to read the two different GPIO's)
    //Start ADC
    HAL_ADC_Start(&hadc1);
    //Start Conversion(s?)
    HAL_ADC_PollForConversion(&hadc1, 100);
    //Get Value 1 and 2 and send them to CAN
    JDO_SendPoti(HAL_ADC_GetValue(&hadc1),HAL_ADC_GetValue(&hadc1));
    HAL_ADC_Stop(&hadc1);
    osDelay(10);
  }
  /* USER CODE END TaskGetS */
}

/* Private application code --------------------------------------------------*/
/* USER CODE BEGIN Application */
void newCanMessage(void){
	   nCM = 1;
}
/* USER CODE END Application */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
