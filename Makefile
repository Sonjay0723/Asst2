FLAGC = -c
FLAGO = -o

all:
	$(error hhhhh)

proc: multitest_proc.c multitest.h
	gcc $(FLAGC) multitest_proc.c
	gcc $(FLAGO) searchtest searchtest.c multitest_proc.o -lm

thread: multitest_thread.c multitest.h
	gcc $(FLAGC) multitest_thread.c
	gcc $(FLAGO) searchtest searchtest.c multitest_thread.o -lpthread -lm

