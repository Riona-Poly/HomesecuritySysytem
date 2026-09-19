#include "buzzer.h"

void Buzzer_On(void)
{
    HAL_GPIO_WritePin(
        BUZZER_GPIO_Port,
        BUZZER_Pin,
        GPIO_PIN_SET
    );
}

void Buzzer_Off(void)
{
    HAL_GPIO_WritePin(
        BUZZER_GPIO_Port,
        BUZZER_Pin,
        GPIO_PIN_RESET
    );
}