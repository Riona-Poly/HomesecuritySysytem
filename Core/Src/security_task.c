#include "security_task.h"
#include "buzzer.h"
#include <string.h>

#define PIN_LENGTH 4

static osMessageQueueId_t keypadQueue;
static osMessageQueueId_t buzzerQueue;

static osThreadId_t securityTaskHandle;

static const osThreadAttr_t securityTask_attributes = {
    .name = "securityTask",
    .stack_size = 128 * 4,
    .priority = (osPriority_t) osPriorityNormal,
};

static const char correctPIN[] = "1234";

static void StartSecurityTask(void *argument)
{
    char enteredPIN[PIN_LENGTH + 1];
    uint8_t pinIndex = 0;
    char key;
    uint8_t beepRequest;

    memset(enteredPIN, 0, sizeof(enteredPIN));

    for (;;)
    {
        if (osMessageQueueGet(
                keypadQueue,
                &key,
                NULL,
                osWaitForever) == osOK)
        {
            if (key >= '0' && key <= '9')
            {
                enteredPIN[pinIndex] = key;
                pinIndex++;

                if (pinIndex == PIN_LENGTH)
                {
                    enteredPIN[PIN_LENGTH] = '\0';

                    if (strcmp(enteredPIN, correctPIN) == 0)
                    {
                        /* Correct PIN */

                        HAL_GPIO_WritePin(
                            Keypad_led_GPIO_Port,
                            Keypad_led_Pin,
                            GPIO_PIN_RESET
                        );

                        Buzzer_Off();
                    }
                    else
                    {
                        /* Wrong PIN */

                        HAL_GPIO_WritePin(
                            Keypad_led_GPIO_Port,
                            Keypad_led_Pin,
                            GPIO_PIN_SET
                        );

                        beepRequest = 1;

                        osMessageQueuePut(
                            buzzerQueue,
                            &beepRequest,
                            0,
                            0
                        );
                    }

                    memset(enteredPIN, 0, sizeof(enteredPIN));
                    pinIndex = 0;
                }
            }
        }
    }
}

osMessageQueueId_t SecurityTask_Init(
    osMessageQueueId_t buzzerQueueInput
)
{
    keypadQueue = osMessageQueueNew(
        10,
        sizeof(char),
        NULL
    );

    if (keypadQueue == NULL)
    {
        Error_Handler();
    }

    buzzerQueue = buzzerQueueInput;

    securityTaskHandle = osThreadNew(
        StartSecurityTask,
        NULL,
        &securityTask_attributes
    );

    if (securityTaskHandle == NULL)
    {
        Error_Handler();
    }

    return keypadQueue;
}