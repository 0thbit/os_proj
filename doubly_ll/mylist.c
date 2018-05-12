#include "mylist.h"
#include "cs402.h"

int MyListInit(MyList* list){
    list->num_members = 0;
    list->anchor.next = &(list->anchor);
    list->anchor.prev = &(list->anchor);
    list->anchor.obj = NULL;
    return 0;
}

int MyListLength(MyList* list){
    return list->num_members;
}

int MyListEmpty(MyList* list){
    return (list->num_members == 0);
}

void MyListUnlinkAll(MyList* list){
    if (MyListEmpty(list)){
        return;
    }
    MyListElem cur =
}
