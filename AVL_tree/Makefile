CC = gcc
CFLAGS = -O1 -g -Wall
OBJS = node.o

%.o : %.c
	$(CC) $(CFLAGS) -c $< -o $@

node: node.o
	$(CC) $(CFLAGS) $< -o $@

clean : $(OBJS) 
	rm $^ node