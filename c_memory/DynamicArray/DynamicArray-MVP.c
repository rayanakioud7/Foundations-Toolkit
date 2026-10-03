#include <stdio.h>
#include <stdlib.h>

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

    for(int i=0; i<5; i++){
        dynarray_push_back(MyDynArray, 10*i);
        printf("new value: %d, size: %zu, capacity: %zu \n", i*10, MyDynArray->size, MyDynArray->capacity);
    }

    //test get
    printf("Element at index 2: %d\n", dynarray_get(MyDynArray, 2));
    
    // test set
    dynarray_set(MyDynArray, 2, 999);
    printf("Element at index 2 after set: %d\n", dynarray_get(MyDynArray, 2));

    dynarray_free(MyDynArray);
    return 0;
}