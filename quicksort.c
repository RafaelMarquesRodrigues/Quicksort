#include <stdio.h>
#include <string.h>
#include <math.h>
#include <stdlib.h>
#include <time.h>

typedef int(*Compare) (const void *a, const void *b);

int compareInt(const void *a, const void *b){
	return (*(int *) a) > (*(int *) b);
}

void swap(int *vector, int a, int b){																		//a
	int aux = vector[a];
	vector[a] = vector[b];
	vector[b] = aux;
}

//Creating subpartitions
void _quicksort(int *vector, int start, int end, Compare compare){

	if(start < end){																						//b
		//Reorder the array
		int r = quicksortialize(vector, start, end, compare);												//n (see below)	

		//Calls quicksort for the others subpartitions
		_quicksort(vector, start, r, compare);																//This both calls together consume:
		_quicksort(vector, r + 1, end, compare);															//log(INITIAL(end) - INITIAL(start))
	}
}

void quicksort(int *vector, int n, Compare compare){
	_quicksort(vector, 0, n - 1, compare);																	//c
}

//Dividing all elements of the vector in two subgroups, greater than and smaller than the pivot
int quicksortialize(int *vector, int left, int pivot, Compare compare){
	//Starts looking at the left of the pivot
	//The pivot in this case is just the rightmost element of the subarray
	int right = pivot - 1;

	while(left < right){																					//(INITIAL(left) - INITIAL(right) = n) -> n
		if(compare(&vector[left], &vector[pivot])){															//d
			swap(vector, right, left);
			right--;
		}
		else
			left++;
	}

	//Places the pivot in it's right place
	if(compare(&vector[left], &vector[pivot]))																//e
		swap(vector, pivot, right);

	return left;
}

//	Therefore -
//			  ||
//			 \  /
//			  \/
//
// Overall Cost:
//
// 			( n * (log(n) + a + d + e) ) + b + c
//
//	Complexity -> O(n log(n))
//

//Transforms the argument to a number
int _stringToNumber(char *str, int counter, int size){
	if(size > 0)
		return (((int) str[size] - 48) * pow(10, counter)) + _stringToNumber(str, counter + 1, size - 1);
	
	return ((int) str[size] - 48) * pow(10, counter); 
}

int stringToNumber(char *str){
	return _stringToNumber(str, 0, strlen(str) - 1);
}

void printVector(int *vector, int n){
	int i;
	for(i = 0; i < n; i++)
		printf("%d ", vector[i]);
	printf("\n");
}

int main(int argc, char *argv[]){

	if(argc < 2){
		printf("usage: %s [array size]\n", argv[0]);
		return -1;
	}

	int i;
	int *vector = NULL;
	int size = stringToNumber(argv[1]);

	//Generate a new seed to provide random numbers 
	srand(time(NULL));

	vector = (int *) malloc(sizeof(int) * size);
	
	//Populates the array with random numbers
	for(i = 0; i < size; i++)
		vector[i] = rand() % size;

	printVector(vector, size);

	quicksort(vector, size, compareInt);

	printVector(vector, size);

	free(vector);

	return 0;
}
