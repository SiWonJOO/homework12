/*
 * hw12-sorting-hashing.c
 *
 *  Homework 12: Sorting & Hashing
 *  Department of Computer Science at Chungbuk National University
 *
 */

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define MAX_ARRAY_SIZE			13	/* prime number */
#define MAX_HASH_TABLE_SIZE 	MAX_ARRAY_SIZE

/* 필요에 따라 함수 추가 가능 */
int initialize(int **a);
int freeArray(int *a);
void printArray(int *a);

int selectionSort(int *a);
int insertionSort(int *a);
int bubbleSort(int *a);
int shellSort(int *a);
/* recursive function으로 구현 */
int quickSort(int *a, int n);


/* hash code generator, key % MAX_HASH_TABLE_SIZE */
int hashCode(int key);

/* array a에대 한 hash table을 만든다. */
int hashing(int *a, int **ht);

/* hash table에서 key를 찾아 hash table의 index return */
int search(int *ht, int key);


int main()
{
	char command;
	int *array = NULL;
	int *hashtable = NULL;
	int key = -1;
	int index = -1;

	srand(time(NULL));

	do{
		printf("----------------------------------------------------------------\n");
		printf("                        Sorting & Hashing                       \n");
		printf("----------------------------------------------------------------\n");
		printf(" Initialize       = z           Quit             = q\n");
		printf(" Selection Sort   = s           Insertion Sort   = i\n");
		printf(" Bubble Sort      = b           Shell Sort       = l\n");
		printf(" Quick Sort       = k           Print Array      = p\n");
		printf(" Hashing          = h           Search(for Hash) = e\n");
		printf("----------------------------------------------------------------\n");

		printf("Command = ");
		scanf(" %c", &command);

		switch(command) {
		case 'z': case 'Z':
			initialize(&array);
			break;
		case 'q': case 'Q':
			freeArray(array);
			break;
		case 's': case 'S':
			selectionSort(array);
			break;
		case 'i': case 'I':
			insertionSort(array);
			break;
		case 'b': case 'B':
			bubbleSort(array);
			break;
		case 'l': case 'L':
			shellSort(array);
			break;
		case 'k': case 'K':
			printf("Quick Sort: \n");
			printf("----------------------------------------------------------------\n");
			printArray(array);
			quickSort(array, MAX_ARRAY_SIZE);
			printf("----------------------------------------------------------------\n");
			printArray(array);

			break;

		case 'h': case 'H':
			printf("Hashing: \n");
			printf("----------------------------------------------------------------\n");
			printArray(array);
			hashing(array, &hashtable);
			printArray(hashtable);
			break;

		case 'e': case 'E':
			printf("Your Key = ");
			scanf("%d", &key);
			printArray(hashtable);
			index = search(hashtable, key);
			printf("key = %d, index = %d,  hashtable[%d] = %d\n", key, index, index, hashtable[index]);
			break;

		case 'p': case 'P':
			printArray(array);
			break;
		default:
			printf("\n       >>>>>   Concentration!!   <<<<<     \n");
			break;
		}

	}while(command != 'q' && command != 'Q');

	return 1;
}

int initialize(int** a)
{
	int *temp = NULL;

	/* array가 NULL인 경우 메모리 할당 */
	if(*a == NULL) {
		temp = (int*)malloc(sizeof(int) * MAX_ARRAY_SIZE);
		*a = temp;  /* 할당된 메모리의 주소를 복사 --> main에서 배열을 control 할수 있도록 함*/
	} else
		temp = *a;

	/* 랜덤값을 배열의 값으로 저장 */
	for(int i = 0; i < MAX_ARRAY_SIZE; i++)
		temp[i] = rand() % MAX_ARRAY_SIZE;

	return 0;
}

int freeArray(int *a) // 할당된 메모리 초기화 하는 함수
{
	if(a != NULL) // 배열이 비어있지 않다면
		free(a); 
	return 0;
}

