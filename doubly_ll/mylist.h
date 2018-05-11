#ifndef _MYLIST_H_
#define _MYLIST_H_

typedef struct tagMyListElem {
	void *obj;
	struct tagMyListElem *next;
	struct tagMyListElem *prev;
} MyListElem;


typedef struct tagMyList {
	int num_members;
	MyListElem anchor;
	/* You do not have to set these function pointers */
	int (*Length)(struct tagMyList *);
	int (*Empty)(struct tagMyList *);
	int (*Append)(struct tagMyList *, void*);
	int (*Prepend)(struct tagMyList *, void*);
	void (*Unlink)(struct tagMyList *, MyListElem*);
	void (*UnlinkAll)(struct tagMyList *);
	int (*InsertBefore)(struct tagMyList *, void*, MyListElem*);
	int (*InsertAfter)(struct tagMyList *, void*, MyListElem*);
	MyListElem *(*First)(struct tagMyList *);
	MyListElem *(*Last)(struct tagMyList *);
	MyListElem *(*Next)(struct tagMyList *, MyListElem *);
	MyListElem *(*Prev)(struct tagMyList *, MyListElem *);
	MyListElem *(*Find)(struct tagMyList *, void *obj);
} MyList;

extern int MyListLength ARGS_DECL((MyList*));
extern int MyListEmpty ARGS_DECL((MyList*));
extern int MyListAppend ARGS_DECL((MyList*, void*));
extern int MyListPrepend ARGS_DECL((MyList*, void*));
extern void MyListUnlink ARGS_DECL((MyList*, MyListElem*));
extern void MyListUnlinkAll ARGS_DECL((MyList*));
extern int MyListInsertAfter ARGS_DECL((MyList*, void*, MyListElem*));
extern int MyListInsertBefore ARGS_DECL((MyList*, void*, MyListElem*));
extern MyListElem MyListFirst ARGS_DECL((MyList*));
extern MyListElem *MyListLast ARGS_DECL((MyList*));
extern MyListElem *MyListNext ARGS_DECL((MyList*, MyListElem*));
extern MyListElem *MyListPrev ARGS_DECL((MyList*, MyListElem*));
extern MyListElem *MyListFind ARGS_DECL((MyList*, void*));
extern int MyListInit ARGS_DECL((MyList*));

#endif /*_MYLIST_H_*/
