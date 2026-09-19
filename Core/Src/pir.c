#include "pir.h"

void PIR_Init(void)
{
    GPIO_InitTypeDef GPIO_InitStruct = {0};

    /* PA2 — PIR input */
    GPIO_InitStruct.Pin = PIR_Pin;
    GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
    GPIO_InitStruct.Pull = GPIO_NOPULL;

    HAL_GPIO_Init(PIR_GPIO_Port, &GPIO_InitStruct);


    /* PB7 — PIR LED */
    HAL_GPIO_WritePin(
        PIR_LED_GPIO_Port,
        PIR_LED_Pin,
        GPIO_PIN_RESET
    );

    GPIO_InitStruct.Pin = PIR_LED_Pin;
    GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
    GPIO_InitStruct.Pull = GPIO_NOPULL;
    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;

    HAL_GPIO_Init(
        PIR_LED_GPIO_Port,
        &GPIO_InitStruct
    );
}


uint8_t PIR_IsMotionDetected(void)
{
    return HAL_GPIO_ReadPin(
        PIR_GPIO_Port,
        PIR_Pin
    ) == GPIO_PIN_SET;
}