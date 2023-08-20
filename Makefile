CC ?= gcc
CFLAGS ?= -Wall -Wextra -pedantic
XCFLAGS ?=

mukd: obj/main.o obj/screen.o
	$(CC) $(CFLAGS) $(XCFLAGS) obj/main.o obj/screen.o -o mukd

obj/%.o: src/%.c
	@mkdir -p obj
	$(CC) $(CFLAGS) $(XCFLAGS) -c $< -o $@

clean:
	rm -f mukd
	rm -rf obj

.PHONY: clean
