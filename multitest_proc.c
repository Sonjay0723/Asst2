#include <stdlib.h>
#include <stdio.h>
#include <stddef.h>
#include <math.h>
#include <unistd.h>
#include <sys/types.h>

int search(int* array, int target, int length) {
  int processes = 0;
  int size = 0;
  int res = -1;
  int PorC = 0;
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

  int i, j, k;
  for (i = (children * size) + leftover; i < length; i++) {
    if (array[i] == target) {
      PorC = 1;
      res = i;
    }
  }

  for (i = 0; i < children; i++) {
    int child = fork();

    if (child == 0) {
      int childNum = getpid();
      int index = childNum % children;

      if (leftover > 0 && i == children - 1) {
        k = 0;
        for (j = (index * size); j < ((index * size) + leftover); j++) {
          if (array[j] == target) {
            if (PorC == 0) {
              PorC = 2;
            }
            printf("J: %d\n", j);
            printf("K: %d\n", k);
            res = j;
            exit(j);
          }
        }
      }
      else {
        k = 0;
        for (j = (index * size); j < ((index + 1) * size); j++) {
          if (array[j] == target) {
            if (PorC == 0) {
              PorC = 2;
            }
            printf("J: %d\n", j);
            printf("K: %d\n", k);
            res = j;
            exit(j);
          }
        }
      }

      exit(length + 1);
    }
    else if(child < 0) {
      printf("Error: child invalid\n");
      exit(-1);
    }
    else {
      int status = 0;
      waitpid(child, &status, 0);
      int exitNum = WEXITSTATUS(status);
      if (exitNum < (length + 1)) {
        if (PorC == 0) {
          PorC = 2;
        }
        printf("exitNum: %d\n", exitNum);
        res = exitNum;
      }
    }
  }

  if (res == -1) {
    printf("Target not found\n");
  }
  else if (PorC == 1) {
    printf("Target found in parent process\n");
  }
  else if (PorC == 2) {
    printf("Target found in child process\n");
  }
  return res;
}
