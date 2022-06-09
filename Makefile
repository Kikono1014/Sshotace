.PHONY = all run install

CC = g++
CFLAGS=
BUILDDIR = build
SRCDIR   = .
SRC = $(shell find $(SRCDIR) -iname '*.cpp')
OBJ = $(patsubst $(SRCDIR)/%.cpp, $(BUILDDIR)/%.o, $(SRC))
LIBS=-lSDL2 -lSDL2_image -lSDL2_mixer -lSDL2_ttf
TARGET=$(BUILDDIR)/main

$(BUILDDIR)/%.o: %.cpp
	mkdir -p `dirname $@`
	$(CC) $(CFLAGS) $(LIBS) -c -o $@ $^

all: $(OBJ)
	$(CC) $(CFLAGS) $(LIBS) $(OBJ) -o ./$(TARGET)

run: all
	./$(TARGET)

install: all
	cp ./$(TARGET) /usr/local/bin

clean:
	rm -rf $(BUILDDIR)

debug:
	make all CFLAGS+=-g
	gdb ./$(TARGET)