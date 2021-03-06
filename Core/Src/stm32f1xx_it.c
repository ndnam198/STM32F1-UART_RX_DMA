/* USER CODE BEGIN Header */
/**
 ******************************************************************************
 * @file    stm32f1xx_it.c
 * @brief   Interrupt Service Routines.
 ******************************************************************************
 * @attention
 *
 * <h2><center>&copy; Copyright (c) 2020 STMicroelectronics.
 * All rights reserved.</center></h2>
 *
 * This software component is licensed by ST under Ultimate Liberty license
 * SLA0044, the "License"; You may not use this file except in compliance with
 * the License. You may obtain a copy of the License at:
 *                             www.st.com/SLA0044
 *
 ******************************************************************************
 */
/* USER CODE END Header */

/* Includes ------------------------------------------------------------------*/
#include "main.h"
#include "stm32f1xx_it.h"
/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN TD */

/* USER CODE END TD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */

/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/
/* USER CODE BEGIN PV */
extern volatile uint16_t NumberOfBytesReceive;
extern volatile uint8_t UART_Buffer[UART_RX_BUFFER_SIZE];
extern volatile uint8_t posBufferOld;
extern volatile uint8_t posBufferNew;

/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
/* USER CODE BEGIN PFP */

extern void vUSART_Check(void);
extern void vUSART_ProcessData(uint8_t *data, size_t len);

/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */

/* USER CODE END 0 */

/* External variables --------------------------------------------------------*/
extern TIM_HandleTypeDef htim4;

/* USER CODE BEGIN EV */

/* USER CODE END EV */

/******************************************************************************/
/*           Cortex-M3 Processor Interruption and Exception Handlers          */
/******************************************************************************/
/**
 * @brief This function handles Non maskable interrupt.
 */
void NMI_Handler(void) {
	/* USER CODE BEGIN NonMaskableInt_IRQn 0 */

	/* USER CODE END NonMaskableInt_IRQn 0 */
	/* USER CODE BEGIN NonMaskableInt_IRQn 1 */

	/* USER CODE END NonMaskableInt_IRQn 1 */
}

/**
 * @brief This function handles Hard fault interrupt.
 */
void HardFault_Handler(void) {
	/* USER CODE BEGIN HardFault_IRQn 0 */

	/* USER CODE END HardFault_IRQn 0 */
	while (1) {
		/* USER CODE BEGIN W1_HardFault_IRQn 0 */
		/* USER CODE END W1_HardFault_IRQn 0 */
	}
}

/**
 * @brief This function handles Memory management fault.
 */
void MemManage_Handler(void) {
	/* USER CODE BEGIN MemoryManagement_IRQn 0 */

	/* USER CODE END MemoryManagement_IRQn 0 */
	while (1) {
		/* USER CODE BEGIN W1_MemoryManagement_IRQn 0 */
		/* USER CODE END W1_MemoryManagement_IRQn 0 */
	}
}

/**
 * @brief This function handles Prefetch fault, memory access fault.
 */
void BusFault_Handler(void) {
	/* USER CODE BEGIN BusFault_IRQn 0 */

	/* USER CODE END BusFault_IRQn 0 */
	while (1) {
		/* USER CODE BEGIN W1_BusFault_IRQn 0 */
		/* USER CODE END W1_BusFault_IRQn 0 */
	}
}

/**
 * @brief This function handles Undefined instruction or illegal state.
 */
void UsageFault_Handler(void) {
	/* USER CODE BEGIN UsageFault_IRQn 0 */

	/* USER CODE END UsageFault_IRQn 0 */
	while (1) {
		/* USER CODE BEGIN W1_UsageFault_IRQn 0 */
		/* USER CODE END W1_UsageFault_IRQn 0 */
	}
}

/**
 * @brief This function handles System service call via SWI instruction.
 */
void SVC_Handler(void) {
	/* USER CODE BEGIN SVCall_IRQn 0 */

	/* USER CODE END SVCall_IRQn 0 */
	/* USER CODE BEGIN SVCall_IRQn 1 */

	/* USER CODE END SVCall_IRQn 1 */
}

/**
 * @brief This function handles Debug monitor.
 */
void DebugMon_Handler(void) {
	/* USER CODE BEGIN DebugMonitor_IRQn 0 */

	/* USER CODE END DebugMonitor_IRQn 0 */
	/* USER CODE BEGIN DebugMonitor_IRQn 1 */

	/* USER CODE END DebugMonitor_IRQn 1 */
}

/**
 * @brief This function handles Pendable request for system service.
 */
void PendSV_Handler(void) {
	/* USER CODE BEGIN PendSV_IRQn 0 */

	/* USER CODE END PendSV_IRQn 0 */
	/* USER CODE BEGIN PendSV_IRQn 1 */

	/* USER CODE END PendSV_IRQn 1 */
}

/**
 * @brief This function handles System tick timer.
 */
void SysTick_Handler(void) {
	/* USER CODE BEGIN SysTick_IRQn 0 */

	/* USER CODE END SysTick_IRQn 0 */
	/* USER CODE BEGIN SysTick_IRQn 1 */

	/* USER CODE END SysTick_IRQn 1 */
}

/******************************************************************************/
/* STM32F1xx Peripheral Interrupt Handlers                                    */
/* Add here the Interrupt Handlers for the used peripherals.                  */
/* For the available peripheral interrupt handler names,                      */
/* please refer to the startup file (startup_stm32f1xx.s).                    */
/******************************************************************************/

