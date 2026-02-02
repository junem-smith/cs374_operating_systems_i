TARGETS=lswc redirout

.PHONY: all clean

all: $(TARGETS)


lswc: lswc.c
	gcc -Wall -Wextra -o $@ $^
redirout: redirout.c
	gcc -Wall -Wextra -o $@ $^

clean:
	rm -f $(TARGETS)