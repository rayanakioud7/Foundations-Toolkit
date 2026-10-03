#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define DA_GROWTH 2

typedef struct {
    int *data;
    size_t size;
    size_t capacity;
}DynamicArray;

void dynarray_free(DynamicArray *arr){
    if(arr ==NULL) return;
    free(arr->data);
    free(arr);
}

DynamicArray* dynarray_create(size_t initial_capacity){
    //first we need to allocate memory for the struct
    DynamicArray *arr =malloc(sizeof(DynamicArray));
    if(arr==NULL){ //if the memory is full we fallback
        return NULL;
    }
    //if the intial capcity is set to 0 then no memory is allocated
    if(initial_capacity==0){
        arr->data =NULL;
        arr->capacity = 0;
    }else{
        // arr ->data = malloc(initial_capacity*sizeof(int)); this works but not optimized if the type changed
        arr->data = malloc(initial_capacity*sizeof(*(arr->data)));
        if(arr->data==NULL){
            free(arr);
            return NULL;
        }
        arr ->capacity = initial_capacity;
    }


    arr->size = 0;
    return arr;
}

void dynarray_push_naive(DynamicArray *arr, int value){
    if(arr->size == arr->capacity){
        size_t new_capacity = arr->capacity;
        if(arr->capacity == 0){
            new_capacity =1;
        }else{
            new_capacity++;
        }
        int *new_data = realloc(arr->data, new_capacity*sizeof(*(arr->data)));
        if(new_data==NULL){
            return;
        }
        arr->data = new_data;
        arr->capacity = new_capacity;
    }
    arr->data[arr->size]=value;
    arr->size++;
}

void dynarray_push_back(DynamicArray *arr, int value){
    
    if(arr->size == arr->capacity){
        size_t new_capacity = arr->capacity;
        if(arr->capacity==0){
            new_capacity = 1;
        }else{
        new_capacity*=DA_GROWTH;
        }
        int *new_data = realloc(arr->data, new_capacity*sizeof(*(arr->data)));
        if(new_data == NULL){
            return;
        }
        arr->data = new_data;
        arr->capacity = new_capacity;
    }


    arr->data[arr->size] = value;
    arr->size++;
}

int dynarray_get(DynamicArray *arr, size_t index){
    if(index>=arr->size){
        printf("Error; index %zu out of bound (size %zu)\n", index, arr->size);
        exit(EXIT_FAILURE);
    }
    return arr->data[index];
}

void dynarray_set(DynamicArray *arr, size_t index, int value){
    if(index>=arr->size){
        printf("Error; index %zu out of bound (size %zu)\n", index, arr->size);
        exit(EXIT_FAILURE);
    }
    arr->data[index]=value;
}



int main(){
    DynamicArray *MyDynArray = dynarray_create(2);


    DynamicArray *MyDynArrayNaive = dynarray_create(2);

    clock_t start_naive = clock();
    for (int i =0; i<100000; i++){
        dynarray_push_naive(MyDynArrayNaive, i);
    }
    clock_t end_naive = clock();
    double time_naive = (double)(end_naive-start_naive)/CLOCKS_PER_SEC;


    clock_t start_amortized = clock();
    for (int i =0; i<100000; i++){
        dynarray_push_back(MyDynArray, i);
    }
    clock_t end_amortized = clock();
    double time_amortized = (double)(end_amortized-start_amortized)/CLOCKS_PER_SEC;

    printf("Naive (+1 realloc per push), 100k elements:     %lf\n", time_naive);
    printf("Doubling (amortized push),     100k elements:   %lf\n", time_amortized);

    dynarray_free(MyDynArray);
    dynarray_free(MyDynArrayNaive);


    return 0;
}