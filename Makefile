SOURCES = $(shell find . -type f -name '*.c')
HEADERS = $(shell find . -type f -name '*.h')
OBJECTS = $(SOURCES:.c=.o)

EXE_NAME = emdebbed
CLEAN_TARGETS = $(OBJECTS) $(EXE_NAME)

.PHONY: all clean

all: $(OBJECTS) $(HEADERS)
	gcc $(OBJECTS) -o $(EXE_NAME)

all-exe: all
	rm -rf $(OBJECTS)

clean:
	rm -rf $(CLEAN_TARGETS)

%.o: %.c
	gcc -c $< -o $@