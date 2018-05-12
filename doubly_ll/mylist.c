#include "mylist.h"
#include "cs402.h"

int MyListLength(MyList* list){
    return list->num_members;
}

int MyListEmpty(MyList*list){
    return (list->num_members == 0);
}
