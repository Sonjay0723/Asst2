#include <stdlib.h>
#include <stdio.h>

int main() {
  int length = 20;
  int list [length];
  int i;
  for (i = 0; i < length; i++) {
    list[i] = i + 1;
  }

  for (i = 0; i < length; i++) {
    int temp = rand() % length;
    int temp2 = list[i];
    int temp3 = list[temp];
    list[i] = temp3;
    list[temp] = temp2;
  }

  for (i = 0; i < length; i++) {
    printf("%d\n", list[i]);
  }
  return 0;
}
