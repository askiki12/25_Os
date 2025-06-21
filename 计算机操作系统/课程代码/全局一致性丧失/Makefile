all: mem-model

CFLAGS := -O2 -I.

mem-model: mem-model.c
	gcc $(CFLAGS) -o $@ $<

clean:
	rm -f mem-model
