#include "Scheduler.h"
#include "fake_millis.h"
#include <iostream>
#include <unistd.h>
using namespace std;
class printer: public Process {
  private:
    const char * msg;
  public:
  printer(const char *str) : msg(str) {}
  void call() {
    cout << msg << endl;
  }
};

int main() {
  Scheduler sched;
  printer p("hi");
  sched.addProcess(p, 100);
  while (1) {
    sched.loop();
  }
  long int m = millis();
  cout << m << " ms.\n";
  m = millis();
  cout << m << " ms.\n";

  return 0;
}
