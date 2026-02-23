TARGETS=mutexes2

.PHONY: all clean

all: $(TARGETS)

mutexes2: mutexes2.c
	gcc -Wall -Wextra -o $@ $^

clean:
	rm -f $(TARGETS)