void printArray(int *a) // 배열을 출력하는 함수
{
	if (a == NULL) {
		printf("nothing to print.\n");
		return;
	}
	for(int i = 0; i < MAX_ARRAY_SIZE; i++)
		printf("a[%02d] ", i);
	printf("\n");
	for(int i = 0; i < MAX_ARRAY_SIZE; i++)
		printf("%5d ", a[i]);
	printf("\n");
}


int selectionSort(int *a) // 선택정렬 함수 구현 - 데이터를 첫번째 데이터 부터 선택하여 마지막 데이터까지 비교해서 가장 작은 값을 첫번째 값으로 swap , 다시 두번째부터 마지막까지 비교하여 젤 작은 값을 swap 해주고 정렬 될때까지 반복하는 알고리즘
{
	int min;
	int minindex;
	int i, j;

	printf("Selection Sort: \n");
	printf("----------------------------------------------------------------\n");

	printArray(a);
   // 배열을 오름차순으로 정렬함
	for (i = 0; i < MAX_ARRAY_SIZE; i++)
	{
		minindex = i;
		min = a[i]; 
		for(j = i+1; j < MAX_ARRAY_SIZE; j++)
		{
			if (min > a[j]) // 주어진 리스트 중에 최소값을 구하기 위한 함수
			{
				min = a[j];
				minindex = j;
			}
		}
		//최소값을 맨 앞에 위치한 값과 교체한다.
		a[minindex] = a[i];
		a[i] = min;
	}

	printf("----------------------------------------------------------------\n");
	printArray(a);
	return 0;
}

int insertionSort(int *a) // 삽입정렬 함수 구현
{
	int i, j, t;

	printf("Insertion Sort: \n");
	printf("----------------------------------------------------------------\n");

	printArray(a); // 현재 배열 상태 출력

	for(i = 1; i < MAX_ARRAY_SIZE; i++)
	{ 
		t = a[i]; //2번째 인덱스에 값을 t 에 저장한다.
		j = i; // 이전값 저장
		while (a[j-1] > t && j > 0) // t와 이전에 있는 원소들을 비교하며 삽입한다.
		{
			a[j] = a[j-1];
			j--;
		}
		a[j] = t; // t의 값을 다음 인덱스에 저장한다.
	}

	printf("----------------------------------------------------------------\n");
	printArray(a);

	return 0;
}

int bubbleSort(int *a) // 버블 정렬 함수 구현 - 서로 인접한 두 원소를 검사하여 정렬하는 알고리즘
{
	int i, j, t;

	printf("Bubble Sort: \n");
	printf("----------------------------------------------------------------\n");

	printArray(a);

	for(i = 0; i < MAX_ARRAY_SIZE; i++) // 배열끝까지 반복
	{
		for (j = 0; j < MAX_ARRAY_SIZE; j++) // j-1번쨰 값과 j의 값을 비교하는 for문
		{
			if (a[j-1] > a[j]) // j-1 번째 값이 j번째 값보다 크다면
			{
				// j-1 과 j 를 스왑해준다
				t = a[j-1];
				a[j-1] = a[j];
				a[j] = t; 
			}
		}
	}

	printf("----------------------------------------------------------------\n");
	printArray(a);

	return 0;
}

int shellSort(int *a) // 셀 정렬 함수 구현 - 삽입정렬을 보완하여 여러개의 부분 리스트로 만든 후 각 부분 리스트에 삽입 정렬로 정렬
{
	int i, j, k, h, v;

	printf("Shell Sort: \n");
	printf("----------------------------------------------------------------\n");

	printArray(a);

	for (h = MAX_ARRAY_SIZE/2; h > 0; h /= 2) // 단계가 수행될때마다 h의 값을 1/2 감소시킨다.
	{
		for (i = 0; i < h; i++) //  처음부터 h까지 반복
		{
			for(j = i + h; j < MAX_ARRAY_SIZE; j += h) // j 에서 MAXSIZE까지 j+h 씩 증가하면 반복
				{v = a[j]; // j번째 값을 v에 저장하고
				k = j; // 순서를 k에 저장한다.
				while (k > h-1 && a[k-h] > v) // 삽입정렬 구현
				{
					a[k] = a[k-h]; // 순서를 바꿔준다.
					k -= h;
				}
				a[k] = v; //이전값을 저장한다.
			}
		}
	}
	
	
	printf("----------------------------------------------------------------\n");
	printArray(a); // 배열을 출력한다.

	return 0;
	
}

