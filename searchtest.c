#include <stdlib.h>
#include <stdio.h>
#include <sys/time.h>
#include <time.h>
#include "multitest.h"
#include <math.h>

/* Structs for time stuff. */
struct timeval begin; //begin time
struct timeval end; //end time

/* Function to create the array with unique values. */
int* arrayMaker(int length) 
{
int *list = malloc(sizeof(int) * length);
int i;
for (i = 0; i < length; i++) 
{
	list[i] = i + 1;
}

for (i = 0; i < length; i++) 
{
	int temp = rand() % length;
	int temp2 = list[i];
	int temp3 = list[temp];
	list[i] = temp3;
	list[temp] = temp2;
}

return list;
}

/* Function to calculate the standard deviation. */
double standardDev(double data[],int size, double mean)
{ 
double stdev=0;
int i;

for(i = 0; i<size; i++)
{
        stdev += (double) pow(data[i] - mean, 2); //sum up this
}
        stdev=(double) sqrt(stdev/size); //divide by size (number of elements, which will be 100) and take sqrt
return stdev;
}

/* Function to calculate the minimum value in the array. */
double minimum(double* data,int size)
{
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

/* Function to calculate the maximum value in the array. */
double maximum(double* data,int size) 
{
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

int main() 
{
//Test Case A:
int i;
double totalTime1=0;
double min1;
double max1;
double stdev1;

int* arr1=arrayMaker(2500);   //generate random array
double data1[100]; //array of times


for (i=0; i<100; i++) {

	//printf("This is iteration %d.",i);
	gettimeofday(&begin,NULL); //start time
	int keyIndex=searchArr(arr1,1900,2500); //run search function for processes/threads
	gettimeofday(&end,NULL); //end time

	data1[i]=(double)(end.tv_usec-begin.tv_usec); //calculate time it took to run function and store in array
	totalTime1=totalTime1+data1[i]; //add time to total time
}

totalTime1=totalTime1/(double)100;// calculates the mean time of all 100 searches
min1= minimum(data1,100); //find minimum in array
max1= maximum(data1,100); //find maximum of array
stdev1=standardDev(data1, 100, totalTime1); //calculate standard deviaton of data

printf("\nTEST A RESULTS: Searching for 1900 in an array of size 2500. \n"); //print everything
printf("Minimum: %f microseconds\n",min1);
printf("Maximum: %f microseconds\n",max1);
printf("Standard Deviation: %f microseconds\n",stdev1);
printf("Average: %f microseconds\n",totalTime1);

return 0;
}
