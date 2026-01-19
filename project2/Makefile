TARGETS=filescanner

.PHONY: all clean

all: $(TARGETS)

filescanner: filescanner.c
	gcc -Wall -Wextra -o $@ $^

clean:
	rm -f $(TARGETS)
