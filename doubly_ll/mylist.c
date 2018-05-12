#include "mylist.h"
#include "cs402.h"

int MyListInit(MyList* list){
    list->num_members = 0;
}

int MyListLength(MyList* list){
    return list->num_members;
}

int MyListEmpty(MyList*list){
    return (list->num_members == 0);
}
