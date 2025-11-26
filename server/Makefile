HEADERS = $(wildcard *.h)
SOURCES = $(wildcard *.c)
OBJECTS = $(patsubst %.c,%.o,$(SOURCES))

COMMON = session.o files.o

.PHONY: clean build install

build: $(OBJECTS)
	clang -o login.cgi login.o $(COMMON)

install: build
	sudo cp -f *.cgi /var/www/seaport/

$(OBJECTS): %.o: %.c $(HEADERS)
	clang -c -o $@ $<

clean:
	rm -rf *.cgi *.o

