TARGETS=deadlock

.PHONY: all clean

all: $(TARGETS)

deadlock: deadlock.c
	gcc -Wall -Wextra -o $@ $^

clean:
	rm -f $(TARGETS)
