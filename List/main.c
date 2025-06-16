#include <stdio.h>
//#include "arrayList.h"
#include "linkedList.h"

int main()
{
    FILE* file = fopen("in.txt", "r");
    if(file == NULL){
        return 1;
    }

    //arrayList list;
    linkedList list;
    init(&list);

    int func, param, param2;
     while(fscanf(file, "%d", &func) == 1 && func != 0)
    {
        if(func == 1 && fscanf(file, "%d", &param) == 1){
            printf("Insert %d\n", param);
            insert(param, &list);
        }
        else if(func == 2){
            printf("Delete current item\n");
            int ret = delete_cur(&list);
            printf("%d is deleted\n", ret);
        }
        else if(func == 3 && fscanf(file, "%d", &param) == 1){
            printf("Append %d\n", param);
            append(param, &list);
        }
        else if(func == 4){
            int ret = size(&list);
            printf("Size of the list is %d\n", ret);
        }
        else if(func == 5 && fscanf(file, "%d", &param) == 1){
            printf("Prev %d\n", param);
            prev(param, &list);
        }
        else if(func == 6 && fscanf(file, "%d", &param) == 1){
            printf("Next %d\n", param);
            next(param, &list);
        }
        else if(func == 7 && fscanf(file, "%d", &param) == 1){
            int ret = is_present(param, &list);
            if(ret){
                printf("%d is present\n", param);
            }
            else{
                printf("%d is not present\n", param);
            }
        }
        else if(func == 8){
            printf("Clear list\n");
            clear(&list);
        }
        else if(func == 9 && fscanf(file, "%d", &param) == 1){
            printf("Delete %d\n", param);
            delete_item(param, &list);
        }
        else if(func == 10 && fscanf(file, "%d %d", &param, &param2) == 2){
            printf("Swap index %d and %d\n", param, param2);
            swap_ind(param, param2, &list);
        }
        printf("\n");
    }

    free_list(&list);
    return 0;
}
