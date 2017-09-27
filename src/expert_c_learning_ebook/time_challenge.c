#include <stdio.h>
#include <time.h>

int main() {
  time_t tm = 0x7FFFFFFF;
  char *time_str = ctime(&tm);
  printf("Max time stamp %s", time_str);

  return 0;
}
