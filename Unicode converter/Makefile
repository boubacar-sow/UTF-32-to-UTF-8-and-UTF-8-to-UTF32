CC = gcc
CCFLAGS = -Wall -g -Wextra
DEPS = unicode.h

main: main.o unicode.o testUnicodeHelper.o
	$(CC) -o $@ $^ $(CCFLAGS)

%.o: %.c $(DEPS)
	$(CC) -c -o $@ $< $(CCFLAGS)
	
