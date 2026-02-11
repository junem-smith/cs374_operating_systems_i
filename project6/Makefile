TARGETS=speed

.PHONY: all clean

all: $(TARGETS)

speed: speed.c
	gcc -Wall -Wextra -o $@ $^

clean:
	rm -f $(TARGETS)
