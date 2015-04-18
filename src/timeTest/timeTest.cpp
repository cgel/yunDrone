#include <Arduino.h>
#include <StandardCplusplus.h>
#include <serstream>
#include <string>
#include <vector>
#include <iterator>

using namespace std;

// <iostream> declares cout/cerr, but the application must define them
// because it's up to you what to do with them.
namespace std
{
  ohserialstream cout(Serial);
}

vector<string> strings;

void setup(void)
{
  Serial.begin(57600);

  cout << "Starting time demo" << endl;
}

void loop(void)
{
	unsigned long time;
	time = millis();	
	cout << "the time is: " << time << endl;
	delay(1000);
}
