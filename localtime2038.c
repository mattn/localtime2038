#ifdef __i386__
#define _GNU_SOURCE
#include <time.h>
#include <dlfcn.h>

static struct tm* (*__localtime)(const time_t *timer);

__attribute__((constructor))
void
wrap_localtime() {
  __localtime = dlsym(RTLD_NEXT, "localtime");
}

struct tm *
localtime(const time_t *timer) {
  struct tm* t;
  unsigned long tmr = *timer;
  int yadd = 0;

  /* 1970 - 2101 */
  if (tmr >= (60uL*60uL*24uL)*47847uL) {
    yadd += 40;
    tmr -= (60uL*60uL*24uL)*14609uL;
  }
  /* 1970 - 2100 */
  if (tmr >= (60uL*60uL*24uL)*47482uL) {
    yadd += 6;
    tmr -= (60uL*60uL*24uL)*2191uL;
  }
  while (tmr >= ((60uL*60uL*24uL)*24837uL)) {
    yadd  +=28;
    tmr -= (60uL*60uL*24uL)*10227uL;
  }
  t = __localtime((time_t*)&tmr);
  t->tm_year += yadd;
  return t;
}
#endif
