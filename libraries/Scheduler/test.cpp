#include "Scheduler.h"
#include <iostream>

using namespace std;

class printer: public Process {
  private:
    const char * msg;
  public:
  printer(const char *str) : msg(str) {};
  void call() {
    cout << msg << "  my id is: " << id << endl;
  }
};

int main() {
  Scheduler sched;
  int x  = 10;
  printer p("hi");
  printer p2("=====");
  sched.addProcess(p, 100);
  sched.addProcess(p2, 300);
  while (1) {
    sched.loop();
  }
  return 0;
}
