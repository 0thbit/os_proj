#ifndef MAX_TIMESTAMP_LENGTH
#define MAX_TIMESTAMP_LENGTH 10
#endif

#ifndef MAX_LINE_LENGTH
#define MAX_LINE_LENGTH 1024
#endif

#ifndef MAX_AMOUNT_LENGTH
#define MAX_AMOUNT_LENGTH 10
#endif

#ifndef LINE_LENGTH
#define LINE_LENGTH 80
#endif

#ifndef _MYDATA_H_
#define _MYDATA_H_

enum readStatus{Type, Timestamp, Amount, Description};

// Data structure to store one line of file
typedef struct tagMyTransData {
    char type;
    unsigned int timestamp;
    int amount;
    char description[MAX_LINE_LENGTH];
} MyTransData;

#endif /*_MYDATA_H_*/
