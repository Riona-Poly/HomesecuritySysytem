#include "pir.h"

uint8_t PIR_IsDetected(void)
{
    return HAL_GPIO_ReadPin(PIR_GPIO_Port, PIR_Pin);
}