CC ?= gcc
CFLAGS ?= -Wall -Wextra -pedantic
XCFLAGS ?=

mukd: main.c screen.c
	$(CC) $(CFLAGS) $(XCFLAGS) main.c screen.c -o mukd

clean:
	rm -f mukd

.PHONY: clean release