int quickSort(int *a, int n) // 퀵 정렬 구현 함수 - 기준값을 중심으로 왼족 오른쪽을 부분집합으로 분할하여 정렬
{
	int v, t;
	int i, j;

	if (n > 1)
	{
		v = a[n-1]; //초기 상태 v는 기준값이 된다.
		i = -1; // 반으로 나눴을떄 왼쪽
		j = n - 1; // 반으로 나눴을때 오른쪽

		while(1)
		{
			while(a[++i] < v);
			while(a[--j] > v);

			if (i >= j) break;
			t = a[i]; // 만약 i<j 라면 오른쪽과 왼쪽값을 스왑해준다.
			a[i] = a[j];
			a[j] = t;
		}
		t = a[i]; // a[n-1] 위치로 스왑해서 다시 중심값을 정해주고 
		a[i] = a[n-1];
		a[n-1] = t;

		quickSort(a, i); //다시 그 위치를 중심으로 왼쪽
		quickSort(a+i+1, n-i-1); // 오른쪽을 나누어서 정렬한다.
	}


	return 0;
}

int hashCode(int key) { // 해시 알고리즘에 의해 생성된 정수 값인 해시 코드 함수 구현
   return key % MAX_HASH_TABLE_SIZE; // 입력받은 key를  max size로 나머지 값 계산한 것을 return 
}

int hashing(int *a, int **ht) //해싱 함수 구현 , 값을 바꾸기위해 더블포인터로 매기변수를 받는다.
{
	int *hashtable = NULL; // 정수형 포인터 해시테이블 선언후 NULL 값으로 초기화

	/* hash table이 NULL인 경우 메모리 할당 */
	if(*ht == NULL) {
		hashtable = (int*)malloc(sizeof(int) * MAX_ARRAY_SIZE); // 해시테이블에 메모리를 할당
		*ht = hashtable;  /* 할당된 메모리의 주소를 복사 --> main에서 배열을 control 할수 있도록 함*/
	} else {
		hashtable = *ht;	/* hash table이 NULL이 아닌경우, table 재활용, reset to -1 */
	}

	for(int i = 0; i < MAX_HASH_TABLE_SIZE; i++)
		hashtable[i] = -1;

	/*
	for(int i = 0; i < MAX_HASH_TABLE_SIZE; i++)
		printf("hashtable[%d] = %d\n", i, hashtable[i]);
	*/

	int key = -1;
	int hashcode = -1;
	int index = -1;
	for (int i = 0; i < MAX_ARRAY_SIZE; i++)
	{
		key = a[i];
		hashcode = hashCode(key);
		/*
		printf("key = %d, hashcode = %d, hashtable[%d]=%d\n", key, hashcode, hashcode, hashtable[hashcode]);
		*/
		if (hashtable[hashcode] == -1)
		{
			hashtable[hashcode] = key;
		} else 	{

			index = hashcode;

			while(hashtable[index] != -1)
			{
				index = (++index) % MAX_HASH_TABLE_SIZE;
				/*
				printf("index = %d\n", index);
				*/
			}
			hashtable[index] = key;
		}
	}

	return 0;
}

int search(int *ht, int key)
{
	int index = hashCode(key);

	if(ht[index] == key)
		return index;

	while(ht[++index] != key)
	{
		index = index % MAX_HASH_TABLE_SIZE;
	}
	return index;
}



