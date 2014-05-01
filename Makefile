# ------------------------------------------------
# Generic Makefile
#
# Original author: yanick.rochon@gmail.com
# Date  : 2011-08-10
#
# Changelog :
#   2010-11-05 - first version
#   2011-08-10 - added structure : sources, objects, binaries
#                thanks to http://stackoverflow.com/users/128940/beta
# ------------------------------------------------

# project name (generate executable with this name)
TARGET   = Digger

CC       = gcc
# compiling flags here
CFLAGS   = -Wall `sdl-config --cflags`

LINKER   = gcc -o
# linking flags here
LFLAGS   = -Wall -I. -lm `sdl-config --libs`

# change these to set the proper directories where each files should be
SRCDIR   = src
HDRDIR   = include
OBJDIR   = obj
BINDIR   = bin

SOURCES  := $(wildcard $(SRCDIR)/*.c)
INCLUDES := $(wildcard $(HDRDIR)/*.h)
OBJECTS  := $(SOURCES:$(SRCDIR)/%.c=$(OBJDIR)/%.o)

all: $(BINDIR)/$(TARGET)

$(BINDIR)/$(TARGET): $(OBJECTS)
	@$(LINKER) $@ $(LFLAGS) $(OBJECTS)
	@echo "Linking complete!"

$(OBJECTS): $(OBJDIR)/%.o : $(SRCDIR)/%.c
	@$(CC) $(CFLAGS) -c $< -o $@
	@echo "Compiled "$<" successfully!"

.PHONY: clean
clean:
	@rm -f $(OBJECTS)
	@echo "Cleanup complete!"

.PHONY: remove
remove: clean
	@rm -f $(BINDIR)/$(TARGET)
	@echo "Executable removed!"