/**
 * @brief This function handles DMA1 channel6 global interrupt.
 */
void DMA1_Channel6_IRQHandler(void) {
	/* USER CODE BEGIN DMA1_Channel6_IRQn 0 */
	if (LL_DMA_IsEnabledIT_HT(DMA1, LL_DMA_CHANNEL_6)
			&& LL_DMA_IsActiveFlag_HT6(DMA1)) {
		LL_DMA_ClearFlag_HT6(DMA1); /* Clear half-transfer complete flag */
		print("-------HT-------\r\n");
		vUSART_Check(); /* Check for data to process */
	}

	/* Check transfer-complete interrupt */
	if (LL_DMA_IsEnabledIT_TC(DMA1, LL_DMA_CHANNEL_6)
			&& LL_DMA_IsActiveFlag_TC6(DMA1)) {
		LL_DMA_ClearFlag_TC6(DMA1); /* Clear transfer complete flag */
		print("-------TC-------\r\n");
		vUSART_Check(); /* Check for data to process */
	}

	/* USER CODE END DMA1_Channel6_IRQn 0 */
	// if (LL_DMA_IsActiveFlag_TC6(DMA1))
	// {
	// 	LL_DMA_ClearFlag_TC6(DMA1);
	// 	//1000 - 0 = 1000
	// 	// NumberOfBytesReceive = UART_RX_BUFFER_SIZE - LL_DMA_GetDataLength(DMA1, );
	// 	posBufferNew = UART_RX_BUFFER_SIZE - LL_DMA_GetDataLength(DMA1, LL_DMA_CHANNEL_6);
	// 	/* Start Tranfer Data To USART TX register */
	// 	if (posBufferNew != posBufferOld)
	// 	{
	// 		if(posBufferNew > posBufferOld)
	// 		{
	// 		/* We are in "linear" mode, case P1, P2, P3 */
	//         /* Process data directly by subtracting "pointers" */
	// 		LL_DMA_DisableChannel(DMA1, LL_DMA_CHANNEL_7);
	// 		LL_DMA_SetDataLength(DMA1, LL_DMA_CHANNEL_7, NumberOfBytesReceive);
	// 		LL_USART_ClearFlag_TC(USART2);
	// 		LL_DMA_EnableChannel(DMA1, LL_DMA_CHANNEL_7);
	// 		}
	// 		else
	// 		{
	// 			/* We are in "overflow" mode, case P4 */
	// 			/* First process data to the end of buffer */
	// 		}
	// 	}
	// 	/* Clear all of flag DMA stream 2 */
	// 	// LL_DMA_DisableChannel(DMA1, LL_DMA_CHANNEL_6);
	// 	DMA1_Channel6->CNDTR = UART_RX_BUFFER_SIZE; /* Set number of bytes to receive */
	// 	LL_DMA_EnableChannel(DMA1, LL_DMA_CHANNEL_6); /* Start DMA transfer */
	// }
	/* USER CODE END DMA1_Channel6_IRQn 1 */
}

/**
 * @brief This function handles DMA1 channel7 global interrupt.
 */
void DMA1_Channel7_IRQHandler(void) {
	/* USER CODE BEGIN DMA1_Channel7_IRQn 0 */
	if (LL_DMA_IsActiveFlag_TC7(DMA1)) {
		// LL_DMA_ClearFlag_TC7(DMA1);
		// LL_DMA_DisableChannel(DMA1, LL_DMA_CHANNEL_7);
	}
	/* USER CODE END DMA1_Channel7_IRQn 0 */

	/* USER CODE BEGIN DMA1_Channel7_IRQn 1 */

	/* USER CODE END DMA1_Channel7_IRQn 1 */
}

/**
 * @brief This function handles EXTI line[9:5] interrupts.
 */
void EXTI9_5_IRQHandler(void) {
	/* USER CODE BEGIN EXTI9_5_IRQn 0 */

	/* USER CODE END EXTI9_5_IRQn 0 */
	HAL_GPIO_EXTI_IRQHandler(GPIO_PIN_6);
	HAL_GPIO_EXTI_IRQHandler(GPIO_PIN_7);
	HAL_GPIO_EXTI_IRQHandler(GPIO_PIN_8);
	/* USER CODE BEGIN EXTI9_5_IRQn 1 */

	/* USER CODE END EXTI9_5_IRQn 1 */
}

/**
 * @brief This function handles TIM4 global interrupt.
 */
void TIM4_IRQHandler(void) {
	/* USER CODE BEGIN TIM4_IRQn 0 */

	/* USER CODE END TIM4_IRQn 0 */
	HAL_TIM_IRQHandler(&htim4);
	/* USER CODE BEGIN TIM4_IRQn 1 */

	/* USER CODE END TIM4_IRQn 1 */
}

/**
 * @brief This function handles USART2 global interrupt.
 */
void USART2_IRQHandler(void) {
	/* USER CODE BEGIN USART2_IRQn 0 */
	if (LL_USART_IsEnabledIT_IDLE(USART2)
			&& LL_USART_IsActiveFlag_IDLE(USART2)) {
		LL_USART_ClearFlag_IDLE(USART2); /* Clear IDLE line flag */
		print("-------IDLE-------\r\n");
		vUSART_Check(); /* Check for data to process */
	}
	/* USER CODE END USART2_IRQn 0 */
	/* USER CODE BEGIN USART2_IRQn 1 */

	/* USER CODE END USART2_IRQn 1 */
}

/* USER CODE BEGIN 1 */

/* USER CODE END 1 */
/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
