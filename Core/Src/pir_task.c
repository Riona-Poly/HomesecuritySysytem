#include "pir_task.h"
#include "pir.h"

static osThreadId_t pirTaskHandle;

static const osThreadAttr_t pirTask_attributes = {
    .name = "pirTask",
    .stack_size = 128 * 4,
    .priority = (osPriority_t) osPriorityNormal,
};

static void StartPIRTask(void *argument)
{
    uint8_t motionDetected;

    for (;;)
    {
        motionDetected = PIR_IsDetected();

        if (motionDetected)
        {
            HAL_GPIO_WritePin(
                PIR_LED_GPIO_Port,
                PIR_LED_Pin,
                GPIO_PIN_SET
            );
        }
        else
        {
            HAL_GPIO_WritePin(
                PIR_LED_GPIO_Port,
                PIR_LED_Pin,
                GPIO_PIN_RESET
            );
        }

        osDelay(100);
    }
}

void PIRTask_Init(void)
{
    pirTaskHandle = osThreadNew(
        StartPIRTask,
        NULL,
        &pirTask_attributes
    );

    if (pirTaskHandle == NULL)
    {
        Error_Handler();
    }
}