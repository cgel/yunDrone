#ifndef __FAKE_MILLIS
#define __FAKE_MILLIS
#include <sys/time.h>
#include <cstddef>

typedef unsigned long millis_t;

class Millis {
 private:
  long int start_millis;
 public:
  Millis() {
    struct timeval now;
    gettimeofday(&now, NULL);
    start_millis = now.tv_sec * 1000 + now.tv_usec / 1000;
  }
  long int operator()() {
    struct timeval now;
    gettimeofday(&now, NULL);
    long int elapsed = now.tv_sec * 1000 + now.tv_usec / 1000 - start_millis;
    return elapsed;
  }
};
#endif
