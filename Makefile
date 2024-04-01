CC = gcc
CFLAGS = -O1 -g -Wall
OBJS = binary_log2.o hamming_distance.o mod.o

%.o : %.c
	$(CC) $(CFLAGS) -c $< -o $@

log2 : binary_log2.o
	$(CC) $(CFLAGS) $< -o $@

hamming : hamming_distance.o
	$(CC) $(CFLAGS) $< -o $@

mod : mod.o
	$(CC) $(CFLAGS) $< -o $@

clean : $(OBJS) 
	rm $^ log2 hamming mod