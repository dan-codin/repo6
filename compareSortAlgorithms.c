#include <time.h>
#include <stdlib.h>
#include <stdio.h>

int extraMemoryAllocated;

void *Alloc(size_t sz)
{
	extraMemoryAllocated += sz;
	size_t* ret = malloc(sizeof(size_t) + sz);
	*ret = sz;
	printf("Extra memory allocated, size: %ld\n", sz);
	return &ret[1];
}

void DeAlloc(void* ptr)
{
	size_t* pSz = (size_t*)ptr - 1;
	extraMemoryAllocated -= *pSz;
	printf("Extra memory deallocated, size: %ld\n", *pSz);
	free((size_t*)ptr - 1);
}

size_t Size(void* ptr)
{
	return ((size_t*)ptr)[-1];
}

// implements heap sort
// extraMemoryAllocated counts bytes of memory allocated
void heapSort(int arr[], int n)
{
}

// implement merge sort
// extraMemoryAllocated counts bytes of extra memory allocated
void mergeSort(int pData[], int l, int r)
{
	if(l < r){

		//sorting array
		//find the middle of pData array and assign the value to variable m
		int m = (l + r)/2;

		//recursive call
		mergeSort(pData, l, m);
		mergeSort(pData, m+1, r);

		//merge array
		// variables i, j, and k are counters
		int i, j, k;
		//Number of elements in two subarrays after pData is split at m
		int n1 = m-l+1;
		int n2 = r-m;

		// create temp arrays
		int *L = (int*)Alloc(sizeof(int)* n1);
		int *R = (int*)Alloc(sizeof(int) * n2);

		//copy data to temp arrays L and R
		for ( i = 0; i < n1; i++)
			L[i] = pData[l+i];
		for ( j = 0; j < n2; i++)
			R[j] = pData[m + 1 + j];

		//merge the temp arrays back
		i = 0;
		j = 0;
		k = 0;
		while(i < n1 && j < n2){
			if(L[i]<= R[j]){
				pData[k]= L[i];
				i++;
			}
			else{
				pData[k] = R[j];
				j++;
			}
			k++;
		}
		// copy remaining elements of L if any
		while(i < n1){
			pData[k] = L[i];
			i++;
			k++;
		}

		// copy remaining elements ofR if any
		while(j < n2){
			pData[k] = R[j];
			j++;
			k++;
		}

		//free subarrays
		DeAlloc(L);
		DeAlloc(R);

		
	}

}

// implement insertion sort
// extraMemoryAllocated counts bytes of memory allocated
void insertionSort(int* pData, int n)
{
	//variables i and j are counters and item is the element that will be the key
	int i, item, j;
	for ( i = 1; i < n; i++)
	{
		item = pData[i];
		for ( j = i-1; j>=0; j--)
		{
			//move element to one position ahead if its greater than the key
			if(pData[j]>item){
				pData[j+1] = pData[j];
			}
			else
				break;
		}

		pData[j + 1] =item;
		
	}
	
	
}

// implement bubble sort
// extraMemoryAllocated counts bytes of extra memory allocated
void bubbleSort(int* pData, int n)
{
	//declare variables i and j for counters, 
	//and temp to temporary hold the value that is being switched.
	int i, j, temp;
	for (i = 0; i < n-1; i++)
	{
		//loop through unsorted array setting the control statement to last sorted element
		for ( j = 0; j < n-i-1; j++)
		{
			//swap the current element with the next if is greater than the next element
			if(pData[j]> pData[j+1]){
				temp=pData[j];
				pData[j] = pData[j+1];
				pData[j+1] = temp;

			}
		}
		
	}
	
	
}

// implement selection sort
// extraMemoryAllocated counts bytes of extra memory allocated
void selectionSort(int* pData, int n)
{
	//declare variables i and j for counters, min_idx to store the minimum idex, 
	//and temp to temporary hold the value that is being switched.
	int i, j, min_idx, temp;

	//move the boundary of the array
	for ( i = 0; i < n-1; i++)
	{
		//find the minimum element
		min_idx = i;
		for ( j = i+1; j < n; j++)
		
		
			if(pData[j]< pData[min_idx])
				min_idx = j;
			
			//swap the minimum element with the first element
			temp = pData[i];
			pData[i] = pData[min_idx];
			pData[min_idx]= temp;
			
		
	}
	
	
}

