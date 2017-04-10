TARGET = t
CFLAGS = -Wall -Wextra -pedantic -std=c99

.PHONY: default all clean

default: $(TARGET)
all: default

SRCDIR = src/
BUILDDIR = bin/

OBJECTS = $(patsubst $(SRCDIR)%.c, $(BUILDDIR)%.o, $(wildcard $(SRCDIR)*.c))
HEADERS = $(wildcard *.h)

$(BUILDDIR)%.o: $(SRCDIR)%.c $(HEADERS)
	@mkdir -p $(BUILDDIR)
	$(CC) $(CFLAGS) -c $< -o $@

.PRECIOUS: $(TARGET) $(OBJECTS)

$(TARGET): $(OBJECTS)
	$(CC) $(OBJECTS) -Wall $(LIBS) -o $(BUILDDIR)$@

clean:
	-rm -f $(BUILDDIR)*.o
	-rm -f $(BUILDDIR)$(TARGET)
