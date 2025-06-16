#include <stdio.h>
#include <stdlib.h>

typedef struct 
{
    //declare variables you need
    int *array;
    int size;
    int current;
    int capacity;
} arrayList;

void init(arrayList* list)
{
    // implement initialization
    list->size = 0;
    list->capacity = 2;// for 0 size->2 cap
    list->current=0;
    list->array=(int*)malloc(list->capacity*sizeof(int));
    if(list->array==NULL){
        return;
    }
}

void free_list(arrayList* list)
{
    // implement destruction of list
    free(list->array);
    list->array = NULL;
    list->size = 0;
    list->capacity = 2;
}

void increase_capacity(arrayList* list)
{
    // implement capacity increase
    if(list->size > 0.5* list->capacity){
        int new_capacity = list->capacity * 2;
        int *newlist =(int *)realloc(list->array, new_capacity*sizeof(int));
        if(newlist==NULL) return;
        list->array= newlist;
        printf("Capacity increased from %d to %d\n", list->capacity, new_capacity);
        list->capacity= new_capacity;
    }
    
}

void decrease_capacity(arrayList* list)
{
    // implement capacity decrease
    if(list->size < 0.25* list->capacity && list->capacity > 2){
        int new_capacity = list->capacity / 2;
        int *newlist =(int *)realloc(list->array, new_capacity*sizeof(int));
        if(newlist==NULL) return;
        list->array= newlist;
        printf("Capacity decreased from %d to %d\n", list->capacity, new_capacity);
        list->capacity= new_capacity;  
    }
}

void print(arrayList* list)
{
    // implement list printing
    if(list->size==0){
        printf("[.]\n");
        return;
    }

    printf("[");
    for(int i=0; i<list->size; i++){
        printf("%d ", list->array[i]);
        if(i== list->current-1)
        printf("\b| ");
    }
    // if(list->current == 0) printf("| ");
    // else if(list->current == list->size) printf("| ");
    printf("\b]\n");
}

void insert(int item, arrayList* list)
{
    // implement insert function
    for(int i= list->size; i>= list->current+1; i--){
        list->array[i]=list->array[i-1];
    }
    list->array[list->current]=item;
    list->size++;
    list->current++;
    increase_capacity(list);
    print(list);
     
}

int delete_cur(arrayList* list)
{
    // implement deletion of current index function
    if(list->size == 0){
        printf("not valid operation\n");
        return -1; 
    }


    int deleteval = list->array[list->current-1];
    for(int i= list->current-1; i< list->size-1; i++){
        list->array[i]=list->array[i+1];
    }
    //list->array[list->size-1]=NULL;
    list->size--;


    if(list->current>=list->size){
        list->current=(list->size==0)? 0: list->size;
    }

    
    decrease_capacity(list);
    print(list);

    return deleteval;
}

void append(int item, arrayList* list)
{
    // implement append function
    list->array[list->size++] = item;
    if(list->size == 1)
        list->current = 1;
    increase_capacity(list);
    print(list);
    
}

int size(arrayList* list)
{
    // implement size function
    return list->size;
}

void prev(int n, arrayList* list)
{
    // implement prev function
    for(int i=0; i<n && list->current>0 ; i++){
        list->current--;
    }
    print(list);
}

void next(int n, arrayList* list)
{
    // implement next function
    for(int i=0; i<n && list->current<list->size ; i++){
        list->current++;
    }
    print(list);
}

int is_present(int n, arrayList* list)
{
    // implement presence checking function
    for(int i=0; i<list->size; i++){
        if(list->array[i]==n) {
            return 1;
        }
    }
    return 0;
}

void clear(arrayList* list)
{
    // implement list clearing function
    list->size=0;
    list->current=0;
    print(list);
}

void delete_item(int item, arrayList* list)
{
    int i;
    for (i = 0; i < list->size; i++) {
        if (item == list->array[i])
            break;
    }

    if (i == list->size) {
        printf(" %d not found\n", item);
        return;
    }

    for (int j = i; j < list->size - 1; j++) {
        list->array[j] = list->array[j + 1];
    }

    list->size--;
    

    decrease_capacity(list);
    print(list);
    
}



void swap_ind(int ind1, int ind2, arrayList* list)
{
    if(ind1<0 || ind1>=list->size || ind2<0 || ind2>=list->size) return;

    int temp= list->array[ind1];
    list->array[ind1]=list->array[ind2];
    list->array[ind2]=temp;
    print(list);
}