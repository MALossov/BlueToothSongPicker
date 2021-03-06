/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.c
  * @brief          : Main program body
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; Copyright (c) 2021 STMicroelectronics.
  * All rights reserved.</center></h2>
  *
  * This software component is licensed by ST under BSD 3-Clause license,
  * the "License"; You may not use this file except in compliance with the
  * License. You may obtain a copy of the License at:
  *                        opensource.org/licenses/BSD-3-Clause
  *
  ******************************************************************************
  */
/* USER CODE END Header */
/* Includes ------------------------------------------------------------------*/
#include "main.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include "XMF_OLED_STM32Cube.h"
/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */

/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */
#define KEY1 HAL_GPIO_ReadPin(GPIOB,GPIO_PIN_1)
#define KEY2 HAL_GPIO_ReadPin(GPIOB,GPIO_PIN_0)
#define KEY3 HAL_GPIO_ReadPin(GPIOB,GPIO_PIN_10)
#define KEY4 HAL_GPIO_ReadPin(GPIOB,GPIO_PIN_11)
/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/
UART_HandleTypeDef huart2;

/* USER CODE BEGIN PV */

/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
static void MX_GPIO_Init(void);
static void MX_USART2_UART_Init(void);
/* USER CODE BEGIN PFP */

/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */
extern unsigned char BMP_MP3[];
void OledWelcome(){
	OLED_Clear();
	OLED_DrawBMP(0,0,128,8,BMP_MP3);
}
	
void ShowList(){
	OLED_Clear();
	
	OLED_ShowTitle(3,0,0);
	OLED_ShowTitle(21,0,1);
	OLED_ShowTitle(39,0,2);
	OLED_ShowTitle(57,0,3);
	OLED_ShowTitle(75,0,4);
	OLED_ShowTitle(93,0,5);
	
	OLED_ShowString(0,2,(uint8_t *)"1.LoveStory.mp3");
	OLED_ShowString(0,4,(uint8_t *)"2.Stay.mp3");
}
//NEXT ARE ABOUT LED
void LedTKT()
{
	HAL_GPIO_TogglePin(GPIOC,GPIO_PIN_13);
	HAL_Delay(200);
}

//NEXT ARE ABOUT VALUES
uint8_t sound = 5;
_Bool isSound = 0;
_Bool isPlay = 0;

