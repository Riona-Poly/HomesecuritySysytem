#include "buzzer_task.h"
#include "buzzer.h"

static osMessageQueueId_t buzzerQueue;
static osThreadId_t buzzerTaskHandle;

static const osThreadAttr_t buzzerTask_attributes = {
    .name = "buzzerTask",
    .stack_size = 128 * 4,
    .priority = (osPriority_t) osPriorityNormal,
};

static void StartBuzzerTask(void *argument)
{
    uint8_t beepRequest;

    for (;;)
    {
        if (osMessageQueueGet(
                buzzerQueue,
                &beepRequest,
                NULL,
                osWaitForever) == osOK)
        {
            if (beepRequest == 1)
            {
                Buzzer_On();

                osDelay(500);

                Buzzer_Off();
            }
        }
    }
}

osMessageQueueId_t BuzzerTask_Init(void)
{
    buzzerQueue = osMessageQueueNew(
        5,
        sizeof(uint8_t),
        NULL
    );

    if (buzzerQueue == NULL)
    {
        Error_Handler();
    }

    buzzerTaskHandle = osThreadNew(
        StartBuzzerTask,
        NULL,
        &buzzerTask_attributes
    );

    if (buzzerTaskHandle == NULL)
    {
        Error_Handler();
    }

    return buzzerQueue;
}