#include "keypad_task.h"
#include "keypad.h"

static osMessageQueueId_t keypadQueue;
static osThreadId_t keypadTaskHandle;

static const osThreadAttr_t keypadTask_attributes = {
    .name = "keypadTask",
    .stack_size = 128 * 4,
    .priority = (osPriority_t) osPriorityNormal,
};

static void StartKeypadTask(void *argument)
{
    char key;

    for (;;)
    {
        key = Keypad_GetKey();

        if (key != 0)
        {
            osMessageQueuePut(
                keypadQueue,
                &key,
                0,
                0
            );
        }

        osDelay(10);
    }
}

void KeypadTask_Init(osMessageQueueId_t queue)
{
    keypadQueue = queue;

    keypadTaskHandle = osThreadNew(
        StartKeypadTask,
        NULL,
        &keypadTask_attributes
    );

    if (keypadTaskHandle == NULL)
    {
        Error_Handler();
    }
}