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

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include <string.h>
#include <stdio.h>
/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */

/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */
/* The fixed message shown in Chrome - change this text if you like */
#define WEB_MESSAGE "Hello from Gracia and chinmayi!"
/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/
UART_HandleTypeDef huart1;
UART_HandleTypeDef huart2;

/* USER CODE BEGIN PV */
char req[1024];     /* data received from the ESP8266 */
char page[512];     /* HTTP reply sent to Chrome      */
char cmd[40];       /* AT command buffer              */
uint16_t n;
/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
static void MX_GPIO_Init(void);
static void MX_USART1_UART_Init(void);
static void MX_USART2_UART_Init(void);
/* USER CODE BEGIN PFP */

/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */

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
  MX_USART2_UART_Init();
  /* USER CODE BEGIN 2 */

  uint8_t buf[512];
  uint16_t len;

  /* 2. AT */
  char cmd1[] = "AT\r\n";
  len = 0;
  HAL_UART_Transmit(&huart1, (uint8_t *)cmd1, strlen(cmd1), HAL_MAX_DELAY);
  while (len < sizeof(buf) && HAL_UART_Receive(&huart1, &buf[len], 1, 100) == HAL_OK)
  {
    len++;
  }
  HAL_UART_Transmit(&huart2, buf, len, HAL_MAX_DELAY);
  HAL_Delay(500);

  /* 3. Station mode */
  char cmd2[] = "AT+CWMODE=1\r\n";
  len = 0;
  HAL_UART_Transmit(&huart1, (uint8_t *)cmd2, strlen(cmd2), HAL_MAX_DELAY);
  while (len < sizeof(buf) && HAL_UART_Receive(&huart1, &buf[len], 1, 100) == HAL_OK)
  {
    len++;
  }
  HAL_UART_Transmit(&huart2, buf, len, HAL_MAX_DELAY);
  HAL_Delay(500);

  /* 4. DHCP */
  char cmd5[] = "AT+CWDHCP=1,1\r\n";
  len = 0;
  HAL_UART_Transmit(&huart1, (uint8_t *)cmd5, strlen(cmd5), HAL_MAX_DELAY);
  while (len < sizeof(buf) && HAL_UART_Receive(&huart1, &buf[len], 1, 100) == HAL_OK)
  {
    len++;
  }
  HAL_UART_Transmit(&huart2, buf, len, HAL_MAX_DELAY);
  HAL_Delay(500);

  /* 5. Join Wi-Fi (slow, so 5 s gap allowed) */
  char cmd3[] = "AT+CWJAP=\"SNUC\",\"snu12345\"\r\n";
  len = 0;
  HAL_UART_Transmit(&huart1, (uint8_t *)cmd3, strlen(cmd3), HAL_MAX_DELAY);
  while (len < sizeof(buf) && HAL_UART_Receive(&huart1, &buf[len], 1, 5000) == HAL_OK)
  {
    len++;
  }
  HAL_UART_Transmit(&huart2, buf, len, HAL_MAX_DELAY);
  HAL_Delay(500);

  /* 6. Get IP */
  char cmd4[] = "AT+CIFSR\r\n";
  len = 0;
  HAL_UART_Transmit(&huart1, (uint8_t *)cmd4, strlen(cmd4), HAL_MAX_DELAY);
  while (len < sizeof(buf) && HAL_UART_Receive(&huart1, &buf[len], 1, 100) == HAL_OK)
  {
    len++;
  }
  HAL_UART_Transmit(&huart2, buf, len, HAL_MAX_DELAY);
  HAL_Delay(500);

  /* 7. Multiple connections */
  char cmd6[] = "AT+CIPMUX=1\r\n";
  len = 0;
  HAL_UART_Transmit(&huart1, (uint8_t *)cmd6, strlen(cmd6), HAL_MAX_DELAY);
  while (len < sizeof(buf) && HAL_UART_Receive(&huart1, &buf[len], 1, 100) == HAL_OK)
  {
    len++;
  }
  HAL_UART_Transmit(&huart2, buf, len, HAL_MAX_DELAY);
  HAL_Delay(500);

  /* 8. Start server on port 80 */
  char cmd7[] = "AT+CIPSERVER=1,80\r\n";
  len = 0;
  HAL_UART_Transmit(&huart1, (uint8_t *)cmd7, strlen(cmd7), HAL_MAX_DELAY);
  while (len < sizeof(buf) && HAL_UART_Receive(&huart1, &buf[len], 1, 100) == HAL_OK)
  {
    len++;
  }
  HAL_UART_Transmit(&huart2, buf, len, HAL_MAX_DELAY);
  HAL_Delay(500);

  /* Build the fixed web page once - it never changes */
  sprintf(page,
          "HTTP/1.1 200 OK\r\n"
          "Content-Type: text/html\r\n"
          "Connection: close\r\n"
          "\r\n"
          "<html><body><h1>%s</h1></body></html>", WEB_MESSAGE);

  char ready[] = "\r\n>>> Server ready. Open the IP address in Chrome.\r\n";
  HAL_UART_Transmit(&huart2, (uint8_t *)ready, strlen(ready), HAL_MAX_DELAY);

  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
  while (1)
  {
    /* USER CODE END WHILE */

    /* USER CODE BEGIN 3 */

    /* ---------- 1. Wait for Chrome's request (+IPD) ---------- */
    HAL_UART_Receive(&huart1, (uint8_t *)&req[0], 1, HAL_MAX_DELAY); /* wait for first byte */
    n = 1;
    while (n < sizeof(req) - 1 && HAL_UART_Receive(&huart1, (uint8_t *)&req[n], 1, 200) == HAL_OK)
    {
      n++;
    }
    req[n] = '\0';
    HAL_UART_Transmit(&huart2, (uint8_t *)req, n, HAL_MAX_DELAY);    /* show request on PC */

    char *ipd = strstr(req, "+IPD,");
    if (ipd == NULL)
    {
      continue;                 /* not a request (e.g. "0,CONNECT" or "0,CLOSED") */
    }
    char id = ipd[5];           /* link ID: '0', '1', ... */

    /* Chrome also asks for /favicon.ico - just close that one */
    if (strstr(req, "favicon") != NULL)
    {
      sprintf(cmd, "AT+CIPCLOSE=%c\r\n", id);
      HAL_UART_Transmit(&huart1, (uint8_t *)cmd, strlen(cmd), HAL_MAX_DELAY);
      n = 0;
      while (n < sizeof(req) - 1 && HAL_UART_Receive(&huart1, (uint8_t *)&req[n], 1, 500) == HAL_OK)
      {
        n++;
      }
      continue;
    }

    /* ---------- 2. AT+CIPSEND=id,length -> wait for '>' ---------- */
    sprintf(cmd, "AT+CIPSEND=%c,%d\r\n", id, (int)strlen(page));
    HAL_UART_Transmit(&huart1, (uint8_t *)cmd, strlen(cmd), HAL_MAX_DELAY);
    n = 0;
    while (n < sizeof(req) - 1 && HAL_UART_Receive(&huart1, (uint8_t *)&req[n], 1, 500) == HAL_OK)
    {
      n++;
    }
    HAL_UART_Transmit(&huart2, (uint8_t *)req, n, HAL_MAX_DELAY);    /* shows "OK" and ">" */

    /* ---------- 3. Send the fixed page -> wait for SEND OK ---------- */
    HAL_UART_Transmit(&huart1, (uint8_t *)page, strlen(page), HAL_MAX_DELAY);
    n = 0;
    while (n < sizeof(req) - 1 && HAL_UART_Receive(&huart1, (uint8_t *)&req[n], 1, 1000) == HAL_OK)
    {
      n++;
    }
    HAL_UART_Transmit(&huart2, (uint8_t *)req, n, HAL_MAX_DELAY);    /* shows "SEND OK" */

    /* ---------- 4. Close the connection so Chrome shows the page ---------- */
    sprintf(cmd, "AT+CIPCLOSE=%c\r\n", id);
    HAL_UART_Transmit(&huart1, (uint8_t *)cmd, strlen(cmd), HAL_MAX_DELAY);
    n = 0;
    while (n < sizeof(req) - 1 && HAL_UART_Receive(&huart1, (uint8_t *)&req[n], 1, 500) == HAL_OK)
    {
      n++;
    }
    HAL_UART_Transmit(&huart2, (uint8_t *)req, n, HAL_MAX_DELAY);    /* shows "0,CLOSED" */
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
  huart2.Init.BaudRate = 115200;
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
  /* USER CODE BEGIN MX_GPIO_Init_1 */

  /* USER CODE END MX_GPIO_Init_1 */

  /* GPIO Ports Clock Enable */
  __HAL_RCC_GPIOD_CLK_ENABLE();
  __HAL_RCC_GPIOA_CLK_ENABLE();

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
#ifdef USE_FULL_ASSERT
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