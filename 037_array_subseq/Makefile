CFLAGS = -Wall -Werror

mySeq: test-subseq.o maxSeq.o
	gcc -o mySeq test-subseq.o maxSeq.o
maxSeq.o: maxSeq.c
	gcc -c maxSeq.c $(CFLAGS)
test-subseq.o: test-subseq.c
	gcc -c test-subseq.c $(CFLAGS)
