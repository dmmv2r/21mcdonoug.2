C = gcc
CFLAGS = -Wall -g

TARGETS = master bin_adder

all: $(TARGETS)

master: master.o
	$(C) $(CFLAGS) -o $@ master.o

bin_adder: bin_adder.o
	$(C) $(CFLAGS) -o $@ bin_adder.o

clean:
	rm -rf *.o $(TARGETS)
