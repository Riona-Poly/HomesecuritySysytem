#include "door_sensor.h"

uint8_t Door_IsOpen(void)
{
    if (HAL_GPIO_ReadPin(DOOR_SENSOR_GPIO_Port, DOOR_SENSOR_Pin) == GPIO_PIN_SET)
    {
        return 1;
    }

    return 0;
}