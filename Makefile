
CC = gcc

CFLAGS = -ansi -Wall -g -O0 -Wwrite-strings -Wshadow -pedantic-errors \
	 -fstack-protector-all -Wextra

PROGS =  public01 public02 public03 public04 public05 public06 \
	public07 student_tests 

all: $(PROGS)

public01: public01.o calendar.o
	$(CC) -o public01 public01.o calendar.o

public02: public02.o calendar.o
	$(CC) -o public02 public02.o calendar.o

public03: public03.o calendar.o
	$(CC) -o public03 public03.o calendar.o

public04: public04.o calendar.o
		$(CC) -o public04 public04.o calendar.o

public05: public05.o calendar.o
		$(CC) -o public05 public05.o calendar.o

public06: public06.o calendar.o
	$(CC) -o public06 public06.o calendar.o

public07: public07.o calendar.o
		$(CC) -o public07 public07.o calendar.o



%.o: %.c calendar.h
	$(CC) $(CFLAGS) -c $<



student_tests: student_tests.o calendar.o
	$(CC) -o student_tests student_tests.o calendar.o


calendar.o: calendar.c calendar.h
	gcc $(CFLAGS) -c calendar.c -o calendar.o

clean:
	@echo "cleaning my system"
	rm -f *.o $(PROGS) a.out



