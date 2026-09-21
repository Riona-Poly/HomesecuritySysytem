#include "lcd.h"

extern I2C_HandleTypeDef hi2c1;

#define LCD_ADDR (0x27 << 1)
#define LCD_BACKLIGHT 0x08
#define LCD_ENABLE    0x04
#define LCD_RS        0x01

static void LCD_SendCommand(uint8_t command);
static void LCD_SendData(uint8_t data);
static void LCD_SendNibble(uint8_t nibble, uint8_t mode);

void LCD_Init(void)
{
    HAL_Delay(50);

    LCD_SendNibble(0x30, 0);
    HAL_Delay(5);

    LCD_SendNibble(0x30, 0);
    HAL_Delay(1);

    LCD_SendNibble(0x30, 0);
    HAL_Delay(1);

    LCD_SendNibble(0x20, 0);
    HAL_Delay(1);

    LCD_SendCommand(0x28);
    LCD_SendCommand(0x08);

    LCD_Clear();

    LCD_SendCommand(0x06);
    LCD_SendCommand(0x0C);
}

void LCD_Clear(void)
{
    LCD_SendCommand(0x01);
    HAL_Delay(2);
}

void LCD_SetCursor(uint8_t row, uint8_t column)
{
    uint8_t address;

    if (row == 0)
    {
        address = 0x80 + column;
    }
    else
    {
        address = 0xC0 + column;
    }

    LCD_SendCommand(address);
}

void LCD_Print(const char *text)
{
    while (*text)
    {
        LCD_SendData((uint8_t)*text);
        text++;
    }
}

static void LCD_SendCommand(uint8_t command)
{
    LCD_SendNibble(command & 0xF0, 0);
    LCD_SendNibble((command << 4) & 0xF0, 0);
}

static void LCD_SendData(uint8_t data)
{
    LCD_SendNibble(data & 0xF0, LCD_RS);
    LCD_SendNibble((data << 4) & 0xF0, LCD_RS);
}

static void LCD_SendNibble(uint8_t nibble, uint8_t mode)
{
    uint8_t data;

    data = nibble | LCD_BACKLIGHT | mode;

    HAL_I2C_Master_Transmit(
        &hi2c1,
        LCD_ADDR,
        &data,
        1,
        HAL_MAX_DELAY
    );

    data |= LCD_ENABLE;

    HAL_I2C_Master_Transmit(
        &hi2c1,
        LCD_ADDR,
        &data,
        1,
        HAL_MAX_DELAY
    );

    data &= ~LCD_ENABLE;

    HAL_I2C_Master_Transmit(
        &hi2c1,
        LCD_ADDR,
        &data,
        1,
        HAL_MAX_DELAY
    );
}