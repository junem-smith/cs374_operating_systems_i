TARGETS=getsize

.PHONY: all clean

all: $(TARGETS)

getsize: getsize.c
	gcc -Wall -Wextra -o $@ $^

clean:
	rm -f $(TARGETS)
