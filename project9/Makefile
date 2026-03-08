TARGETS=pc

.PHONY: all clean

all: $(TARGETS)

pc: pc.c eventbuf.c
	gcc -Wall -Wextra -o $@ $^

clean:
	rm -f $(TARGETS)
