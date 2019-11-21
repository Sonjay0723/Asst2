#include<stdlib.h>
#include<stdio.h>
#include<pthread.h> // Need to use Threads.
#include"multitest.h"
#include<math.h> // Need for the pow function to calculate the number of threads needed.

/* Global Variables. */
const char *name = "thread"; // Determines that the program is running in multi-thread mode.
int subSize; // Size of subarray.
int size2; // Size of array.
int* numArr; // Pointer to array.
int numThreads; // Number of threads.
int keyIndex = -1; // Index the target is at.
int key; // Target to find.
int currThread = 0; // Current Thread. 

void* ThreadSearch()
{

int num = currThread++; // Post increment.
int i;

if (num == (numThreads-1)) { // If on last thread
	for (i=num*subSize;i<size2;i++) { //run until end of array
	if (numArr[i]==key) { //if found
        keyIndex=i; //set keyIndex to index where key is at
}
}
}

else 
{
	for (i=num*subSize;i<(num+1)*subSize;i++) { //from beginning of subarray to end
	if (numArr[i]==key) { //if found
        keyIndex=i; //set keyIndex to index where key is at
}
}
}
pthread_exit(NULL);
}

int search(int* array, int target, int size)
{
/* Local Variables. */
int count = 0; //Number of times to divide.
numArr = array;
key = target;
size2 = size;

/* If size is less than 250, then increase the count variable and split into two different subarrays. */
if(size < 250)
{
	count++;
	subSize=size/2;
}

else 
{
/* If size is greater than 250, keep on dividing until the size is less than 250. */
int temp = size;

while(temp >= 250)
{
	count++; 
	temp = temp / 2;
}

	subSize=temp; 
}

	numThreads=pow(2,count); //Number of threads needed is 2^number of times divided.


	pthread_t thread[numThreads]; //create array of pthreads
int i;
for (i=0; i<numThreads; i++) { //run searchNum to see if element can be found
	pthread_create(&thread[i], NULL, ThreadSearch, NULL);
}

for (i=0; i<numThreads;i++) 
{
	pthread_join(thread[i],NULL);
}
//	printf("The number %d is found at %d and it is %d\n",key,keyIndex,numArr[keyIndex]);
	currThread=0;
return keyIndex;
}
