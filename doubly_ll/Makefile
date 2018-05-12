doubly_ll: doubly_ll.o mylist.o
	gcc -o doubly_ll -g doubly_ll.o mylist.o

doubly_ll.o: doubly_ll.c mylist.h mydata.h
	gcc -g -c -Wall doubly_ll.c

mylist.o: mylist.c mylist.h
	gcc -g -c -Wall mylist.c

clean:
	rm -f *.o doubly_ll