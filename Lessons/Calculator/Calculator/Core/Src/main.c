
#include "main.h"

int D8=0x00;
int D7=0x10;
int D6=0x20;
int D5=0x30;
int D4=0x40;
int D3=0x50;
int D2=0x60;
int D1=0x70;

int decodificar, contador, acumulado, total;
uint32_t tecla, teclado;

void SystemClock_Config(void);
static void MX_GPIO_Init(void);

void displayNumber(int numero);
void setDisplay(int dig1, int dig2, int dig3, int dig4, int dig5, int dig6, int dig7, int dig8);
void decodificarTeclado(void);
int numeros[10]={0x0,0x1,0x2,0x3,0x4,0x5,0x6,0x7,0x8,0x9};

int main(void)
{

  HAL_Init();

  SystemClock_Config();

  MX_GPIO_Init();

  GPIOA->ODR=0xF0;

  while (1)
  {
	  displayNumber(teclado);
  }

}

void displayNumber(int valor)
  {
    int dig1,dig2,dig3,dig4,dig5,dig6,dig7,dig8;

    dig8=valor%10; //Unidades (8)
    dig7=(valor%100)/10; //Decenas (7)
    dig6=(valor%1000)/100; //Centenas (6)
    dig5=(valor%10000)/1000; //millares almacenar el (5)
    dig4=(valor%100000)/10000;//Decenas de millares (4)
    dig3=(valor%1000000)/100000;//Centenas de millares (3)
    dig2=(valor%10000000)/1000000; //Millones        (2)
    dig1=(valor%100000000)/10000000;//Decenas de millones (1)

    setDisplay(dig1, dig2, dig3, dig4, dig5, dig6, dig7, dig8);
  }

void setDisplay(int dig1, int dig2, int dig3, int dig4, int dig5,int dig6,int dig7,int dig8)
{

    GPIOC->ODR=D8+numeros[dig8];// Unidades
    HAL_Delay(1);
    GPIOC->ODR=D7+numeros[dig7];// Decenas
    HAL_Delay(1);
    GPIOC->ODR=D6+numeros[dig6];
    HAL_Delay(1);
    GPIOC->ODR=D5+numeros[dig5];
    HAL_Delay(1);
    GPIOC->ODR=D4+numeros[dig4];
    HAL_Delay(1);
    GPIOC->ODR=D3+numeros[dig3];
    HAL_Delay(1);
    GPIOC->ODR=D2+numeros[dig2];
    HAL_Delay(1);
    GPIOC->ODR=D1+numeros[dig1];
    HAL_Delay(1);

}


