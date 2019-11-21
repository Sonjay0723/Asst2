#include <stdlib.h>
#include <stdio.h>
#include <stddef.h>
#include <math.h>
#include <unistd.h>
#include <sys/types.h>

int searchArr(int* array, int target, int length) {
  int processes = 0;
  int size = 0;
  if (length > 250) {
    size = length;
    while (size > 250) {
      size /= 2;
      processes++;
    }
  }
  else {
    processes = 2;
    size = length / 2;
  }

  int children = pow(2, processes) - 1;
  int leftover = length - ((children + 1) * size);
  if (leftover > 0) {
    children++;
  }

  int i, j;
  for (i = (children * size) + leftover; i < length; i++) {
    if (array[i] == target) {
      printf("Found in the parent process\n");
      return i;
    }
  }

  for (i = 0; i < children; i++) {
    int child = fork();

    if (child == 0) {
      int childNum = getpid();
      int index = childNum % children;

      if (leftover > 0 && i == children - 1) {
        for (j = (index * size); j < ((index * size) + leftover); j++) {
          if (array[j] == target) {
            return j;
          }
        }
      }
      else {
        for (j = (index * size); j < ((index + 1) * size); j++) {
          if (array[j] == target) {
            return j;
          }
        }
      }
    }
  }

  return -1;
}
