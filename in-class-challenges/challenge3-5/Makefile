TARGETS=tokenize3

.PHONY: all clean

all: $(TARGETS)

tokenize3: tokenize3.c
	gcc -Wall -Wextra -o $@ $^

clean:
	rm -f $(TARGETS)
