/*
 * Author:      William Chia-Wei Cheng (bill.cheng@acm.org)
 *
 * @(#)$Id: listtest.c,v 1.1 2013/01/10 18:02:44 william Exp $
 */

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <sys/time.h>

#include "cs402.h"

#include "mylist.h"

static char gszProgName[MAXPATHLENGTH];

int gnDebug=0;

/* ----------------------- Utility Functions ----------------------- */

static
void Usage()
{
    fprintf(stderr,
            "usage: %s %s\n",
            gszProgName, "test");
    exit(-1);
}

static
void ProcessOptions(int argc, char *argv[])
{
    for (argc--, argv++; argc > 0; argc--, argv++) {
        if (*argv[0] == '-') {
            if (strcmp(*argv, "-debug") == 0) {
                gnDebug++;
            } else {
                Usage();
            }
        } else {
            Usage();
        }
    }
}

static
void SetProgramName(char *s)
{
    char *c_ptr=strrchr(s, DIR_SEP);

    if (c_ptr == NULL) {
        strcpy(gszProgName, s);
    } else {
        strcpy(gszProgName, ++c_ptr);
    }
}

/* ----------------------- Test() ----------------------- */

static
void CreateTestList(MyList *pList, int num_items)
{
    int i=0;

    for (i=0; i < num_items; i++) {
        (void)MyListAppend(pList, (void*)i);
    }
}

static
int RandomIndex(int num_values)
    /* return a random value >= 0 and <= num_values-1 */
{
    double dval=(drand48()*((double)num_values))-((double)0.5);
    int idx=0;

    if (dval < ((double)(-0.5))) dval = (double)(-0.5);
    idx = round(dval);
    if (idx < 0) idx = 0;
    if (idx >= num_values) idx = num_values-1;

    return idx;
}

static
void RandomShuffle(MyList *pList, int num_items)
{
    int i=0;
    MyList list2;
    MyListElem *elem=NULL;

    memset(&list2, 0, sizeof(MyList));
    (void)MyListInit(&list2);

    for (i=0; i < num_items; i++) {
        int j=0, idx=0, num_in_list=num_items-i;
        void *obj=NULL;

        idx = RandomIndex(num_in_list);
        for (elem=MyListFirst(pList); elem != NULL; elem=MyListNext(pList, elem)) {
            if (j == idx) {
                break;
            }
            j++;
        }
        if (elem == NULL) {
            fprintf(stderr, "Unrecoverable error in RandomShuffle().\n");
            exit(1);
        }
        obj = elem->obj;
        MyListUnlink(pList, elem);
        (void)MyListAppend(&list2, obj);
    }
    if (!MyListEmpty(pList)) {
        fprintf(stderr, "List not empty in RandomShuffle().\n");
        exit(1);
    }
    for (elem=MyListFirst(&list2); elem != NULL; elem=MyListNext(&list2, elem)) {
        (void)MyListAppend(pList, elem->obj);
    }
}

static
void FindAllInList(MyList *pList, int num_items)
{
    int i=0;

    for (i=0; i < num_items; i++) {
        if (MyListFind(pList, (void*)i) == NULL) {
            fprintf(stderr, "Cannot find %1d in FindAllInList().\n", i);
        }
    }
}

static
void PrintTestList(MyList *pList, int num_items)
{
    MyListElem *elem=NULL;

    if (MyListLength(pList) != num_items) {
        fprintf(stderr, "List length is not %1d in PrintTestList().\n", num_items);
        exit(1);
    }
    for (elem=MyListFirst(pList); elem != NULL; elem=MyListNext(pList, elem)) {
        int ival=(int)(elem->obj);

        fprintf(stdout, "%1d ", ival);
    }
    fprintf(stdout, "\n");
}

static
void CopyTestList(MyList *pListFrom, MyList *pListTo)
{
    MyListElem *elem=NULL;

    for (elem=MyListFirst(pListFrom); elem != NULL; elem=MyListNext(pListFrom, elem)) {
        (void)MyListAppend(pListTo, elem->obj);
    }
}

static
void BubbleForward(MyList *pList, MyListElem **pp_elem1, MyListElem **pp_elem2)
    /* (*pp_elem1) must be closer to First() than (*pp_elem2) */
{
    MyListElem *elem1=(*pp_elem1), *elem2=(*pp_elem2);
    void *obj1=elem1->obj, *obj2=elem2->obj;
    MyListElem *elem1prev=MyListPrev(pList, elem1);
    MyListElem *elem2next=MyListNext(pList, elem2);

    MyListUnlink(pList, elem1);
    MyListUnlink(pList, elem2);
    if (elem1prev == NULL) {
        (void)MyListPrepend(pList, obj2);
        *pp_elem1 = MyListFirst(pList);
    } else {
        (void)MyListInsertAfter(pList, obj2, elem1prev);
        *pp_elem1 = MyListNext(pList, elem1prev);
    }
    if (elem2next == NULL) {
        (void)MyListAppend(pList, obj1);
        *pp_elem2 = MyListLast(pList);
    } else {
        (void)MyListInsertBefore(pList, obj1, elem2next);
        *pp_elem2 = MyListPrev(pList, elem2next);
    }
}

