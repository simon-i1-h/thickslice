# BSD Make

.PHONY: clean test valgrind

TEST := thickslice-test
OBJS := hashmap.o json.o lex.o parse.o util.o vector.o
TEST_OJBS := test.o
CFLAGS := -pedantic -g -O -Wall -Wextra

$(TEST): $(OBJS) $(TEST_OJBS)
	$(CC) $(CFLAGS) -o $(TEST) $(OBJS) $(TEST_OJBS)

clean:
	rm -f ./$(TEST) ./*.o

test: $(TEST)
	./$(TEST)

valgrind: $(TEST)
	valgrind --leak-check=full ./$(TEST)
