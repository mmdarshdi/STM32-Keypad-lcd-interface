	/* USER CODE BEGIN Header */
	/**
		******************************************************************************
		* @file           : main.c
		* @brief          : Main program body
		******************************************************************************
		* @attention
		*
		* Copyright (c) 2026 STMicroelectronics.
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
	#include "lcd.h"
	/* Private includes ----------------------------------------------------------*/
	/* USER CODE BEGIN Includes */

	/* USER CODE END Includes */

	/* Private typedef -----------------------------------------------------------*/
	/* USER CODE BEGIN PTD */

	/* USER CODE END PTD */

	/* Private define ------------------------------------------------------------*/
	/* USER CODE BEGIN PD */
	#define R1_PORT GPIOA
	#define R1_PIN GPIO_PIN_8

	#define R2_PORT GPIOA
	#define R2_PIN GPIO_PIN_9

	#define R3_PORT GPIOA
	#define R3_PIN GPIO_PIN_10

	#define R4_PORT GPIOA
	#define R4_PIN GPIO_PIN_11

	#define R5_PORT GPIOA
	#define R5_PIN GPIO_PIN_12

	#define C1_PORT GPIOB
	#define C1_PIN GPIO_PIN_5

	#define C2_PORT GPIOB
	#define C2_PIN GPIO_PIN_4

	#define C3_PORT GPIOB
	#define C3_PIN GPIO_PIN_3

	#define C4_PORT GPIOA
	#define C4_PIN GPIO_PIN_15

	/* USER CODE END PD */

	/* Private macro -------------------------------------------------------------*/
	/* USER CODE BEGIN PM */

	/* USER CODE END PM */

	/* Private variables ---------------------------------------------------------*/
	UART_HandleTypeDef huart1;

	/* USER CODE BEGIN PV */
	int value ;
	char str[20];
	uint8_t memory = 0;
	/* USER CODE END PV */

	/* Private function prototypes -----------------------------------------------*/
	void SystemClock_Config(void);
	static void MX_GPIO_Init(void);
	static void MX_USART1_UART_Init(void);
	/* USER CODE BEGIN PFP */
	char read_keypad (void);
	/* USER CODE END PFP */

	/* Private user code ---------------------------------------------------------*/
	/* USER CODE BEGIN 0 */
	uint8_t key;
	uint8_t KEY[]=
	{'F','f','#','*',
		'1','2','3','U',
		'4','5','6','D',
		'7','8','9','E',
		'L','0','R','T' };



	char read_keypad (void)
	{
	//	make ROW1 Low and ALL_CHANNELS other ROWs HIGH
		HAL_GPIO_WritePin (R1_PORT, R1_PIN,GPIO_PIN_RESET); //PULL R1 LOW
		HAL_GPIO_WritePin (R2_PORT, R2_PIN,GPIO_PIN_SET); //PULL Rx up
		HAL_GPIO_WritePin (R3_PORT, R3_PIN,GPIO_PIN_SET);//PULL Rx up
		HAL_GPIO_WritePin (R4_PORT, R4_PIN,GPIO_PIN_SET); //PULL Rx up
		HAL_GPIO_WritePin (R5_PORT, R5_PIN,GPIO_PIN_SET); //PULL Rx up
		HAL_Delay(5);


		if(!(HAL_GPIO_ReadPin (C1_PORT, C1_PIN)))
			{
				while (!(HAL_GPIO_ReadPin (C1_PORT,C1_PIN))); //// Wait until button released
		str[memory] = KEY[0];                        // Store new character
		memory++;                                   // Move to next position
		str[memory] = '\0';                         // End string
		lcd_puts(str);                               // Display key on LCD
		lcd_gotoxy(0,0);
		return 'F';
		}
	if(!(HAL_GPIO_ReadPin (C2_PORT, C2_PIN))){
		while (!(HAL_GPIO_ReadPin (C2_PORT,C2_PIN))); //// Wait until button releasedD
	str[memory] = KEY[1];                        // Store new character
		memory++;                                   // Move to next position
		str[memory] = '\0';  
		lcd_gotoxy(0,0);                       // End string
		lcd_puts(str);                               // Display key on LCD                        
	return 'f';
	}
	if(!(HAL_GPIO_ReadPin (C3_PORT, C3_PIN))){
		while (!(HAL_GPIO_ReadPin (C3_PORT,C3_PIN))); //// Wait until button released
	str[memory] = KEY[2];                        // Store new character
		memory++;                                   // Move to next position
		str[memory] = '\0';
		lcd_gotoxy(0,0);                          // End string
		lcd_puts(str);                               // Display key on LCD                           
		
	return '#';
	}	
	if(!(HAL_GPIO_ReadPin (C4_PORT, C4_PIN))){
		while (!(HAL_GPIO_ReadPin (C4_PORT,C4_PIN))); //// Wait until button released
	str[memory] = KEY[3];                        // Store new character
		memory++;                                   // Move to next position
		str[memory] = '\0'; 
		lcd_gotoxy(0,0);                         // End string
		lcd_puts(str);                               // Display key on LC
		
	return '*';
	}


	//	make ROW2 Low and ALL_CHANNELS other ROWs HIGH
		HAL_GPIO_WritePin (R1_PORT, R1_PIN,GPIO_PIN_SET); //PULL R1 UP
		HAL_GPIO_WritePin (R2_PORT, R2_PIN,GPIO_PIN_RESET); //PULL R2 LOW
		HAL_GPIO_WritePin (R3_PORT, R3_PIN,GPIO_PIN_SET);//PULL Rx up
		HAL_GPIO_WritePin (R4_PORT, R4_PIN,GPIO_PIN_SET); //PULL Rx up
		HAL_GPIO_WritePin (R5_PORT, R5_PIN,GPIO_PIN_SET); //PULL Rx up
		HAL_Delay(5);


	if(!(HAL_GPIO_ReadPin (C1_PORT, C1_PIN))){
		while (!(HAL_GPIO_ReadPin (C1_PORT,C1_PIN))); //WAIT TILL THE BUTTON IS PORESSED
str[memory] = KEY[4];                        // Store new character
		memory++;                                   // Move to next position
		str[memory] = '\0';  
		lcd_gotoxy(0,0);                        // End string
		lcd_puts(str);                               // Display key on LCD
	return '1';
	}
	if(!(HAL_GPIO_ReadPin (C2_PORT, C2_PIN))){
		while (!(HAL_GPIO_ReadPin (C2_PORT,C2_PIN))); //WAIT TILL THE BUTTON IS PORESSED
	str[memory] = KEY[5];                        // Store new character
		memory++;                                   // Move to next position
		str[memory] = '\0';
		lcd_gotoxy(0,0);                          // End string
		lcd_puts(str);                               // Display key on LCD
	return '2';
	}	
	if(!(HAL_GPIO_ReadPin (C3_PORT, C3_PIN))){
		while (!(HAL_GPIO_ReadPin (C3_PORT,C3_PIN))); //WAIT TILL THE BUTTON IS PORESSED
str[memory] = KEY[6];                        // Store new character
		memory++;                                   // Move to next position
		str[memory] = '\0'; 
		lcd_gotoxy(0,0);                         // End string
		lcd_puts(str);     
	return '3';
	}	
	if(!(HAL_GPIO_ReadPin (C4_PORT, C4_PIN))){
		while (!(HAL_GPIO_ReadPin (C4_PORT,C4_PIN))); //WAIT TILL THE BUTTON IS PORESSED
	str[memory] = KEY[7];                        // Store new character
		memory++;                                   // Move to next position
		str[memory] = '\0'; 
		lcd_gotoxy(0,0);                         // End string
		lcd_puts(str);     
	return 'U';
	}
		
		//	make ROW3 Low and ALL_CHANNELS other ROWs HIGH
		HAL_GPIO_WritePin (R1_PORT, R1_PIN,GPIO_PIN_SET); //PULL R1 UP
		HAL_GPIO_WritePin (R2_PORT, R2_PIN,GPIO_PIN_SET); //PULL Rx up
		HAL_GPIO_WritePin (R3_PORT, R3_PIN,GPIO_PIN_RESET);//PULL R3 LOW
		HAL_GPIO_WritePin (R4_PORT, R4_PIN,GPIO_PIN_SET); //PULL Rx up
		HAL_GPIO_WritePin (R5_PORT, R5_PIN,GPIO_PIN_SET); //PULL Rx up
		HAL_Delay(5);


	if(!(HAL_GPIO_ReadPin (C1_PORT, C1_PIN))){
		while (!(HAL_GPIO_ReadPin (C1_PORT,C1_PIN))); //WAIT TILL THE BUTTON IS PORESSED
str[memory] = KEY[8];                        // Store new character
		memory++;                                   // Move to next position
		str[memory] = '\0';  
		lcd_gotoxy(0,0);                        // End string
		lcd_puts(str);     
	return '4';
	}
	if(!(HAL_GPIO_ReadPin (C2_PORT, C2_PIN))){
		while (!(HAL_GPIO_ReadPin (C2_PORT,C2_PIN))); //WAIT TILL THE BUTTON IS PORESSED
str[memory] = KEY[9];                        // Store new character
		memory++;                                   // Move to next position
		str[memory] = '\0';  
		lcd_gotoxy(0,0);                        // End string
		lcd_puts(str);     
	return '5';
	}	
	if(!(HAL_GPIO_ReadPin (C3_PORT, C3_PIN))){
		while (!(HAL_GPIO_ReadPin (C3_PORT,C3_PIN))); //WAIT TILL THE BUTTON IS PORESSED
	str[memory] = KEY[10];                        // Store new character
		memory++;                                   // Move to next position
		str[memory] = '\0';   
		lcd_gotoxy(0,0);                       // End string
		lcd_puts(str);     
	return '6';
	}	
	if(!(HAL_GPIO_ReadPin (C4_PORT, C4_PIN))){
		while (!(HAL_GPIO_ReadPin (C4_PORT,C4_PIN))); //WAIT TILL THE BUTTON IS PORESSED
	str[memory] = KEY[11];                        // Store new character
		memory++;                                   // Move to next position
		str[memory] = '\0'; 
		lcd_gotoxy(0,0);                         // End string
		lcd_puts(str);     
	return 'D';
	}
			//	make ROW4 Low and ALL_CHANNELS other ROWs HIGH
		HAL_GPIO_WritePin (R1_PORT, R1_PIN,GPIO_PIN_SET); //PULL R1 UP
		HAL_GPIO_WritePin (R2_PORT, R2_PIN,GPIO_PIN_SET); //PULL Rx up
		HAL_GPIO_WritePin (R3_PORT, R3_PIN,GPIO_PIN_SET);//PULL R3 UP
		HAL_GPIO_WritePin (R4_PORT, R4_PIN,GPIO_PIN_RESET); //PULL R4 LOW
		HAL_GPIO_WritePin (R5_PORT, R5_PIN,GPIO_PIN_SET); //PULL Rx up
		HAL_Delay(5);


	if(!(HAL_GPIO_ReadPin (C1_PORT, C1_PIN))){
		while (!(HAL_GPIO_ReadPin (C1_PORT,C1_PIN))); //WAIT TILL THE BUTTON IS PORESSED
	str[memory] = KEY[12];                        // Store new character
		memory++;                                   // Move to next position
		str[memory] = '\0'; 
		lcd_gotoxy(0,0);                         // End string
		lcd_puts(str);                               // Display key on LCD
	return '7';
	}
	if(!(HAL_GPIO_ReadPin (C2_PORT, C2_PIN))){
		while (!(HAL_GPIO_ReadPin (C2_PORT,C2_PIN))); //WAIT TILL THE BUTTON IS PORESSED
	str[memory] = KEY[13];                        // Store new character
		memory++;                                   // Move to next position
		str[memory] = '\0';  
		lcd_gotoxy(0,0);                        // End string
		lcd_puts(str);     
	return '8';
	}	
	if(!(HAL_GPIO_ReadPin (C3_PORT, C3_PIN))){
		while (!(HAL_GPIO_ReadPin (C3_PORT,C3_PIN))); //WAIT TILL THE BUTTON IS PORESSED
	str[memory] = KEY[14];                        // Store new character
		memory++;                                   // Move to next position
		str[memory] = '\0';
		lcd_gotoxy(0,0);                          // End string
		lcd_puts(str);     
	return '9';
	}	
	if(!(HAL_GPIO_ReadPin (C4_PORT, C4_PIN))){
		while (!(HAL_GPIO_ReadPin (C4_PORT,C4_PIN))); //WAIT TILL THE BUTTON IS PORESSED
str[memory] = KEY[15];                        // Store new character
		memory++;                                   // Move to next position
		str[memory] = '\0';
		lcd_gotoxy(0,0);                          // End string
		lcd_puts(str);     
	return 'E';
	}	
			//	make ROW5 Low and ALL_CHANNELS other ROWs HIGH
		HAL_GPIO_WritePin (R1_PORT, R1_PIN,GPIO_PIN_SET); //PULL R1 UP
		HAL_GPIO_WritePin (R2_PORT, R2_PIN,GPIO_PIN_SET); //PULL Rx up
		HAL_GPIO_WritePin (R3_PORT, R3_PIN,GPIO_PIN_SET);//PULL R3 UP
		HAL_GPIO_WritePin (R4_PORT, R4_PIN,GPIO_PIN_SET); //PULL Rx up
		HAL_GPIO_WritePin (R5_PORT, R5_PIN,GPIO_PIN_RESET); //PULL R5 LOW
		HAL_Delay(5);


	if(!(HAL_GPIO_ReadPin (C1_PORT, C1_PIN))){
	str[memory] = KEY[16];                        // Store new character
		memory++;                                   // Move to next position
		str[memory] = '\0';  
		lcd_gotoxy(0,0);                        // End string
		lcd_puts(str);     
	return 'L';
	}
	if(!(HAL_GPIO_ReadPin (C2_PORT, C2_PIN))){
		while (!(HAL_GPIO_ReadPin (C2_PORT,C2_PIN))); //WAIT TILL THE BUTTON IS PORESSED
	str[memory] = KEY[17];                        // Store new character
		memory++;                                   // Move to next position
		str[memory] = '\0';
		lcd_gotoxy(0,0);                          // End string
		lcd_puts(str);     
	return '0';
	}	
	if(!(HAL_GPIO_ReadPin (C3_PORT, C3_PIN))){
		while (!(HAL_GPIO_ReadPin (C3_PORT,C3_PIN))); //WAIT TILL THE BUTTON IS PORESSED
	str[memory] = KEY[18];                        // Store new character
		memory++;                                   // Move to next position
		str[memory] = '\0';  
		lcd_gotoxy(0,0);                        // End string
		lcd_puts(str);     
	return 'R';
	}	
	if(!(HAL_GPIO_ReadPin (C4_PORT, C4_PIN))){
		while (!(HAL_GPIO_ReadPin (C4_PORT,C4_PIN))); //WAIT TILL THE BUTTON IS PORESSED
	str[memory] = KEY[19];                        // Store new character
		memory++;                                   // Move to next position
		str[memory] = '\0'; 
		lcd_gotoxy(0,0);                         // End string
		lcd_puts(str);     
	return 'T';

	}


	return 'N';
		
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
		MX_USART1_UART_Init();
		/* USER CODE BEGIN 2 */
	 lcd_init();                  // Initialize LCD

	 lcd_clear();                 // Clear LCD display
	 
		/* USER CODE END 2 */

		/* Infinite loop */
		/* USER CODE BEGIN WHILE */
		while (1)
		{
			/* USER CODE END WHILE */
	key = read_keypad();
			
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
		* @brief USART1 Initialization Function
		* @param None
		* @retval None
		*/
	static void MX_USART1_UART_Init(void)
	{

		/* USER CODE BEGIN USART1_Init 0 */

		/* USER CODE END USART1_Init 0 */

		/* USER CODE BEGIN USART1_Init 1 */

		/* USER CODE END USART1_Init 1 */
		huart1.Instance = USART1;
		huart1.Init.BaudRate = 115200;
		huart1.Init.WordLength = UART_WORDLENGTH_8B;
		huart1.Init.StopBits = UART_STOPBITS_1;
		huart1.Init.Parity = UART_PARITY_NONE;
		huart1.Init.Mode = UART_MODE_TX_RX;
		huart1.Init.HwFlowCtl = UART_HWCONTROL_NONE;
		huart1.Init.OverSampling = UART_OVERSAMPLING_16;
		if (HAL_UART_Init(&huart1) != HAL_OK)
		{
			Error_Handler();
		}
		/* USER CODE BEGIN USART1_Init 2 */

		/* USER CODE END USART1_Init 2 */

	}

	/**
		* @brief GPIO Initialization Function
		* @param None
		* @retval None
		*/
	static void MX_GPIO_Init(void)
	{
		GPIO_InitTypeDef GPIO_InitStruct = {0};
	/* USER CODE BEGIN MX_GPIO_Init_1 */
	/* USER CODE END MX_GPIO_Init_1 */

		/* GPIO Ports Clock Enable */
		__HAL_RCC_GPIOD_CLK_ENABLE();
		__HAL_RCC_GPIOA_CLK_ENABLE();
		__HAL_RCC_GPIOB_CLK_ENABLE();

		/*Configure GPIO pin Output Level */
		HAL_GPIO_WritePin(GPIOA, GPIO_PIN_0|GPIO_PIN_1|GPIO_PIN_2|GPIO_PIN_3
														|GPIO_PIN_4|GPIO_PIN_5|GPIO_PIN_6|GPIO_PIN_7
														|GPIO_PIN_8|GPIO_PIN_9|GPIO_PIN_10|GPIO_PIN_11
														|GPIO_PIN_12, GPIO_PIN_RESET);

		/*Configure GPIO pin Output Level */
		HAL_GPIO_WritePin(GPIOB, GPIO_PIN_0|GPIO_PIN_1|GPIO_PIN_2, GPIO_PIN_RESET);

		/*Configure GPIO pins : PA0 PA1 PA2 PA3
														 PA4 PA5 PA6 PA7
														 PA8 PA9 PA10 PA11
														 PA12 */
		GPIO_InitStruct.Pin = GPIO_PIN_0|GPIO_PIN_1|GPIO_PIN_2|GPIO_PIN_3
														|GPIO_PIN_4|GPIO_PIN_5|GPIO_PIN_6|GPIO_PIN_7
														|GPIO_PIN_8|GPIO_PIN_9|GPIO_PIN_10|GPIO_PIN_11
														|GPIO_PIN_12;
		GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
		GPIO_InitStruct.Pull = GPIO_NOPULL;
		GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
		HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

		/*Configure GPIO pins : PB0 PB1 PB2 */
		GPIO_InitStruct.Pin = GPIO_PIN_0|GPIO_PIN_1|GPIO_PIN_2;
		GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
		GPIO_InitStruct.Pull = GPIO_NOPULL;
		GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
		HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);

		/*Configure GPIO pin : PA15 */
		GPIO_InitStruct.Pin = GPIO_PIN_15;
		GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
		GPIO_InitStruct.Pull = GPIO_PULLUP;
		HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

		/*Configure GPIO pins : PB3 PB4 PB5 */
		GPIO_InitStruct.Pin = GPIO_PIN_3|GPIO_PIN_4|GPIO_PIN_5;
		GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
		GPIO_InitStruct.Pull = GPIO_PULLUP;
		HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);

	/* USER CODE BEGIN MX_GPIO_Init_2 */
	/* USER CODE END MX_GPIO_Init_2 */
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
