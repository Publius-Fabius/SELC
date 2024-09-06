# SELC Makefile

CFLAGS = -g -std=c99 -pedantic -Wconversion -Wall -I include
CC = gcc

# error.h
build/selc/error.o : source/selc/error.c include/selc/error.h
	$(CC) $(CFLAGS) -c -o $@ $<
bin/test_error : tests/selc/error.c build/selc/error.o
	$(CC) $(CFLAGS) -o $@ $^
lib/libselc.a : \
	build/selc/error.o
	ar -crs $@ $^

clean:
	rm build/selc/error.o || true
	rm lib/libselc.a || true 
	rm bin/test_error || true