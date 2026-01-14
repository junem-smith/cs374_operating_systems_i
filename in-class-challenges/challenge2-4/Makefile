TARGETS=myls

.PHONY: all clean

all: $(TARGETS)

myls: myls.c
	gcc -Wall -Wextra -o $@ $^

clean:
	rm -f $(TARGETS)
