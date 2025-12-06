HEADERS = $(wildcard *.h)
SOURCES = $(wildcard *.c)
OBJECTS = $(patsubst %.c,%.o,$(SOURCES))

COMMON = session.o files.o input.o form.o base64.o db.o -lpq

.PHONY: clean build install

build: $(OBJECTS)
	clang -o login.cgi login.o $(COMMON)
	clang -o html.cgi html.o $(COMMON)
	clang -o role.cgi role.o $(COMMON)

install: build
	sudo cp -f *.cgi /var/www/seaport/

$(OBJECTS): %.o: %.c $(HEADERS)
	clang -c -o $@ $<

clean:
	rm -rf *.cgi *.o

