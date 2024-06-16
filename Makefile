CC = gcc
CFLAGS = -Isrc -Wall -Wextra -Werror -Wshadow
LDFLAGS = -lcunit

# Source files and object files
SRCS = $(wildcard src/*.c)
OBJS = $(patsubst src/%.c, build/%.o, $(SRCS))
TARGET = project_codewars

# Test files and object files
TEST_SRCS = $(wildcard tests/*.c)
TEST_OBJS = $(patsubst tests/%.c, build/%.o, $(TEST_SRCS))
TEST_TARGET = test_project_codewars

.PHONY: all clean test

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CC) -o $(TARGET) $(filter-out build/project_codewars.o, $(OBJS))

build/%.o: src/%.c
	$(CC) $(CFLAGS) -c $< -o $@

build/%.o: tests/%.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f build/*.o $(TARGET) $(TEST_TARGET) CUnitAutomated-Results.xml CUnit-Results.xml

test: $(TEST_TARGET)
	./$(TEST_TARGET)

$(TEST_TARGET): $(TEST_OBJS) $(filter-out build/main.o, $(OBJS))
	$(CC) -o $(TEST_TARGET) $(TEST_OBJS) $(filter-out build/main.o, $(OBJS)) $(LDFLAGS)
