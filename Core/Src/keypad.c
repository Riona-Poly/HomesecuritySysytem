#include "keypad.h"

static const char keys[4][4] =
{
    {'1','2','3','A'},
    {'4','5','6','B'},
    {'7','8','9','C'},
    {'*','0','#','D'}
};

char Keypad_GetKey(void)
{
    uint16_t columns[4] = {
        GPIO_PIN_8,
        GPIO_PIN_9,
        GPIO_PIN_10,
        GPIO_PIN_11
    };

    uint16_t rows[4] = {
        GPIO_PIN_12,
        GPIO_PIN_13,
        GPIO_PIN_14,
        GPIO_PIN_15
    };

    for (int col = 0; col < 4; col++)
    {
        HAL_GPIO_WritePin(GPIOA,
                          GPIO_PIN_8 | GPIO_PIN_9 |
                          GPIO_PIN_10 | GPIO_PIN_11,
                          GPIO_PIN_SET);

        HAL_GPIO_WritePin(GPIOA, columns[col], GPIO_PIN_RESET);

        for (int row = 0; row < 4; row++)
        {
            if (HAL_GPIO_ReadPin(GPIOB, rows[row]) == GPIO_PIN_RESET)
            {
                HAL_Delay(20);

                if (HAL_GPIO_ReadPin(GPIOB, rows[row]) == GPIO_PIN_RESET)
                {
                    while (HAL_GPIO_ReadPin(GPIOB, rows[row]) == GPIO_PIN_RESET);

                    return keys[row][col];
                }
            }
        }
    }

    return 0;
}