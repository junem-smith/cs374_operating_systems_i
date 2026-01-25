TARGETS=tokenize4

.PHONY: all clean

all: $(TARGETS)

tokenize4: tokenize4.c
	gcc -Wall -Wextra -o $@ $^

clean:
	rm -f $(TARGETS)
