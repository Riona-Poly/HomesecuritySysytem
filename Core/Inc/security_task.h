#ifndef SECURITY_TASK_H
#define SECURITY_TASK_H

#include "main.h"
#include "cmsis_os.h"

osMessageQueueId_t SecurityTask_Init(
    osMessageQueueId_t buzzerQueue
);

#endif