CC=gcc
CCOPTS=--std=gnu99 -Wall
AR=ar
HEADERS=read_from_files.h

OBJS=read_from_files.o

LIBS=libRefresh.a

BINS=refresh

#disastros_test

.phony: clean all


all:	$(LIBS) $(BINS)

%.o:	%.c $(HEADERS)
	$(CC) $(CCOPTS) -c -o $@  $<

libRefresh.a: $(OBJS) 
	$(AR) -rcs $@ $^
	$(RM) $(OBJS)

refresh: refresh.c $(LIBS)
	$(CC) $(CCOPTS) -o $@ $^

clean:
	rm -rf *.o *~ $(LIBS) $(BINS)