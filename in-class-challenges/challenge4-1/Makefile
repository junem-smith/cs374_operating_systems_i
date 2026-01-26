TARGETS=pipetest

.PHONY: all clean

all: $(TARGETS)

pipetest: pipetest.c
	gcc -Wall -Wextra -o $@ $^

clean:
	rm -f $(TARGETS)
