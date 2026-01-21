TARGETS=tokenize

.PHONY: all clean

all: $(TARGETS)

tokenize: tokenize.c
	gcc -Wall -Wextra -o $@ $^

clean:
	rm -f $(TARGETS)
