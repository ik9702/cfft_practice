CC = gcc
LD = gcc

INCDIR = ../inc
SRCDIR1 = ../src
SRCDIR2 = 

VPATH = $(SRCDIR1) $(SRCDIR2) ..

CFLAGS = -O2 -I$(INCDIR)
LIBS = -lm

TARGET = modeltest.exe

SRCS = $(foreach dir, .. $(SRCDIR1) $(SRCDIR2), $(wildcard $(dir)/*.c))
SRCS := $(notdir $(SRCS))

OBJS = $(SRCS:.c=.o)

all: $(TARGET)

$(TARGET) : $(OBJS)
	$(LD) $^ -o$(TARGET) $(LIBS)
	mv $(TARGET) ../


%o:%c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	-rm -rf $(OBJS)
	-rm -f ../$(TARGET)

depend: $(SRCS)
	$(CC) -M $(CFLAGS) $^ > $@

-include depend