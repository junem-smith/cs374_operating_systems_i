TARGETS=producer consumer

.PHONY: all clean

all: $(TARGETS)


producer: producer.c
	gcc -Wall -Wextra -o $@ $^
consumer: consumer.c
	gcc -Wall -Wextra -o $@ $^

clean:
	rm -f $(TARGETS)