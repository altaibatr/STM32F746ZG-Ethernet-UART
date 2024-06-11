#include "stm32f7xx_hal.h"
#include "cmsis_os.h"
#include "uart_init.h"
#include "string.h"

/*USART 6 INIT BLOCK FOR STM32F746ZG*/


extern uint8_t uartBuffer[];

UART_HandleTypeDef s_UARTHandle;

void UART_Init(void) {
    __USART6_CLK_ENABLE();
    __GPIOG_CLK_ENABLE();
    
    GPIO_InitTypeDef GPIO_InitStructure;
 
    GPIO_InitStructure.Pin = GPIO_PIN_14;
    GPIO_InitStructure.Mode = GPIO_MODE_AF_OD;
    GPIO_InitStructure.Alternate = GPIO_AF8_USART6;
    GPIO_InitStructure.Speed = GPIO_SPEED_HIGH;
    GPIO_InitStructure.Pull = GPIO_NOPULL;
    HAL_GPIO_Init(GPIOG, &GPIO_InitStructure);
    
    GPIO_InitStructure.Pin = GPIO_PIN_9;
    GPIO_InitStructure.Mode = GPIO_MODE_AF_OD;
    HAL_GPIO_Init(GPIOG, &GPIO_InitStructure);
 
    s_UARTHandle.Instance        = USART6;
    s_UARTHandle.Init.BaudRate   = 115200;
    s_UARTHandle.Init.WordLength = UART_WORDLENGTH_8B;
    s_UARTHandle.Init.OverSampling = UART_OVERSAMPLING_16;
    s_UARTHandle.Init.StopBits   = UART_STOPBITS_1;
    s_UARTHandle.Init.Parity     = UART_PARITY_NONE;
    s_UARTHandle.Init.HwFlowCtl  = UART_HWCONTROL_NONE;
    s_UARTHandle.Init.Mode       = UART_MODE_TX_RX;
    
    if (HAL_UART_Init(&s_UARTHandle) != HAL_OK) {
        for(;;);
    }
    
    // Enable the UART receive interrupt
    HAL_NVIC_SetPriority(USART6_IRQn, 5, 0);
    HAL_NVIC_EnableIRQ(USART6_IRQn);
    
    // Start UART reception in interrupt mode
    HAL_UART_Receive_IT(&s_UARTHandle, uartBuffer, 1);
}

