#include <stdlib.h>
#include <stdio.h>

int searchArr(int[] array, target) {
  int length = sizeof(array) / sizeof(array[0]);

  int processes = length / 250;
  int counter = 0;
  int counter2 = 1;
  int index = -1;
  int begin = 0;
  int end;
  if ((begin + 249) < length) {
    end = begin + 249;
  }
  else {
    end = length - 1;
  }
  pid_t pid;

  while (counter2 < processes) {
    counter++;
    counter2 *= 2;
  }

  while (counter > 0) {
    pid = fork();
    counter--;
  }

  int i;

  for (i = begin; i <= end; i++) {
    if (array[i] == target) {
      if (pid == 0) {
        printf("This is a child process.");
      }
      else {
        printf("This is a parent process.");
      }
      return i;
    }
  }

  if ((end + 1) < length) {
    begin = end + 1;

    if ((begin + 249) < length) {
      end = begin + 249;
    }
    else {
      end = length - 1;
    }
  }
  else {
    return -1;
  }
}
