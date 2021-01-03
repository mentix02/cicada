CC       = cc
INCS     = -I..
CFLAGS   = -std=c11 -Wall -pedantic -g
OBJFILES = build/tests.o build/sort.o build/vector.o build/random.o build/array.o build/utils.o build/list.o build/test_utils.o build/test_vector.o build/test_list.o build/test_array.o build/test_sort.o

tests: $(OBJFILES)
	$(CC) $(CFLAGS) $(OBJFILES) -o tests

build/%.o: %.c
	$(CC) $(CFLAGS) $(INCS) -c $? -o $@

build/%.o: ../a/%.c
	$(CC) $(CFLAGS) $(INCS) -c $? -o $@

build/%.o: ../ds/%.c
	$(CC) $(CFLAGS) $(INCS) -c $? -o $@

test: tests
	@./tests -v

clean:
	rm -rf tests build/*.o build/*.dSYM
