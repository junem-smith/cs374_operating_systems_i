TARGETS=grayscaler

.PHONY: all clean

all: $(TARGETS)

grayscaler: grayscaler.c ppm.c
	gcc -Wall -Wextra -o $@ $^

clean:
	rm -f $(TARGETS)
