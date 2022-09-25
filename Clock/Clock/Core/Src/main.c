
#include "main.h"

ADC_HandleTypeDef hadc1;

int D1 = 0x70;
int D2 = 0x60;
int D3 = 0x50;
int D4 = 0x40;
int D5 = 0x30;
int D6 = 0x20;
int D7 = 0x10;
int D8 = 0x00;

void SystemClock_Config(void);
static void MX_GPIO_Init(void);
static void MX_ADC1_Init(void);
void displayNumber(int valor);
void setDisplay(int dig1, int dig2, int dig3, int dig4, int dig5, int dig6, int dig7, int dig8);
void setDisplay_reloj(int dig1, int dig2, int dig4, int dig5, int dig7, int dig8);
void displayReloj(int segundos, int minutos, int horas);

uint32_t ADCValue = 0;
uint32_t VP_segundos = 0;
uint32_t VP_minutos = 0;
uint32_t VP_horas = 0;

uint32_t segundos_antes = 0;

uint32_t segundos = 0;
uint32_t minutos = 0;
uint32_t horas = 0;

int contador = 0;
int numero = 0;

int numeros[10] = {0x00, 0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07, 0x08, 0x09};

int main(void)
{

  HAL_Init();

  SystemClock_Config();

  MX_GPIO_Init();
  MX_ADC1_Init();

  while (1)
  {

	  HAL_ADC_Start(&hadc1);
	    if(HAL_ADC_PollForConversion(&hadc1, 5)==HAL_OK)
	    {
	 	   ADCValue=HAL_ADC_GetValue(&hadc1);
	    }
	    HAL_ADC_Stop(&hadc1);

	    VP_segundos = (ADCValue*59)/4095;
	    VP_minutos = (ADCValue*59)/4095;
	    VP_horas = (ADCValue*23)/4095;

	    if(contador == 0)
	    {
	    	displayNumber(0);
	    }

	    else if(contador == 1)
		{
			segundos = VP_segundos;
			displayNumber(segundos);
		}else if(contador == 2)
		{
			minutos = VP_minutos;
			displayNumber(minutos);
		}else if(contador == 3)
		{
			horas = VP_horas;
			displayNumber(horas);
		}else if(contador == 4)
		{
			displayReloj(segundos, minutos, horas);

			if(segundos_antes <= 59)
			{
				segundos_antes++;
			}
			else if(segundos < 59)
			{
				segundos_antes=0;
				segundos++;

			}else if (minutos < 59)
			{
				segundos = 0;
				minutos++;


			}else if(horas < 23)
			{
				minutos = 0;
				horas++;

			}else
			{
				segundos = 0;
				minutos = 0;
				horas = 0;
			}
		}

  }

}



void displayReloj(int segundos, int minutos, int horas)
{
	int dig1,dig2,dig4,dig5,dig7,dig8;

	    dig8=segundos%10;
	    dig7=(segundos%100)/10;
	    dig5=(minutos%10);
	    dig4=(minutos%100)/10;
	    dig2=(horas%10);
	    dig1=(horas%100)/10;

	    setDisplay_reloj(dig1, dig2, dig4, dig5, dig7, dig8);

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

void setDisplay_reloj(int dig1, int dig2, int dig4, int dig5,int dig7,int dig8)
  {

    GPIOC->ODR=D8+numeros[dig8];// Unidades
    HAL_Delay(1);
    GPIOC->ODR=D7+numeros[dig7];// Decenas
    HAL_Delay(1);
    GPIOC->ODR=D5+numeros[dig5];
    HAL_Delay(1);
    GPIOC->ODR=D4+numeros[dig4];
    HAL_Delay(1);
    GPIOC->ODR=D2+numeros[dig2];
    HAL_Delay(1);
    GPIOC->ODR=D1+numeros[dig1];
    HAL_Delay(1);

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
  * @brief ADC1 Initialization Function
  * @param None
  * @retval None
  */
static void MX_ADC1_Init(void)
{

  /* USER CODE BEGIN ADC1_Init 0 */

  /* USER CODE END ADC1_Init 0 */

  ADC_ChannelConfTypeDef sConfig = {0};

  /* USER CODE BEGIN ADC1_Init 1 */

  /* USER CODE END ADC1_Init 1 */

  /** Configure the global features of the ADC (Clock, Resolution, Data Alignment and number of conversion)
  */
  hadc1.Instance = ADC1;
  hadc1.Init.ClockPrescaler = ADC_CLOCK_SYNC_PCLK_DIV2;
  hadc1.Init.Resolution = ADC_RESOLUTION_12B;
  hadc1.Init.ScanConvMode = DISABLE;
  hadc1.Init.ContinuousConvMode = DISABLE;
  hadc1.Init.DiscontinuousConvMode = DISABLE;
  hadc1.Init.ExternalTrigConvEdge = ADC_EXTERNALTRIGCONVEDGE_NONE;
  hadc1.Init.ExternalTrigConv = ADC_SOFTWARE_START;
  hadc1.Init.DataAlign = ADC_DATAALIGN_RIGHT;
  hadc1.Init.NbrOfConversion = 1;
  hadc1.Init.DMAContinuousRequests = DISABLE;
  hadc1.Init.EOCSelection = ADC_EOC_SINGLE_CONV;
  if (HAL_ADC_Init(&hadc1) != HAL_OK)
  {
    Error_Handler();
  }

  /** Configure for the selected ADC regular channel its corresponding rank in the sequencer and its sample time.
  */
  sConfig.Channel = ADC_CHANNEL_0;
  sConfig.Rank = 1;
  sConfig.SamplingTime = ADC_SAMPLETIME_3CYCLES;
  if (HAL_ADC_ConfigChannel(&hadc1, &sConfig) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN ADC1_Init 2 */

  /* USER CODE END ADC1_Init 2 */

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

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOC, GPIO_PIN_0|GPIO_PIN_1|GPIO_PIN_2|GPIO_PIN_3
                          |GPIO_PIN_4|GPIO_PIN_5|GPIO_PIN_6|GPIO_PIN_7, GPIO_PIN_RESET);

  /*Configure GPIO pin : PC13 */
  GPIO_InitStruct.Pin = GPIO_PIN_13;
  GPIO_InitStruct.Mode = GPIO_MODE_IT_RISING;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  HAL_GPIO_Init(GPIOC, &GPIO_InitStruct);

  /*Configure GPIO pins : PC0 PC1 PC2 PC3
                           PC4 PC5 PC6 PC7 */
  GPIO_InitStruct.Pin = GPIO_PIN_0|GPIO_PIN_1|GPIO_PIN_2|GPIO_PIN_3
                          |GPIO_PIN_4|GPIO_PIN_5|GPIO_PIN_6|GPIO_PIN_7;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOC, &GPIO_InitStruct);

  /*Configure GPIO pin : PC8 */
  GPIO_InitStruct.Pin = GPIO_PIN_8;
  GPIO_InitStruct.Mode = GPIO_MODE_ANALOG;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  HAL_GPIO_Init(GPIOC, &GPIO_InitStruct);

  /* EXTI interrupt init*/
  HAL_NVIC_SetPriority(EXTI15_10_IRQn, 0, 0);
  HAL_NVIC_EnableIRQ(EXTI15_10_IRQn);

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
