TARGETS=mush

.PHONY: all clean

all: $(TARGETS)

mush: mush.c
	gcc -Wall -Wextra -o $@ $^

clean:
	rm -f $(TARGETS)
