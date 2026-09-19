#ifndef KEYPAD_TASK_H
#define KEYPAD_TASK_H

#include "main.h"
#include "cmsis_os.h"

void KeypadTask_Init(osMessageQueueId_t queue);

#endif