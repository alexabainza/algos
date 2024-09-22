#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<stdbool.h>
#define SIZE 5
#define INF 99999999
#define MAX_NODES (SIZE * 2 - 1)
#define RADIX_SIZE 10

typedef struct node{
	int data;
	struct node *next;
} NodeType, *Bucket;

typedef struct {
    int Elem[MAX_NODES];
    int size;
} OFFLINE_HEAP;

typedef Bucket bin[SIZE];

void displayArr(int arr[], int size){
	int i;
	for(i=0; i<size; i++){
		printf("%d\t", arr[i]);
	}
	printf("\n\n");
}

void swap(int* a, int *b){
	int temp = *a;
	*a = *b;
	*b = temp;
}

int getMax(int arr[], int size){
	int i, max=arr[0];
	for(i=0; i<size; i++){
		if(arr[i]>max){
			max = arr[i];
		}
	}
	return max;
}

int getMin(int arr[], int size){
	int i, min=arr[0];
	for(i=0; i<size; i++){
		if(arr[i]<min){
			min = arr[i];
		}
	}
	return min;
}

void initBin(bin b, int bucketSize){
	int i;
	for(i=0; i<bucketSize; i++){
		b[i] = NULL;
	}
}

void displayDict(bin b, int bucketSize){
	int i;
	Bucket trav;
	for(i=0; i<bucketSize; i++){
		printf("[%d] => ", i);
    	for (trav = b[i]; trav != NULL; trav = trav->next) {
       		printf("%d ", trav->data);
        	}
        printf("\n");
	}
}

void insertSorted(Bucket *L, int elem){

	Bucket *trav;

    for (trav = L; *trav != NULL && (*trav)->data < elem; trav = &(*trav)->next) {}
    Bucket temp = (Bucket) malloc(sizeof(NodeType));

    if(temp != NULL) {
        temp->data = elem;
        temp->next = *trav;
        *trav = temp;
    }
	
}

void merge(int arr[], int leftArr[], int rightArr[], int leftSize, int rightSize){
	int i = 0, leftArrIndex = 0, rightArrIndex = 0;
	while(leftArrIndex < leftSize && rightArrIndex < rightSize){
		if(leftArr[leftArrIndex] < rightArr[rightArrIndex]){
			arr[i++] = leftArr[leftArrIndex++];
		}
		else{
			arr[i++] = rightArr[rightArrIndex++];
		}
	}
	while(leftArrIndex < leftSize){
		arr[i++] = leftArr[leftArrIndex++];
	}
	while(rightArrIndex < rightSize){
		arr[i++] = rightArr[rightArrIndex++];
	}
	printf("\nMerged array:\n");
	displayArr(arr, rightSize+leftSize);
	
}
void mergeSort(int arr[], int size){
	int length = size, i, j;
	int middle = size/2;
	int* leftArr = (int*)malloc(middle * sizeof(int));
	int* rightArr = (int*)malloc((size - middle) * sizeof(int));
	
	if(size>1){
		for(i=0, j=0; i<length; i++){
			if(i<middle){
				leftArr[i] = arr[i];
			}
			else{
				rightArr[j] = arr[i];
				j++;
			}
	}
	displayArr(leftArr, middle);
	displayArr(rightArr, size-middle);
	mergeSort(leftArr, middle);
	mergeSort(rightArr, size-middle);
	merge(arr, leftArr, rightArr, middle, size-middle);
	free(leftArr);
	free(rightArr);
	}
}

void bucketSort(int arr[], int size, bin b){
	int index, bucketIndex, arrIndex;
	int bucketSize = SIZE/2;
	int min = getMin(arr, size), max =  getMax(arr, size);
	int range = max-min;
	printf("\nrange is %d\nbucket size is %d\n", range, bucketSize);
	
	for(arrIndex=0; arrIndex<size; arrIndex++){
		index = (arr[arrIndex]-min)/range;
		insertSorted(&b[index], arr[arrIndex]);
	}
	displayDict(b, bucketSize);
	
	for(bucketIndex=0, arrIndex=0; bucketIndex<bucketSize; bucketIndex++){
		Bucket trav;
		if(b[bucketIndex]!=NULL){
			for(trav=b[bucketIndex]; trav!=NULL; trav = trav->next){
				arr[arrIndex] = trav->data;
				arrIndex++;
			}
		}
	}
	displayArr(arr, SIZE);

	
}

void lomuto(int arr[], int start, int end){
	int pivot = arr[end];
	int i, j;
	if(start<end){
		for(i=start-1, j=start; j<end; j++){
			printf("\nComparing %d and %d\n", arr[j], pivot);
			if(arr[j] < pivot){
				
				swap(&arr[++i], &arr[j]);
								printf("\nSwapping %d and %d\n", arr[i], arr[j]);

		}
		
	}
	swap(&arr[++i], &arr[end]);
	printf("\nAfter iteration:\n");
	displayArr(arr, SIZE);
	lomuto(arr, start, i-1);
	lomuto(arr, i+1, end);
	}

}

