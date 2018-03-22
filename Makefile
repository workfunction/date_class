CC     = g++
CFLAGS = -std=c++11 -Wall -O3

OBJS   = main.o date.o
EXEC   = Date

.PHONY: clean run

SRC_MAIN  = main.cpp
SRC_CLASS = Date.cpp Date.h

all: clean $(EXEC) run

Date: $(OBJS)
	$(CC) $(OBJS) -o $@ 

main.o: $(SRC_MAIN)
	$(CC) $(CFLAGS) -c -o $@ $<

date.o: $(SRC_CLASS)
	$(CC) $(CFLAGS) -c -o $@ $<

clean:
	rm $(EXEC) $(OBJS)

run:
	./$(EXEC)