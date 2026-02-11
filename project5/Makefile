TARGETS=appendlog

.PHONY: all clean

all: $(TARGETS)

appendlog: appendlog.c
	gcc -Wall -Wextra -o $@ $^

clean:
	rm -f $(TARGETS)
