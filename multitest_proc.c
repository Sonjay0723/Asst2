#include <stdlib.h>
#include <stdio.h>
#include <stddef.h>
#include <math.h>
#include <unistd.h>
#include <sys/types.h>

const char *name = "The multi-mode being used is Process." //determines that the program is running in process mode
int search(int* array, int target, int length) {
  int res = -1; //return value initialized
  int processes = 0; //determines how many times the process needs to happen so each one has at most 250 values to search through
  int size; //size of each new array per child
  int i;
  int PorC = 0; //determines if the parent or child found the value. 1 for parent, 2 for child, 0 for not found

  if (length > 250) { //determining size and processes is length > 250
    size = length;
    while (size > 250) {
      processes++;
      size /= 2;
    }
  }
  else { //makes 2 processes even if length is less than or equal to 250
    processes = 1;
    size = length / 2;
  }

  int children = pow(2, processes) - 1; //how many child processes there need to be

  for (i = (children * size); i < length; i++) { //checks to see if target is in parent process
    if (array[i] == target) {
      res = i;
      PorC = 1;
    }
  }

  for (i = 0; i < children; i++) { //splits up process and makes children
    int child = fork();

    if (child < 0) {
      printf("Error: Invalid Child\n"); //checks for invalid child
      exit(-1);
    }
    else if (child == 0) {
      int childNum = getpid();
      int j;
      int k = 0;

      int index = childNum % children;

      for (j = (index * size); j < ((index + 1) * size); j++) { //checks through various child processes for target
        k++;
        if (array[j] == target) {
          PorC = 2;
          res = j;
          exit(k); //exit brings child processes back to the parent
        }
      }

      exit(251);
    }
    else {
      int stat = 0;
      waitpid(child, &stat, 0);
      int exitNum = WEXITSTATUS(stat); //gets the value from exit from child processes
      if (exitNum < 251) {
        int index = child % children;
        res = (index * size) - 1 + exitNum; //sets res equal to the index
      }
    }
  }

  /*if (res == -1) {
    printf("Target not found\n");
  }
  else if (PorC == 1) {
    printf("Target found in parent process\n");
  }
  else {
    printf("Target found in child process\n");
  }*/

  return res;
}
