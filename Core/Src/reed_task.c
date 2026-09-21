#include "reed_task.h"
#include "reed_switch.h"

static osThreadId_t reedTaskHandle;

static const osThreadAttr_t reedTask_attributes = {
    .name = "reedTask",
    .stack_size = 128 * 4,
    .priority = (osPriority_t) osPriorityNormal,
};

static void StartReedTask(void *argument)
{
    uint8_t reedOpen;

    for (;;)
    {
        reedOpen = Reed_IsOpen();

        if (reedOpen)
        {
            HAL_GPIO_WritePin(
                REED_LED_GPIO_Port,
                REED_LED_Pin,
                GPIO_PIN_SET
            );
        }
        else
        {
            HAL_GPIO_WritePin(
                REED_LED_GPIO_Port,
                REED_LED_Pin,
                GPIO_PIN_RESET
            );
        }

        osDelay(100);
    }
}

void ReedTask_Init(void)
{
    reedTaskHandle = osThreadNew(
        StartReedTask,
        NULL,
        &reedTask_attributes
    );

    if (reedTaskHandle == NULL)
    {
        Error_Handler();
    }
}