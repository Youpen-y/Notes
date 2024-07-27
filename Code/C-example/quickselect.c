#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int quickselect(int array[], int n, int k);
int randomnumber(int min, int max);
int main()
{
    int arr[] = {10, 3, 5, 8, 2, 7, 29, 16, 14, 28};
    int size = sizeof(arr)/sizeof(int);
    int temp = quickselect(arr, size, size/2);
    printf("Array size is %d, and the median is %d", size, temp);
    return 0;
}

int quickselect(int array[], int n, int k)
{
    int *L = malloc(sizeof(int)*n);
    int *R = malloc(sizeof(int)*n);
    srand(time(0));
    int r = rand()%n;
    int pivot = array[r];
    int i,s,t;
    for(i = 0, s = 0, t = 0; i < n; i++)
    {
	if(array[i]<pivot){
	    L[s] = array[i];
	    s++;
	}else{
	    R[t] = array[i];
	    t++;
	}
    }
    if(s+1 == k){
	return pivot;
    }
    else if(s > k){
	return quickselect(L, s, k);
    }
    else {
	return quickselect(R, t, k-s-1);
    }
}

int randomnumber(int min, int max)
{

}
