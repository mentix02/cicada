CC := cc
CFLAGS := -std=c11 -Wall -pedantic -g -O0
INCLUDES := -I../src -Iacutest -I../src/utils
OBJECTS := build/tests.o build/utils.o build/list.o build/vector.o build/list_test.o build/vector_test.o

all: $(OBJECTS)
	$(CC) $(CFLAGS) $(OBJECTS) -o tests

build/%.o: %.c
	$(CC) $(CFLAGS) $(INCLUDES) -c $? -o $@

build/%.o: ../src/**/%.c
	$(CC) $(CFLAGS) $(INCS) -c $? -o $@

clean:
	rm -rf tests build/*.o build/*.dSYM
