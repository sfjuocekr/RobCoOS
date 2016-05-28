#include <Time.h>
#include <TimeAlarms.h>

#define WIDTH 128
#define HEIGHT 36

#define CURSOR_HOME 0
#define CURSOR_UP 1
#define CURSOR_DOWN 2
#define CURSOR_RIGHT 3
#define CURSOR_LEFT 4


#define arrayLength(x) (sizeof(x) / sizeof(*x))

void parseInput(String _input);
void clearTerminal(boolean _home);
void moveCursor(uint8_t _direction);
void moveCursor(uint8_t _steps, int _direction);
uint8_t consoleHeader();
uint8_t consoleHeader(String _name);
void consolePrompt();
void drawTerminal();
void drawTerminal(boolean _clear);

