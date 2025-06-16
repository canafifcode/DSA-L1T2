#include <stdio.h>
#include <stdlib.h>

struct node
{
    int element;
    struct node* next;
    struct node* prev;
};

typedef struct 
{
    // declare head, tail, cur and other variables you need
    struct node* head;
    struct node* tail;
    struct node* cur;
    int size;
} linkedList;

void init(linkedList* list)
{
    // implement initialization
    list-> head=NULL;
    list-> tail=NULL;
    list-> cur=NULL;
    list-> size=0;
}

void free_list(linkedList* list)
{
    // implement destruction of list
    struct node* tmp= list->head;
    while(tmp!=NULL){
        struct node* nxt=tmp->next;
        free(tmp);
        tmp=nxt;
    }
}

void print(linkedList* list)
{
    // implement list printing
    if(list->size==0){
        printf("[.]\n");
        return;
    }

    printf("[");
    struct node* tmp= list->head;
    while(tmp!=NULL){
        printf("%d ", tmp->element);
        if(tmp== list->cur)
        printf("\b| ");
        tmp=tmp->next;
    }
    printf("\b]\n");
}
 
void append(int item, linkedList* list)
{
    // implement append function
    struct node *newNode=  (struct node*)malloc(sizeof (struct node));
    newNode->element=item;
    newNode->next= NULL;
    newNode->prev= NULL;
    struct node* tmp=list->head;

    if(tmp==NULL){
        list->head=list->tail=list->cur=newNode;
    }
    
    else{
        list->tail->next=newNode;
        newNode->prev=list->tail;
        list->tail=newNode;
    }

    list->size++;
    print(list);
}

void insert(int item, linkedList* list)
{
    // implement insert function
    struct node *newNode=  (struct node*)malloc(sizeof (struct node));
    newNode->element=item;
    newNode->next= NULL;
    newNode->prev= NULL;
    //struct node* tmp=list->head;

    if(list->head==NULL){
        list->head=list->tail=list->cur=newNode;
    }

    else{
        newNode->prev=list->cur;
        newNode->next = list->cur->next;
        if(list->cur->next != NULL) {
            list->cur->next->prev = newNode;
        } else {
            list->tail = newNode;
        }
        list->cur->next = newNode;
        list->cur=newNode;
    }

    list->size++;
    print(list);
}

int delete_cur(linkedList* list)
{
    // implement deletion of current index function
    if(list->size == 0){
        printf("not valid operation\n");
        return -1; 
    }

    struct node* tmp= list->cur;
    int deleteitem= tmp->element;
    
    if(list->cur==list->head){
        list->head=list->cur->next;
        if(list->head != NULL) list->head->prev=NULL;
    }
    if(list->cur==list->tail){
        list->tail=tmp->prev;
        if(list->tail != NULL) list->tail->next=NULL;
    }
    else{
        tmp->prev->next= tmp->next;
        tmp->next->prev= tmp->prev;
    }

    list->cur=(tmp->next==NULL)?tmp->prev: tmp->next;

    list->size--;

    free(tmp);
    print(list);

    return deleteitem;
}



int size(linkedList* list)
{
    // implement size function
    return list->size;
}

void prev(int n, linkedList* list)
{
    for(int i=0; i<n && list->cur!= NULL && list->cur->prev!= NULL; i++){
        list->cur = list->cur->prev;
    }
    print(list);
}

void next(int n, linkedList* list)
{
    for(int i=0; i<n && list->cur!= NULL  && list->cur->next!= NULL; i++){
        list->cur = list->cur->next;
    }
    print(list);
}

int is_present(int n, linkedList* list)
{
    // implement presence checking function
    struct node* tmp=list->head;
    while(tmp!=NULL){
        if(tmp->element==n){
            return 1;
        }
        tmp=tmp->next;
    }
    return 0;
}

void clear(linkedList* list)
{
    // implement list clearing function
    free_list(list);
    list-> head=NULL;
    list-> tail=NULL;
    list-> cur=NULL;
    list-> size=0;
    print(list);
}

void delete_item(int item, linkedList* list)
{
    struct node* tmp = list->head;
    
    while (tmp != NULL) {
        if (tmp->element == item) {
            //struct node* next_node = tmp->next;
            struct node* prev_cur = list->cur;
            list->cur = tmp;
            delete_cur(list);
            if (prev_cur != tmp) {
                list->cur = prev_cur;
            }
            return;
        }
        tmp = tmp->next;
    }
    printf("%d not found\n", item);
}


void swap_ind(int ind1, int ind2, linkedList* list)
{
    // implement swap function
    struct node* temp1= list->head;
    struct node* temp2= list->head;
    int i=0;
    while(i<ind1 && temp1!=NULL){
        temp1= temp1->next;
        i++;
    }
    i=0;
    while(i<ind2 && temp2!=NULL){
        temp2= temp2->next;
        i++;
    }
    
    int temp= temp1->element;
    temp1->element= temp2->element;
    temp2->element=temp;

    print(list);
}

// you can define helper functions you need