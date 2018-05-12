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

MyListElem *MyListNext(MyList* list, MyListElem* node){
	MyList*  current = list;

	while(current != node){
		current = current->next;
	}

	return current->next;

}

MyListElem *MyListPrev(MyList* list, MyListElem* node){
	MyList*  current = list;

	while(current != node){
		current = current->next;
	}

	return current->prev;

}


MyListElem *MyListFind(MyList* list, void * data){
	MyList*  current = list;

	while(current->obj != data){
		current = current->next;
	}

	return current;

}


MyListElem *MyListFirst(MyList* list){
	MyList*  current = list;

	while(current->obj != NULL){
		current = current->next;
	}

	return current->next;

}

MyListElem *MyListLast(MyList* list){
	MyList*  current = list;

	while(current->obj != NULL){
		current = current->next;
	}

	return current->prev;

}


MyListElem *MyListAppend(MyList* list, void * data){
	MyList*  current = list;

	while(current->obj != NULL){
		current = current->next;
	}

	MyListElem * new_elem = (MyListElem *)malloc(sizeof(MyListElem));
	new_elem->obj = data;

	new_elem->prev = current->prev;
	current->prev->next = new_elem;
	current->prev = new_elem;
	new_elem->next = current;

	list->num_members= list->num_members+1;

}

MyListElem *MyListPrepend(MyList* list, void * data){
	MyList*  current = list;

	while(current->obj != NULL){
		current = current->next;
	}

	MyListElem * new_elem = (MyListElem *)malloc(sizeof(MyListElem));
	new_elem->obj = data;


	new_elem->next = current->next;
	current->next->prev = new_elem;
	current->next = new_elem;
	new_elem->prev = current;

	list->num_members= list->num_members+1;

}

void MyListUnlink(MyList* list, MyListElem* node){
	MyList * current = list;

	while(current != node){
		current = current->next;
	}

	current->next->prev = current->prev;
	current->prev->next = current->next;

	current->next = NULL;
	current->prev = NULL;
}


int MyListInsertAfter(MyList * list, void * data , MyListElem * node){
	MyList * current = list;

	while(current != node){
		current = current->next;
	}

	MyListElem * new_elem = (MyListElem *)malloc(sizeof(MyListElem));
	new_elem->obj = data;

	current->next->prev = new_elem;
	current->next=  new_elem;
	new_elem->prev = current;
	new_elem->next->prev = new_elem;


}


int MyListInsertBefore(MyList * list, void * data , MyListElem * node){
	MyList * current = list;

	while(current != node){
		current = current->next;
	}

	MyListElem * new_elem = (MyListElem *)malloc(sizeof(MyListElem));
	new_elem->obj = data;

	current = current->prev;
	current->next->prev = new_elem;
	current->next=  new_elem;
	new_elem->prev = current;
	new_elem->next->prev = new_elem;


}
