TARGETS=forkpipe

.PHONY: all clean

all: $(TARGETS)

forkpipe: forkpipe.c
	gcc -Wall -Wextra -o $@ $^

clean:
	rm -f $(TARGETS)
