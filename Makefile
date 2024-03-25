CC = gcc
CFLAGS = -O1 -g -Wall
OBJS = binary_log2.o

%.o : %.c
	$(CC) $(CFLAGS) -c $< -o $@

log2 : binary_log2.o
	$(CC) $(CFLAGS) $< -o $@

clean : $(OBJS) 
	rm $^ log2