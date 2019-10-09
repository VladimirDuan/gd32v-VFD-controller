
all: main

CC=gcc
COBJS=hid.o main.o os_related.o 
OBJS=$(COBJS)
CFLAGS=-I. -g -c
LDFLAGS = -mwindows -lsetupapi -lpsapi

$(COBJS): %.o: %.c
	$(CC) $(CFLAGS) $< -o $@
	
main: $(OBJS)
	g++ -g $^ $(LDFLAGS) -o vfd_display

clean:
	rm *.o vfd_display.exe

.PHONY: clean
