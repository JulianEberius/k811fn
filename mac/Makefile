all: k811fn

CC=gcc
CXX=g++
COBJS=hid.o
CPPOBJS=k811fn.o
OBJS=$(COBJS) $(CPPOBJS)
CFLAGS+=-I../include/ -Wall -g -c
LIBS=-framework IOKit -framework CoreFoundation


k811fn: $(OBJS)
	g++ -Wall -g $^ $(LIBS) -o k811fn

$(COBJS): %.o: %.c
	$(CC) $(CFLAGS) $< -o $@

$(CPPOBJS): %.o: %.cpp
	$(CXX) $(CFLAGS) $< -o $@

clean:
	rm -f *.o k811fn $(CPPOBJS)

.PHONY: clean
