LDFLAGS += $(shell pkg-config --libs glib-2.0) -lm -lunicorn -lpthread

TESTS = mast3r

all: $(TESTS)
	strip -s $(TESTS)

clean:
	rm -f $(TESTS)

%: %.c
		$(CC) $(CFLAGS) $^ $(LDFLAGS) -o $@

.PHONY: all clean