// parses input file to an integer array
int parseData(char *inputFileName, int **ppData)
{
	FILE* inFile = fopen(inputFileName,"r");
	int dataSz = 0;
	*ppData = NULL;
	
	if (inFile)
	{
		fscanf(inFile,"%d\n",&dataSz);
		*ppData = (int *)Alloc(sizeof(int) * dataSz);
		// Implement parse data block
		for (int i = 0; i < dataSz; i++)
		{
			fscanf(inFile, "%d", *ppData+i);
		}
		
	}
	
	return dataSz;
}

// prints first and last 100 items in the data array
void printArray(int pData[], int dataSz)
{
	int i, sz = dataSz - 100;
	printf("\tData:\n\t");

	for (i=0;i<100;++i)
	{
		printf("%d ",pData[i]);
	}
	printf("\n\t");
	
	for (i=sz;i<dataSz;++i)
	{
		printf("%d ",pData[i]);
	}
	printf("\n\n");
}

int main(void)
{
	clock_t start, end;
	int i;
    double cpu_time_used;
	char* fileNames[] = {"input1.txt", "input2.txt", "input3.txt"};
	
	for (i=0;i<3;++i)
	{
		int *pDataSrc, *pDataCopy;
		int dataSz = parseData(fileNames[i], &pDataSrc);
		
		if (dataSz <= 0)
			continue;
		
		pDataCopy = (int *)Alloc(sizeof(int)*dataSz);
	
		printf("---------------------------\n");
		printf("Dataset Size : %d\n",dataSz);
		printf("---------------------------\n");
		
		printf("Selection Sort:\n");
		memcpy(pDataCopy, pDataSrc, dataSz*sizeof(int));
		extraMemoryAllocated = 0;
		start = clock();
		selectionSort(pDataCopy, dataSz);
		end = clock();
		cpu_time_used = ((double) (end - start)) / CLOCKS_PER_SEC;
		printf("\truntime\t\t\t: %.1lf\n",cpu_time_used);
		printf("\textra memory allocated\t: %d\n",extraMemoryAllocated);
		printArray(pDataCopy, dataSz);
		
		printf("Insertion Sort:\n");
		memcpy(pDataCopy, pDataSrc, dataSz*sizeof(int));
		extraMemoryAllocated = 0;
		start = clock();
		insertionSort(pDataCopy, dataSz);
		end = clock();
		cpu_time_used = ((double) (end - start)) / CLOCKS_PER_SEC;
		printf("\truntime\t\t\t: %.1lf\n",cpu_time_used);
		printf("\textra memory allocated\t: %d\n",extraMemoryAllocated);
		printArray(pDataCopy, dataSz);

		printf("Bubble Sort:\n");
		memcpy(pDataCopy, pDataSrc, dataSz*sizeof(int));
		extraMemoryAllocated = 0;
		start = clock();
		bubbleSort(pDataCopy, dataSz);
		end = clock();
		cpu_time_used = ((double) (end - start)) / CLOCKS_PER_SEC;
		printf("\truntime\t\t\t: %.1lf\n",cpu_time_used);
		printf("\textra memory allocated\t: %d\n",extraMemoryAllocated);
		printArray(pDataCopy, dataSz);
		
		printf("Merge Sort:\n");
		memcpy(pDataCopy, pDataSrc, dataSz*sizeof(int));
		extraMemoryAllocated = 0;
		start = clock();
		mergeSort(pDataCopy, 0, dataSz - 1);
		end = clock();
		cpu_time_used = ((double) (end - start)) / CLOCKS_PER_SEC;
		printf("\truntime\t\t\t: %.1lf\n",cpu_time_used);
		printf("\textra memory allocated\t: %d\n",extraMemoryAllocated);
		printArray(pDataCopy, dataSz);

                printf("Heap Sort:\n");
		memcpy(pDataCopy, pDataSrc, dataSz*sizeof(int));
		extraMemoryAllocated = 0;
		start = clock();
		//heapSort(pDataCopy, 0, dataSz - 1);
		end = clock();
		cpu_time_used = ((double) (end - start)) / CLOCKS_PER_SEC;
		printf("\truntime\t\t\t: %.1lf\n",cpu_time_used);
		printf("\textra memory allocated\t: %d\n",extraMemoryAllocated);
		printArray(pDataCopy, dataSz);
		
		DeAlloc(pDataCopy);
		DeAlloc(pDataSrc);
	}
	
}
