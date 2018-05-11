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
};