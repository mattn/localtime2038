#include <stdio.h>
#include <time.h>

void
test(time_t tmr) {
  struct tm* t;
  char buf[2038];
  t = localtime(&tmr);
  strftime(buf, sizeof(buf), "%Y/%m/%d %H:%M:%S", t);
  puts(buf);
}

int
main(int argc, char* argv[]) {
  int i;
  time_t tmr = 2147483647;

  test(tmr); /* 2038/01/19 12:14:07 */
  tmr += 1;
  test(tmr); /* 1901/12/14 05:45:52 */
  return 0;
}
