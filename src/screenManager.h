/*Comments*/
#ifndef _SCREENMANAGER_H
#define _SCREENMANAGER_H
/* Place to put all of my definitions etc. */

typedef char byte;

extern void screenManagerInit();
extern void print(char* message);
extern void printAt(char* message, int x, int y);
extern void setBackgroundColor(byte backgroundColor);
extern void setForegroundColor(byte foregroundColor);
extern void setTerminalColor(byte backgroundColor, byte foregroundColor);
extern void clearScreen();

extern const byte VGA_COLOR_BLACK;
extern const byte VGA_COLOR_BLUE;
extern const byte VGA_COLOR_GREEN;
extern const byte VGA_COLOR_CYAN;
extern const byte VGA_COLOR_RED;
extern const byte VGA_COLOR_MAGENTA;
extern const byte VGA_COLOR_BROWN;
extern const byte VGA_COLOR_GRAY;
extern const byte VGA_COLOR_DARK_GRAY;
extern const byte VGA_COLOR_BRIGHT_BLUE;
extern const byte VGA_COLOR_BRIGHT_GREEN;
extern const byte VGA_COLOR_BRIGHT_CYAN;
extern const byte VGA_COLOR_BRIGHT_RED;
extern const byte VGA_COLOR_BRIGHT_MAGENTA;
extern const byte VGA_COLOR_YELLOW;
extern const byte VGA_COLOR_WHITE;
#endif
