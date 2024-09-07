#ifndef LCD_H_
#define LCD_H_

void LCD_Command(unsigned char);
void LCD_Init (void);
void LCD_Char (unsigned char);
void LCD_String (char*);
void LCD_String_xy (char, char, char*);
void LCD_Clear();

#endif