void decodificarTeclado(void)
{

	switch(decodificar)
	{
	case 0:
		HAL_GPIO_WritePin(GPIOA, GPIO_PIN_4, GPIO_PIN_SET);
		if(HAL_GPIO_ReadPin(GPIOA, GPIO_PIN_0) == 1)
		{
			tecla = 1;
		}

		HAL_GPIO_WritePin(GPIOA, GPIO_PIN_4, GPIO_PIN_RESET);
		HAL_GPIO_WritePin(GPIOA, GPIO_PIN_5, GPIO_PIN_SET);
		if(HAL_GPIO_ReadPin(GPIOA, GPIO_PIN_0) == 1)
		{
			tecla = 2;
		}

		HAL_GPIO_WritePin(GPIOA, GPIO_PIN_5, GPIO_PIN_RESET);
		HAL_GPIO_WritePin(GPIOA, GPIO_PIN_6, GPIO_PIN_SET);
		if(HAL_GPIO_ReadPin(GPIOA, GPIO_PIN_0) == 1)
		{
			tecla = 3;
		}
		HAL_GPIO_WritePin(GPIOA, GPIO_PIN_6, GPIO_PIN_RESET);
		HAL_GPIO_WritePin(GPIOA, GPIO_PIN_7, GPIO_PIN_SET);
		if(HAL_GPIO_ReadPin(GPIOA, GPIO_PIN_0) == 1)
		{
			contador = 1;
			tecla = 0;
			acumulado = teclado;
			teclado = 0;;
		}

		teclado = (teclado%100000000)*10 + tecla;
		GPIOA->ODR = 0xF0;
		break;

	case 1:
		HAL_GPIO_WritePin(GPIOA, GPIO_PIN_4, GPIO_PIN_SET);
		if(HAL_GPIO_ReadPin(GPIOA, GPIO_PIN_1) == 1)
		{
			tecla = 4;
		}

		HAL_GPIO_WritePin(GPIOA, GPIO_PIN_4, GPIO_PIN_RESET);
		HAL_GPIO_WritePin(GPIOA, GPIO_PIN_5, GPIO_PIN_SET);
		if(HAL_GPIO_ReadPin(GPIOA, GPIO_PIN_1) == 1)
		{
			tecla = 5;
		}

		HAL_GPIO_WritePin(GPIOA, GPIO_PIN_5, GPIO_PIN_RESET);
		HAL_GPIO_WritePin(GPIOA, GPIO_PIN_6, GPIO_PIN_SET);
		if(HAL_GPIO_ReadPin(GPIOA, GPIO_PIN_1) == 1)
  {
			tecla = 6;
		}

		HAL_GPIO_WritePin(GPIOA, GPIO_PIN_6, GPIO_PIN_RESET);
		HAL_GPIO_WritePin(GPIOA, GPIO_PIN_7, GPIO_PIN_SET);
		if(HAL_GPIO_ReadPin(GPIOA, GPIO_PIN_1) == 1)
		{
			contador = 2;
			tecla = 0;
			acumulado = teclado;
			teclado = 0;;
  }

		teclado = (teclado%100000000)*10 + tecla;
		GPIOA->ODR = 0xF0;
		break;

	case 2:
		HAL_GPIO_WritePin(GPIOA, GPIO_PIN_4, GPIO_PIN_SET);
		if(HAL_GPIO_ReadPin(GPIOB, GPIO_PIN_4) == 1)
		{
			tecla = 7;
}

		HAL_GPIO_WritePin(GPIOA, GPIO_PIN_4, GPIO_PIN_RESET);
		HAL_GPIO_WritePin(GPIOA, GPIO_PIN_5, GPIO_PIN_SET);
		if(HAL_GPIO_ReadPin(GPIOB, GPIO_PIN_4) == 1)
		{
			tecla = 8;
		}

		HAL_GPIO_WritePin(GPIOA, GPIO_PIN_5, GPIO_PIN_RESET);
		HAL_GPIO_WritePin(GPIOA, GPIO_PIN_6, GPIO_PIN_SET);
		if(HAL_GPIO_ReadPin(GPIOB, GPIO_PIN_4) == 1)
		{
			tecla = 9;
		}

		HAL_GPIO_WritePin(GPIOA, GPIO_PIN_6, GPIO_PIN_RESET);
		HAL_GPIO_WritePin(GPIOA, GPIO_PIN_7, GPIO_PIN_SET);
		if(HAL_GPIO_ReadPin(GPIOB, GPIO_PIN_4) == 1)
		{
			contador = 3;
			tecla = 0;
			acumulado = teclado;
			teclado = 0;;
		}
		teclado = (teclado%100000000)*10 + tecla;
		GPIOA->ODR = 0xF0;
		break;

	case 3:
		HAL_GPIO_WritePin(GPIOA, GPIO_PIN_4, GPIO_PIN_SET);
		if(HAL_GPIO_ReadPin(GPIOB, GPIO_PIN_5) == 1)
		{
			total= 0;
			contador = 0;
			teclado = 0;
			acumulado = 0;
		}

		HAL_GPIO_WritePin(GPIOA, GPIO_PIN_4, GPIO_PIN_RESET);
		HAL_GPIO_WritePin(GPIOA, GPIO_PIN_5, GPIO_PIN_SET);
		if(HAL_GPIO_ReadPin(GPIOB, GPIO_PIN_5) == 1)
		{
			tecla = 0;
			total = (teclado%100000000)*10 + tecla;
		}

		HAL_GPIO_WritePin(GPIOA, GPIO_PIN_5, GPIO_PIN_RESET);
		HAL_GPIO_WritePin(GPIOA, GPIO_PIN_6, GPIO_PIN_SET);
		if(HAL_GPIO_ReadPin(GPIOB, GPIO_PIN_5) == 1)
		{
			if(contador == 1)
			{
				total = teclado + acumulado;
				contador = 0;
			}
			if(contador == 2)
			{
				total = acumulado - teclado;
				contador = 0;
			}
			if(contador == 3)
			{
				total = acumulado * teclado;
				contador = 0;
			}
			if(contador == 4)
			{
				total = acumulado / teclado;
				contador = 0;
			}

		}

		HAL_GPIO_WritePin(GPIOA, GPIO_PIN_6, GPIO_PIN_RESET);
		HAL_GPIO_WritePin(GPIOA, GPIO_PIN_7, GPIO_PIN_SET);
		if(HAL_GPIO_ReadPin(GPIOB, GPIO_PIN_5) == 1)
		{
			contador = 4;
			tecla = 0;
			acumulado = teclado;
			teclado = 0;
			total = 0;
		}

		teclado = total;
		GPIOA->ODR = 0xF0;
		break;

	}
}

