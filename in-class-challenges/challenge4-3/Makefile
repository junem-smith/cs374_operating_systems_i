TARGETS=printffile

.PHONY: all clean

all: $(TARGETS)

printffile: printffile.c
	gcc -Wall -Wextra -o $@ $^

clean:
	rm -f $(TARGETS)
