#include <stdlib.h>
#include <stdio.h>
//#include <sys/time.h>
#include <time.h>
#include "multitest.h"
#include <math.h>

int* arrayMaker(int length) {
  //int length = x;
  int *list = malloc(sizeof(int) * length);
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

  return list;
}

struct timeval begin; //begin time
struct timeval end; //end time

double calculateSD(double data[],int size, double mean)
{ //function to calculate stdev
double stdev=0;
int i;

for(i = 0; i<size; i++)
{
        stdev += (double) pow(data[i] - mean, 2); //sum up this
}
        stdev=(double) sqrt(stdev/size); //divide by size (number of elements, which will be 100) and take sqrt
return stdev;
}

double findMin(double* data,int size)
{ //find minimum value in array
double min=data[0];
int i;

for (i = 1; i<size;i++)
{
        if (data[i]<min) { //if current value in array is smaller than current min
        min=data[i]; //replace min value
}
}
return min;
}

double findMax(double* data,int size) { //find maximum value in array
double max=data[0];
int i;
for (i=1;i<size;i++)
{
        if (data[i]>max) { //if current value in array is larger than current size
        max=data[i]; //replace max value
}
}
return max;
}

int main() {
  int length = 20;
  int* list = arrayMaker(length);
  int i;

  /*for (i = 0; i < length; i++) {
    printf("%d\n", list[i]);
  }*/
  return 0;
}
