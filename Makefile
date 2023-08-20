CC ?= gcc
CFLAGS ?= -Wall -Wextra -pedantic
XCFLAGS ?=

mukd: main.c
	$(CC) $(CFLAGS) $(XCFLAGS) main.c -o mukd

clean:
	rm -f mukd

.PHONY: clean release
