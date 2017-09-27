#include <stdio.h>

int main(int argc, char *argv[]) {

  int apricot[2][3][5] = {
    {
      {1,  2, 3, 4, 5},
      {6,  7, 8, 9,10},
      {11,12,13,14,15}
    },
    {
      {16,17,18,19,20},
      {21,22,23,24,25},
      {26,27,28,29,30}
    }
  };

  int (*r)[5] = apricot[0];
  int *t = apricot[0][0];

  printf("Size of int is:           %lo\n", sizeof(int));
  printf("Size of apricot:          %lo\n", sizeof(apricot));
  printf("Size of apricot[0]:       %lo\n", sizeof(apricot[0]));
  printf("Size of apricot[0][0]:    %lo\n", sizeof(apricot[0][0]));
  printf("Size of apricot[0][0][0]: %lo\n", sizeof(apricot[0][0][0]));

  printf("r value is %d          in: %x\n", **r, (unsigned int)r);
  printf("t value is %d          in: %x\n", *t, (unsigned int)t);

  r++; // Forward 20 bytes
  t++; // Forward  4 bytes

  printf("r++ value is %d        in: %x\n", **r, (unsigned int)r);
  printf("t++ value is %d        in: %x\n", *t, (unsigned int)t);

  int table[3][4] = {
    {1,  2,  3,  4},
    {5,  6,  7,  8},
    {9, 10, 11, 12}
  };

  return 0;
}
