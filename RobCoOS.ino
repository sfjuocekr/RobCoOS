#include <RobCoOS.h>
#include <RobCoTerm.h>
#include <Time.h>
#include <TimeAlarms.h>

void setup()
{
	Serial.begin(9600);
	Serial.flush();

	drawTerminal();
	consolePrompt();
}

void loop()
{
	Alarm.delay(0);
}
