TARGETS=mymkdir

.PHONY: all clean

all: $(TARGETS)

mymkdir: mymkdir.c
	gcc -Wall -Wextra -o $@ $^

clean:
	rm -f $(TARGETS)
