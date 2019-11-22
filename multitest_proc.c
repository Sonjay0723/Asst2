#include <stdlib.h>
#include <stdio.h>
#include <stddef.h>
#include <math.h>
#include <unistd.h>
#include <sys/types.h>

int search(int* array, int target, int length) {
  int res = -1;
  int processes = 0;
  int size;
  int i;
  int PorC = 0;

  if (length > 250) {
    size = length;
    while (size > 250) {
      processes++;
      size /= 2;
    }
  }
  else {
    processes = 1;
    size = length / 2;
  }

  int children = pow(2, processes) - 1;

  for (i = (children * size); i < length; i++) {
    if (array[i] == target) {
      res = i;
      PorC = 1;
    }
  }

  for (i = 0; i < children; i++) {
    int child = fork();

    if (child < 0) {
      printf("Error: Invalid Child\n");
      exit(-1);
    }
    else if (child == 0) {
      int childNum = getpid();
      int j;
      int k = 0;

      int index = childNum % children;

      for (j = (index * size); j < ((index + 1) * size); j++) {
        k++;
        if (array[j] == target) {
          PorC = 2;
          res = j;
          exit(k);
        }
      }

      exit(251);
    }
    else {
      int stat = 0;
      waitpid(child, &stat, 0);
      int exitNum = WEXITSTATUS(stat);
      if (exitNum < 251) {
        int index = child % children;
        res = (index * size) - 1 + exitNum;
      }
    }
  }

  if (res == -1) {
    printf("Target not found\n");
  }
  else if (PorC == 1) {
    printf("Target found in parent process\n");
  }
  else {
    printf("Target found in child process\n");
  }

  return res;
}