//NEXT ARE ABOUT TEXTSENDING
void VoiceDisplayAndSend(uint8_t level){
	uint8_t soundl = level + 48;
	uint8_t soundstr[] = "SoundLevelIs:" ;
	
	ShowList();
	if(level < 10 && level > 0){
	OLED_ShowString(0,6,soundstr);
	OLED_ShowChar(118,6,soundl);
		HAL_UART_Transmit(&huart2,(uint8_t *)&soundl,1,10);
		HAL_UART_Transmit(&huart2,(uint8_t *)"\n",1,10);}
	else if(level == 0)	
	{OLED_ShowString(0,6,(uint8_t *)"NowMIN! NoChange");
		HAL_UART_Transmit(&huart2,(uint8_t *)"0\n",2,10);}
	else {OLED_ShowString(0,6,(uint8_t *)"NowMAX! NoChange");
		HAL_UART_Transmit(&huart2,(uint8_t *)":\n",2,10);}
	
}
//NEXT ARE ABOUT SCAN
void Scan_Keys()
{
		LedTKT();
	LedTKT();
	
//	if(isPlay){	HAL_UART_Transmit(&huart2,(uint8_t *)"v\n",2,50);
//							HAL_Delay(600);}

		
    if(KEY2 == GPIO_PIN_RESET)
    {
        HAL_Delay(30);
        if(KEY2 == GPIO_PIN_RESET)
        {          
					if(isSound == 0){
						ShowList();
						OLED_ShowString(0,6,(uint8_t *)"Now Next Song!");
						HAL_UART_Transmit(&huart2,(uint8_t *)"U\n",2,10);
						isPlay = 1;
					}

					else{
						if(sound < 10) sound++;
						VoiceDisplayAndSend(sound);}
						
						
						while(KEY2 == GPIO_PIN_RESET);
					
        }
    }
	
    if(KEY3 == RESET)
    {
        HAL_Delay(30);
        if(KEY3 == RESET)
        {
            
					if(isSound == 0){
           						ShowList();
						OLED_ShowString(0,6,(uint8_t *)"Now Former Song!");
						HAL_UART_Transmit(&huart2,(uint8_t *)"D\n",2,10);
						isPlay = 1;
					}
				else{
					 if(sound) sound--;
						VoiceDisplayAndSend(sound);
						}
				
				while(KEY3 == RESET);

        }
    }
    if(KEY4 == RESET)
    {
        HAL_Delay(30);
        if(KEY4 == 0)
        {
            ShowList();
						//HAL_UART_Transmit(&huart2,strp,sizeof(strp),10);
				if(isPlay) {
					isPlay--; 
					OLED_ShowString(0,6,(uint8_t *)"You PAUSE!");}
				else {OLED_ShowString(0,6,(uint8_t *)"You PLAY! "); isPlay++;}
								HAL_UART_Transmit(&huart2,(uint8_t *)"P\n",2,10);

						
						while(KEY4 == GPIO_PIN_RESET);						
        }
    }
		if(KEY1 == RESET)
    {
        HAL_Delay(30);
        if(KEY1 == 0)
        {
            ShowList();
					if(isSound == 0){
						isSound++;
						OLED_ShowString(0,6,(uint8_t *)"SoundChangeMode!");}
					else{
						isSound--;
						OLED_ShowString(0,6,(uint8_t *)"MusicChangeMode!");}
					
						while(KEY1 == GPIO_PIN_RESET);						
        }
    }
		
		
		
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
  MX_USART2_UART_Init();
  /* USER CODE BEGIN 2 */
	OLED_Init();
	OledWelcome();
	HAL_Delay(5000);
	ShowList();
  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
  while (1)
  {
				Scan_Keys();
    /* USER CODE END WHILE */

    /* USER CODE BEGIN 3 */
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
}

/**
  * @brief USART2 Initialization Function
  * @param None
  * @retval None
  */
static void MX_USART2_UART_Init(void)
{

  /* USER CODE BEGIN USART2_Init 0 */

  /* USER CODE END USART2_Init 0 */

  /* USER CODE BEGIN USART2_Init 1 */

  /* USER CODE END USART2_Init 1 */
  huart2.Instance = USART2;
  huart2.Init.BaudRate = 9600;
  huart2.Init.WordLength = UART_WORDLENGTH_8B;
  huart2.Init.StopBits = UART_STOPBITS_1;
  huart2.Init.Parity = UART_PARITY_NONE;
  huart2.Init.Mode = UART_MODE_TX_RX;
  huart2.Init.HwFlowCtl = UART_HWCONTROL_NONE;
  huart2.Init.OverSampling = UART_OVERSAMPLING_16;
  if (HAL_UART_Init(&huart2) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN USART2_Init 2 */

  /* USER CODE END USART2_Init 2 */

}

/**
  * @brief GPIO Initialization Function
  * @param None
  * @retval None
  */
static void MX_GPIO_Init(void)
{
  GPIO_InitTypeDef GPIO_InitStruct = {0};

  /* GPIO Ports Clock Enable */
  __HAL_RCC_GPIOC_CLK_ENABLE();
  __HAL_RCC_GPIOD_CLK_ENABLE();
  __HAL_RCC_GPIOA_CLK_ENABLE();
  __HAL_RCC_GPIOB_CLK_ENABLE();

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOC, GPIO_PIN_13, GPIO_PIN_RESET);

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOB, GPIO_PIN_12|GPIO_PIN_13|GPIO_PIN_14|GPIO_PIN_15, GPIO_PIN_RESET);

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOA, GPIO_PIN_8, GPIO_PIN_SET);

  /*Configure GPIO pin : PC13 */
  GPIO_InitStruct.Pin = GPIO_PIN_13;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOC, &GPIO_InitStruct);

  /*Configure GPIO pins : PB0 PB1 PB10 PB11 */
  GPIO_InitStruct.Pin = GPIO_PIN_0|GPIO_PIN_1|GPIO_PIN_10|GPIO_PIN_11;
  GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
  GPIO_InitStruct.Pull = GPIO_PULLUP;
  HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);

  /*Configure GPIO pins : PB12 PB13 PB14 PB15 */
  GPIO_InitStruct.Pin = GPIO_PIN_12|GPIO_PIN_13|GPIO_PIN_14|GPIO_PIN_15;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);

  /*Configure GPIO pin : PA8 */
  GPIO_InitStruct.Pin = GPIO_PIN_8;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

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

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
