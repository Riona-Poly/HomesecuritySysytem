#ifndef LCD_H
#define LCD_H

#include "main.h"

void LCD_Init(void);
void LCD_Clear(void);
void LCD_SetCursor(uint8_t row, uint8_t column);
void LCD_Print(const char *text);

#endif