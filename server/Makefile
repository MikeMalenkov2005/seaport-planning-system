HEADERS = $(wildcard *.h)
SOURCES = $(wildcard *.c)
OBJECTS = $(patsubst %.c,%.o,$(SOURCES))

COMMON = session.o files.o input.o form.o base64.o db.o
MODULES = login.cgi role.cgi html.cgi bid.cgi ibid.cgi

.PHONY: clean build install

install: $(MODULES)
	sudo cp -f *.cgi /var/www/seaport/

$(MODULES): %.cgi: %.o $(COMMON)
	clang -o $@ $^ -lpq

$(OBJECTS): %.o: %.c $(HEADERS)
	clang -c -o $@ $<

clean:
	rm -rf *.cgi *.o