int* counting(int arr[], int size){
	int max = getMax(arr, size);
	int* countArr = (int*)malloc(sizeof(int) * (max+1));
	int* sortedArr = (int*)malloc(sizeof(int) * size);
	int i;
	for(i=0; i<=max; i++){
		countArr[i] = 0;
	}
	for(i=0; i<size; i++){
		countArr[arr[i]]++;
	}
	
	printf("Counting array:\n");
	displayArr(countArr, max+1);
	
	for(i=1; i<=max; i++){
		countArr[i] += countArr[i-1];
	}
	
	printf("Cumulative array:\n");
	displayArr(countArr, max+1);
	
	for(i=size-1; i>=0; i--){
		sortedArr[--countArr[arr[i]]] = arr[i];
	}
	printf("Sorted array:\n");
	displayArr(sortedArr, size);
	free(countArr);
	displayArr(sortedArr, size);
	return sortedArr;
	
}

void hoare(int arr[], int start, int end){
	int i, j, pivot;
	if(start<end){
		for(i=start, j=end, pivot = arr[start]; i<j;){
			printf("\nj is %d\n", j);
						printf("\ni is %d\n", i);

			while(arr[i]<pivot){
				i++;
				
			}
			
			while(arr[j]>pivot){
				j--;
			}
			
			if(i<j && arr[i]!=arr[j]){
				swap(&arr[i], &arr[j]);
								printf("\nSwap %d and %d\n",arr[i], arr[j]);

					displayArr(arr,SIZE);

				i++;
				j--;
			}

		
	}
					printf("\ndone with iteration:\n");

	displayArr(arr,SIZE);
	printf("\nStarting left:\n");
	hoare(arr, start, j);
		printf("\nStarting right:\n");

	hoare(arr, j+1, end);
	}
}

void shell(int arr[], int size){
	int i, gap, j, temp;
	for(gap = size/2; gap>0; gap/=2){
		for(i=gap; i<size; i++){
			temp = arr[i];
			for(j=i; j>=gap && arr[j-gap] > temp; j-=gap){
				arr[j] = arr[j-gap];
			};

			arr[j] = temp;

		}
		printf("\nInterval: %d\n", gap);
		displayArr(arr, size);
	}
}

void shiftElements(int arr[], int* size, int index) {
	int j;
    for (j = index; j < *size - 1; j++) {
        arr[j] = arr[j + 1];
    }
    (*size)--;
}


void strand(int arr[], int size){
	int* outputArr = (int*)malloc(size * sizeof(int));
	int outputSize = 0;
	int  outputIndex = 0;
	int n = size, j;

	while(n>0){
		int* sublist = (int*)malloc(size * sizeof(int));
		int sublistIndex = 0, arrIndex = 0;
		sublist[sublistIndex++] = arr[0];
   		shiftElements(arr, &n, 0); 
		
		while(arrIndex<n){
			if(arr[arrIndex] > sublist[sublistIndex-1] ){
				sublist[sublistIndex++] = arr[arrIndex];
				shiftElements(arr, &n, arrIndex);
			}
		
		else{
			arrIndex++;
		}
	}
	
	printf("\nsublist array\n");
	displayArr(sublist, sublistIndex);

	if(outputSize == 0){
		for(j=0; j<sublistIndex; j++){
			outputArr[j] = sublist[j];
		}
		outputSize = sublistIndex;  // Update output size
	        printf("\nCurrent output size: %d\n", outputSize);

	}
	else{
		int* tempArr = (int*)malloc((outputSize + sublistIndex) * sizeof(int));
		merge(tempArr, outputArr, sublist, outputSize, sublistIndex);
        free(outputArr);
        outputArr = tempArr;
        outputSize += sublistIndex;
        printf("\nCurrent output size: %d\n", outputSize);
	}
    printf("\nOutput array:\n");
    displayArr(outputArr, outputSize);

    printf("\nRemaining input array:\n");
    displayArr(arr, n);

    free(sublist);
	}
	
	printf("\nSorted array:\n");
	displayArr(outputArr, outputSize);		
}

void countRadix(int arr[], int size, int exp){
	int countArr[RADIX_SIZE] = {0};
	int sorted[size];
	int i, currVal;
	
	for(i=0; i<size; i++){
		currVal = (arr[i]/exp)%10;
		countArr[currVal]++;
	}
	for(i=1; i<RADIX_SIZE; i++){
		countArr[i] += countArr[i-1];
	}
	
	for(i=size-1; i>=0; i--){
		currVal = (arr[i]/exp)%10;
		sorted[--countArr[currVal]]= arr[i];
	}
	
	for(i=0; i<SIZE; i++){
		arr[i] = sorted[i];
	}
	
	printf("Sorted array in %d place:\n", exp);
	displayArr(sorted, size);
}

