LFLAGS=-lncurses -g -Wall -I. -lm
CC=gcc

#define object and source directories
ODIR=obj
SDIR=src


CFLAGS=-Wall -g -I./$(SDIR)/include

TARGET=nccolacs

#obtain source files

SRCFILES := $(wildcard $(SDIR)/*.c)
INCLUDES := $(wildcard $(SDIR)/include/*.h)
OBJ := $(SRCFILES:$(SDIR)/%.c=$(ODIR)/%.o)



all: $(TARGET)
#link objects into final executable
$(TARGET): $(OBJ)
	$(CC) -o $(TARGET) $(OBJ) $(LFLAGS)

#compile objects from src/*.o -> obj/*.o
$(OBJ): $(ODIR)/%.o : $(SDIR)/%.c
	$(CC) $(CFLAGS) -c $< -o $@
	@echo "Compiled " $<

clean:
	rm -f $(TARGET) $(OBJ)

