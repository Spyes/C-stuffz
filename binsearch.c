#include <stdio.h>

int find(double searchKey, double lowerBound, double upperBound, double *arr, int nElements)
{
    int curIn = (lowerBound + upperBound) / 2;
    if (arr[curIn] == searchKey) return curIn;
    else if (lowerBound > upperBound) return nElements;
    else {
	if (arr[curIn] < searchKey)
	    return find(searchKey, curIn+1, upperBound, arr, nElements);
	else if (arr[curIn] > searchKey)
	    return find(searchKey, lowerBound, curIn-1, arr, nElements);
    }
}

int sizeof_array(double arr[])
{
    return sizeof((*arr));
}

int main(int argc, char **argv)
{
    double arr[] = {0, 2, 3, 6, 2, 5};
    arr[0] = (sizeof(arr) / sizeof(double));
    printf("Array is of size %i\n", arr[0]);
    return 0;
}