static
void BubbleSortForwardList(MyList *pList, int num_items)
{
    MyListElem *elem=NULL;
    int i=0;

    if (MyListLength(pList) != num_items) {
        fprintf(stderr, "List length is not %1d in BubbleSortForwardList().\n", num_items);
        exit(1);
    }
    for (i=0; i < num_items; i++) {
        int j=0, something_swapped=FALSE;
        MyListElem *next_elem=NULL;

        for (elem=MyListFirst(pList), j=0; j < num_items-i-1; elem=next_elem, j++) {
            int cur_val=(int)(elem->obj), next_val=0;

            next_elem=MyListNext(pList, elem);
            next_val = (int)(next_elem->obj);

            if (cur_val > next_val) {
                BubbleForward(pList, &elem, &next_elem);
                something_swapped = TRUE;
            }
        }
        if (!something_swapped) break;
    }
}

static
void BubbleBackward(MyList *pList, MyListElem **pp_elem1, MyListElem **pp_elem2)
    /* (*pp_elem1) must be closer to Last() than (*pp_elem2) */
{
    MyListElem *elem1=(*pp_elem1), *elem2=(*pp_elem2);
    void *obj1=elem1->obj, *obj2=elem2->obj;
/*  MyListElem *elem1prev=MyListPrev(pList, elem1); */
    MyListElem *elem1next=MyListNext(pList, elem1);
    MyListElem *elem2prev=MyListPrev(pList, elem2);
/*  MyListElem *elem2next=MyListNext(pList, elem2); */

    MyListUnlink(pList, elem1);
    MyListUnlink(pList, elem2);
    if (elem1next == NULL) {
        (void)MyListAppend(pList, obj2);
        *pp_elem1 = MyListLast(pList);
    } else {
        (void)MyListInsertBefore(pList, obj2, elem1next);
        *pp_elem1 = MyListPrev(pList, elem1next);
    }
    if (elem2prev == NULL) {
        (void)MyListPrepend(pList, obj1);
        *pp_elem2 = MyListFirst(pList);
    } else {
        (void)MyListInsertAfter(pList, obj1, elem2prev);
        *pp_elem2 = MyListNext(pList, elem2prev);
    }
}

static
void BubbleSortBackwardList(MyList *pList, int num_items)
{
    MyListElem *elem=NULL;
    int i=0;

    if (MyListLength(pList) != num_items) {
        fprintf(stderr, "List length is not %1d in BubbleSortBackwardList().\n", num_items);
        exit(1);
    }
    for (i=0; i < num_items; i++) {
        int j=0, something_swapped=FALSE;
        MyListElem *prev_elem=NULL;

        for (elem=MyListLast(pList), j=0; j < num_items-i-1; elem=prev_elem, j++) {
            int cur_val=(int)(elem->obj), prev_val=0;

            prev_elem=MyListPrev(pList, elem);
            prev_val = (int)(prev_elem->obj);

            if (cur_val < prev_val) {
                BubbleBackward(pList, &elem, &prev_elem);
                something_swapped = TRUE;
            }
        }
        if (!something_swapped) break;
    }
}
static
void CompareTestList(MyList *pList1, MyList *pList2, int num_items)
{
    MyListElem *elem1=NULL, *elem2=NULL;
    int idx=0;

    if (MyListLength(pList1) != num_items) {
        fprintf(stderr, "List1 length is not %1d in CompareTestList().\n", num_items);
        exit(1);
    }
    if (MyListLength(pList2) != num_items) {
        fprintf(stderr, "List2 length is not %1d in CompareTestList().\n", num_items);
        exit(1);
    }
    for (elem1=MyListFirst(pList1), elem2=MyListFirst(pList2);
            elem1 != NULL && elem2 != NULL;
            elem1=MyListNext(pList1, elem1), elem2=MyListNext(pList2, elem2), idx++) {
        int ival1=(int)(elem1->obj);
        int ival2=(int)(elem2->obj);

        if (ival1 != ival2) {
            fprintf(stderr, "(%1d,%1d): item %1d not identical in CompareTestList().\n", ival1, ival2, idx);
            exit(1);
        }
    }
}

static
void DoTest()
{
    int num_items=64;
    MyList list, list2;

    memset(&list, 0, sizeof(MyList));
    memset(&list2, 0, sizeof(MyList));
    (void)MyListInit(&list);
    (void)MyListInit(&list2);

    CreateTestList(&list, num_items);
    RandomShuffle(&list, num_items);
    FindAllInList(&list, num_items);
    CopyTestList(&list, &list2);

    BubbleSortForwardList(&list, num_items);
    if (gnDebug > 0) PrintTestList(&list, num_items);

    BubbleSortBackwardList(&list2, num_items);
    if (gnDebug > 0) PrintTestList(&list2, num_items);

    CompareTestList(&list, &list2, num_items);

    MyListUnlinkAll(&list);
    MyListUnlinkAll(&list2);
}

/* ----------------------- Process() ----------------------- */

static
void Process()
{
    int i=0, num_itr=10;

    if (gnDebug > 0) {
        srand48(gnDebug);
    } else {
        struct timeval tv;

        (void)gettimeofday(&tv, NULL);
        srand48(((long)tv.tv_sec)+((long)tv.tv_usec));
    }
    for (i=0; i < num_itr; i++) {
        DoTest();
    }
}

/* ----------------------- main() ----------------------- */

int main(int argc, char *argv[])
{
    SetProgramName(*argv);
    ProcessOptions(argc, argv);

    Process();
    return(0);
}
