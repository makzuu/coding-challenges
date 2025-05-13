TARGET=cut
CC=gcc
CFILES=$(wildcard *.c)
OBJECTS=$(patsubst %.c, %.o, $(CFILES))

default: $(TARGET)

$(TARGET): $(OBJECTS)
	$(CC) -o $@ $^

%.o: %.c
	$(CC) -g -c $<

clean:
	rm -f *.o
	rm -f $(TARGET)