void SystemClock_Config(void)
{
  RCC_OscInitTypeDef RCC_OscInitStruct = {0};
  RCC_ClkInitTypeDef RCC_ClkInitStruct = {0};

  /** Configure the main internal regulator output voltage
  */
  __HAL_RCC_PWR_CLK_ENABLE();
  __HAL_PWR_VOLTAGESCALING_CONFIG(PWR_REGULATOR_VOLTAGE_SCALE2);

  /** Initializes the RCC Oscillators according to the specified parameters
  * in the RCC_OscInitTypeDef structure.
  */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSI;
  RCC_OscInitStruct.HSIState = RCC_HSI_ON;
  RCC_OscInitStruct.HSICalibrationValue = RCC_HSICALIBRATION_DEFAULT;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_NONE;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    Error_Handler();
  }

  /** Initializes the CPU, AHB and APB buses clocks
  */
  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
                              |RCC_CLOCKTYPE_PCLK1|RCC_CLOCKTYPE_PCLK2;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_HSI;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV1;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV1;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_0) != HAL_OK)
  {
    Error_Handler();
  }
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
  __HAL_RCC_GPIOA_CLK_ENABLE();
  __HAL_RCC_GPIOB_CLK_ENABLE();

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOC, GPIO_PIN_0|GPIO_PIN_1|GPIO_PIN_2|GPIO_PIN_3
                          |GPIO_PIN_4|GPIO_PIN_5|GPIO_PIN_6|GPIO_PIN_7
                          |GPIO_PIN_8, GPIO_PIN_RESET);

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOA, GPIO_PIN_4|GPIO_PIN_5|GPIO_PIN_6|GPIO_PIN_7, GPIO_PIN_RESET);

  /*Configure GPIO pins : PC0 PC1 PC2 PC3
                           PC4 PC5 PC6 PC7
                           PC8 */
  GPIO_InitStruct.Pin = GPIO_PIN_0|GPIO_PIN_1|GPIO_PIN_2|GPIO_PIN_3
                          |GPIO_PIN_4|GPIO_PIN_5|GPIO_PIN_6|GPIO_PIN_7
                          |GPIO_PIN_8;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOC, &GPIO_InitStruct);

  /*Configure GPIO pins : PA0 PA1 */
  GPIO_InitStruct.Pin = GPIO_PIN_0|GPIO_PIN_1;
  GPIO_InitStruct.Mode = GPIO_MODE_IT_RISING;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

  /*Configure GPIO pins : PA4 PA5 PA6 PA7 */
  GPIO_InitStruct.Pin = GPIO_PIN_4|GPIO_PIN_5|GPIO_PIN_6|GPIO_PIN_7;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

  /*Configure GPIO pins : PB4 PB5 */
  GPIO_InitStruct.Pin = GPIO_PIN_4|GPIO_PIN_5;
  GPIO_InitStruct.Mode = GPIO_MODE_IT_RISING;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);

  /* EXTI interrupt init*/
  HAL_NVIC_SetPriority(EXTI0_IRQn, 0, 0);
  HAL_NVIC_EnableIRQ(EXTI0_IRQn);

  HAL_NVIC_SetPriority(EXTI1_IRQn, 0, 0);
  HAL_NVIC_EnableIRQ(EXTI1_IRQn);

  HAL_NVIC_SetPriority(EXTI4_IRQn, 0, 0);
  HAL_NVIC_EnableIRQ(EXTI4_IRQn);

  HAL_NVIC_SetPriority(EXTI9_5_IRQn, 0, 0);
  HAL_NVIC_EnableIRQ(EXTI9_5_IRQn);

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
