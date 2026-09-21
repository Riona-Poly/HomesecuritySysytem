#include "reed_switch.h"

uint8_t Reed_IsOpen(void)
{
    return (
        HAL_GPIO_ReadPin(
            REED_Pin_GPIO_Port,
            REED_Pin_Pin
        ) == GPIO_PIN_SET
    );
}