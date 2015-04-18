#include <Arduino.h>
#include <StandardCplusplus.h>
#include <serstream>
#include <string>
#include <vector>
#include <iterator>
#include <Scheduler.h>

using namespace std;


// <iostream> declares cout/cerr, but the application must define them
// because it's up to you what to do with them.
namespace std
{
  ohserialstream cout(Serial);
}

Scheduler sys;

void setup(void)
{
  Serial.begin(57600);

  cout << "Starting Scheduler demo" << endl;
}

void loop(void)
{
}

// vim:cin:ai:sts=2 sw=2 ft=cpp
