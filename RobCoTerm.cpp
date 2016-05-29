#include <RobCoTerm.h>

String strings[5] =
{
			"ROBCO INDUSTRIES UNIFIED OPERATING SYSTEM",
			"COPYRIGHT 2075-2077 ROBCO INDUSTRIES",
			"UGH-ARDUINO",
			">",
			"NOT IMPLEMENTED: "
};

String terminalBuffer[HEIGHT];
uint8_t terminalLines = 0;

String terminalInput;

uint8_t cursorX = 0;
uint8_t cursorY = 0;

boolean prompt = false;

void serialEvent()
{
	if (!prompt)
	{
		Serial.flush();
		return;
	}

	while (Serial.available())
	{
		if (Serial.available() > 0)
		{
			char _input = Serial.read();

			if (_input == 13)
			{
				Serial.println(); cursorY++; cursorX = 0;
				terminalInput += _input;
				parseInput(terminalInput);
				return;

			}
			/*else if (_input == 27)
			{
				Serial.print((String)_input); cursorX++;
				return;
			}*/
			else
			{
				Serial.print((String)_input); cursorX++;
				terminalInput += _input;
				return;
			}
		}
	}
}

void parseInput(String _input)
{
	prompt = false;
	terminalInput = "";

	if (cursorY > HEIGHT)
	{
		drawTerminal();
	}

	if (_input.length() == 1)
	{
		consolePrompt();
		return;
	}

	if (_input.length() >= 2)
	{
		switch (_input.charAt(0))
		{
			case 49: // 1
				Serial.println((String)cursorX + " " + (String)cursorY); cursorY++;
				consolePrompt();
				break;
			default:
				Serial.println(strings[4] + _input); cursorY++;
				consolePrompt();
				break;
		}
	}

/*	if (_input.length() > 2)
	{
		Serial.println(strings[4] + _input); cursorY++;
		consolePrompt();
	}*/
}


void clearTerminal()
{
	clearTerminal(true);
}

void clearTerminal(boolean _home)
{
	Serial.write(27);
	Serial.print("[2J");

	if (_home) moveCursor(CURSOR_HOME);

	memset(terminalBuffer, 0, sizeof(terminalBuffer));

	terminalLines = 0;
}

void moveCursor(uint8_t _direction)
{
	moveCursor(0, CURSOR_HOME);
}

void moveCursor(uint8_t _steps, int _direction)
{
	switch (_direction)
	{
		case CURSOR_HOME:
			cursorX = 0;
			cursorY = 0;
			Serial.write(27);
			Serial.print("[H");
			break;
		case CURSOR_UP:
			cursorY -= _steps;
			Serial.write(27);
			Serial.print("[" + (String)_steps + "A");
			break;
		case CURSOR_DOWN:
			cursorY += _steps;
			Serial.write(27);
			Serial.print("[" + (String)_steps + "B");
			break;
		case CURSOR_RIGHT:
			cursorX += _steps;
			Serial.write(27);
			Serial.print("[" + (String)_steps + "C");
			break;
		case CURSOR_LEFT:
			cursorX -= _steps;
			Serial.write(27);
			Serial.print("[" + (String)_steps + "D");
			break;
	}
}

String printSpaces(String _string)
{
	String _tmp;

	for (uint8_t i = 0; i < (WIDTH - _string.length()) / 2; i++)
		_tmp += " ";

	return _tmp + _string;
}

String printLine()
{
	String _tmp;

	for (uint8_t i = 0; i < WIDTH; i++)
        	_tmp += "_";

	return _tmp;
}

uint8_t consoleHeader()
{
        return consoleHeader(strings[2]);
}

uint8_t consoleHeader(String _name)
{
	terminalBuffer[0] = printSpaces(strings[0]);
	terminalBuffer[1] = printSpaces(strings[1]);
	terminalBuffer[2] = printSpaces(_name);
	terminalBuffer[3] = printLine();

	return 4;
}

void consolePrompt()
{
	cursorX = 0;
        Serial.print(strings[3]); cursorX += strings[3].length();
        moveCursor(1, CURSOR_RIGHT);
	prompt = true;
}

void drawTerminal()
{
	drawTerminal(true);
}

void drawTerminal(boolean _clear)
{
	if (_clear) clearTerminal();

	terminalLines += consoleHeader();//cursorY += terminalLines;

	for (uint8_t i = 0; i < terminalLines; i++)
	{
		Serial.println(terminalBuffer[i]);
		cursorY++;
	}

	if (prompt) consolePrompt();
}
