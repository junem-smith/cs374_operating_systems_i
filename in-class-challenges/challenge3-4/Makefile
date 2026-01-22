TARGETS=tokenize2

.PHONY: all clean

all: $(TARGETS)

tokenize2: tokenize2.c
	gcc -Wall -Wextra -o $@ $^

clean:
	rm -f $(TARGETS)