void radix(int arr[], int size){
	int max = getMax(arr, size), exp;
	for(exp = 1; (max/exp) > 0; exp*=10){
		countRadix(arr, size, exp);
	}
	
}

void gnome(int arr[], int size){
	int i;
	for(i=1; i<size;){
		if(i==0 || arr[i] >= arr[i-1]){
			i++;
			printf("\nForward index: %d", i);
		}
		else{
						printf("\nSwappping: %d and %d\n", arr[i], arr[i-1]);

			swap(&arr[i-1], &arr[i]);
			i--;
			printf("\nBack index: %d", i);

		}
		printf("\nFinal index %d\n", i);
		displayArr(arr, SIZE);
	}
}


void selectionSort(int arr[], int size) {
    int i, j, min;
    
    for(i = 0; i < size; i++) {
	    printf("\nIteration %d\n", i);
		min = i;
        for(j = i+1; j < size; j++) {
            if(arr[j] < arr[min]) {
                min=j;
            }
        }
        
        if(min!=i) {
			swap(&arr[i], &arr[min]);
		}
		displayArr(arr, size);
    }
}

void insertionSort(int arr[], int size) {
    int i, j, key;
    
    for(i = 1; i < size; i++) {
        key = arr[i];
        for(j = i-1; j >= 0 && arr[j] > key; j--) {
            arr[j+1] = arr[j];
        }
        arr[j+1] = key;
	    printf("\nIteration %d\n", i);

		displayArr(arr, size);
        
    }
}
 
void bubbleSort(int arr[], int size) {
    int i, j;
    
    for(i = 0; i < size-1; i++) {
    	printf("\nIteration %d\n", i);
        for(j = 0; j < size-i-1; j++) {
            if(arr[j] > arr[j+1]) {
                swap(arr+j, arr+(j+1));
            }
            	displayArr(arr, SIZE);

        }
    }
}

void comb(int arr[], int size){
	int gap, i;
	bool swapped = true;
	
	for(gap = size; gap >=1 || swapped == true ; gap /= 1.3){
		//in case gap reaches 0.3 or whatever
		if(gap < 1){
			gap=1;
		}
		swapped = false;
//				printf("\nSwapping with interval %d\n", gap);

		//compare teh elements in the gap positions	
		for(i=gap; i<size; i++){
			printf("\nComparing %d and %d with gap %d\n", arr[i], arr[i-gap], gap);

			if(arr[i] < arr[i-gap]){
				swap(&arr[i], &arr[i-gap]);
				swapped = true;
				displayArr(arr, size);

			}
		}
	}
}

void initHeap(OFFLINE_HEAP* h){
	int i;
	for(i=0; i<h->size; i++){
		h->Elem[i] = INF;
	}
	
}


void offlineTournament(int arr[], int inputSize){
	OFFLINE_HEAP h;
	h.size = MAX_NODES;
	initHeap(&h);

	int i, j, min, minIndex, left, right;

	//POPULATE THE HEAP
	for(i=MAX_NODES-1, j=inputSize-1; i>= inputSize-1; i--){
		h.Elem[i] = arr[j];
		j--;
	}
	printf("\nHeap:\n");
	displayArr(h.Elem, h.size);
	
	int iter;
	//FIND WINNER OF EACH ROUND
	//(SIZE/2)-1 is the last parent
	for(iter = 0; iter<SIZE; iter++){
		for(i = (h.size/2)-1; i>=0; i--){
			printf("\nChecking element at index %d\n", i);
//			THE CHILDREN
			left = (i*2)+1;
			right = (i*2) + 2;
			if(left < h.size || right<h.size){
				min = (h.Elem[left] < h.Elem[right]? h.Elem[left]: h.Elem[right]);
			}
			//SET WINNER AS THE INDEX
			h.Elem[i] = min;
	}
	
//	FIND THE WINNER IN THE HEAP TO MARK IT AS PROCESSED
	for(i=MAX_NODES-1; i<h.size && h.Elem[i]!=min; i--){}
	h.Elem[i] = INF;
	
	printf("\nResult of iteration %d\n", iter);
	displayArr(h.Elem, h.size);

	arr[iter] = h.Elem[0];


	}
		
}
int main(){
	int arr[] = {43, 56, 13, 35, 49};
	printf("Original array:\n");
	displayArr(arr, SIZE);
//	bin b;
//	initBin(b, SIZE);
	
//	comb(arr, SIZE);
	strand(arr, SIZE);
//	printf("\nArray output so far:\n");
//	displayArr(arr, SIZE);
}
