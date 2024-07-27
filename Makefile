# Project Paths
CURRENT_DIR := $(subst /cygdrive/c,C:,$(CURDIR))
PROJECT_NAME := $(notdir $(CURRENT_DIR))
PARENT_DIR := $(subst /$(PROJECT_NAME),,$(CURRENT_DIR))

# Project Structure
BUILD_DIR = build
COVERAGE_DIR = coverage
REPORT_DIR = report
RULE_DIR = rule
SOURCE_DIR = src
TEST_DIR = test

# Makefile Targets
TARGET := $(PROJECT_NAME)
TEST_TARGET := test_$(PROJECT_NAME)

# Main Function
MAIN_OBJ := $(BUILD_DIR)/$(PROJECT_NAME).o

# Source files and object files
SOURCE_FILES := $(wildcard $(SOURCE_DIR)/*.c)
HEADER_FILES := $(wildcard $(SOURCE_DIR)/*.h)
OBJECT_FILES := $(patsubst $(SOURCE_DIR)/%.c,$(BUILD_DIR)/%.o,$(SOURCE_FILES))

# Test files and object files
TEST_SOURCE_FILES := $(wildcard $(TEST_DIR)/*.c)
TEST_HEADER_FILES := $(wildcard $(TEST_DIR)/*.h)
TEST_OBJECT_FILES := $(patsubst $(TEST_DIR)/%.c,$(BUILD_DIR)/%.o,$(TEST_SOURCE_FILES))

# Command Line Tool Paths
GCC = "/usr/bin/gcc"
CLANG = "/usr/bin/clang"
CLANG_VERSION = 17
CLANG-FORMAT = "/usr/bin/clang-format"
CLANG-TIDY = "/usr/bin/clang-tidy"
CLANG-CHECK = "/usr/bin/clang-check"
CPPCHECK = "/usr/bin/cppcheck"
CPPCHECK_HTML_REPORT = "../cppcheck/htmlreport/cppcheck-htmlreport"
GCOV = "/usr/bin/gcov"
LLVM-PROFDATA = "/usr/bin/llvm-profdata"
LLVM-COV = "/usr/bin/llvm-cov"

# Include Paths
SYSTEM_LIBS = \
	-I"/usr/include" \
	-I"/usr/lib/clang/$(CLANG_VERSION)/include" \

INCLUDE_DIRS = \
 	-I"$(SOURCE_DIR)" \

TEST_INCLUDE_DIRS = \
	-I"$(TEST_DIR)" \

# Compiler and Linker Flags
CC := $(CLANG)
C_STD = -std=iso9899:1999 #iso9899:2011
CFLAGS = -Wall -Wextra -Werror -Wshadow -pedantic -g -O0
LDFLAGS = -lcunit

# Cppcheck Flags
CPPCHECK_MISRA := $(RULE_DIR)/misra.json
CPPCHECK_REPORT := $(REPORT_DIR)/cppcheck.report
CPPCHECK_XML := $(REPORT_DIR)/cppcheck_errors.xml
CPPCHECK_HTML := $(wildcard $(REPORT_DIR)/html/*)

CPPCHECK_FLAGS := \
	--quiet \
	--force \
	--enable=all \
	--addon=$(CPPCHECK_MISRA) \
	--checkers-report=$(CPPCHECK_REPORT) \

CPPCHECK_EXPORT = \
	--xml --xml-version=2 2> $(CPPCHECK_XML) \

CPPCHECK_SUPPRESS = \
	--inline-suppr \
	--suppress=unmatchedSuppression \
	--suppress=missingIncludeSystem \
	--suppress=preprocessorErrorDirective \
	--suppress=checkersReport \

CPPCHECK_REPORT_FLAGS := \
	--title=$(PROJECT_NAME) \
	--file=$(CPPCHECK_XML) \
	--report-dir=$(REPORT_DIR)/html \
	--source-dir=. \

CLANG-ANALYZE_FLAGS = \
	-Xanalyzer -analyzer-output=plist \
	-Xanalyzer -analyzer-output=text \

COVERAGE_FLAGS = -fprofile-instr-generate -fcoverage-mapping
COVERAGE_PROFRAW := $(COVERAGE_DIR)/default.profraw
COVERAGE_PROFDATA := $(COVERAGE_DIR)/default.profdata
COVERAGE_FILES := $(wildcard $(COVERAGE_DIR)/*)

# Reports
REPORTS := \
	$(REPORT_DIR)/CUnitAutomated-Results.xml \
	$(REPORT_DIR)/CUnitAutomated-Listing.xml \
	$(CPPCHECK_XML) \
	$(CPPCHECK_REPORT) \
	$(CPPCHECK_HTML) \

.PHONY: all clean test style tidy cppcheck report check analyze coverage show-%

all: $(TARGET)

$(TARGET): $(OBJECT_FILES)
	$(CC) -o $(TARGET) $(OBJECT_FILES) $(COVERAGE_FLAGS)

$(BUILD_DIR)/%.o: $(SOURCE_DIR)/%.c
	$(CC) $(INCLUDE_DIRS) $(CFLAGS) $(C_STD) $(COVERAGE_FLAGS) -c $< -o $@

$(TEST_TARGET): $(TEST_OBJECT_FILES) $(OBJECT_FILES)
	$(CC) -o $(TEST_TARGET) $(TEST_OBJECT_FILES) $(filter-out $(MAIN_OBJ),$(OBJECT_FILES)) $(LDFLAGS) $(COVERAGE_FLAGS)

$(BUILD_DIR)/%.o: $(TEST_DIR)/%.c
	$(CC) $(INCLUDE_DIRS) $(TEST_INCLUDE_DIRS) $(CFLAGS) $(C_STD) $(COVERAGE_FLAGS) -c $< -o $@

clean:
	rm -rf $(TARGET) $(TEST_TARGET) $(OBJECT_FILES) $(TEST_OBJECT_FILES) $(REPORTS) $(COVERAGE_FILES)

test: $(TEST_TARGET)
	LLVM_PROFILE_FILE="$(COVERAGE_PROFRAW)" ./$(TEST_TARGET)

style: $(SOURCE_FILES) $(HEADER_FILES) $(TEST_SOURCE_FILES) $(TEST_HEADER_FILES)
	@echo "style has started..."
	$(CLANG-FORMAT) -i -style=file $^
	@echo "completed."

tidy: $(SOURCE_FILES) $(TEST_SOURCE_FILES)
	@echo "clang-tidy has started..."
	$(CLANG-TIDY) -extra-arg=$(C_STD) $^ -- $(INCLUDE_DIRS) $(TEST_INCLUDE_DIRS)
	@echo "completed."

$(CPPCHECK_REPORT): $(SOURCE_FILES) $(TEST_SOURCE_FILES)
	@echo "cppcheck has started..."
	$(CPPCHECK) $(CPPCHECK_FLAGS) $(CPPCHECK_SUPPRESS) $(INCLUDE_DIRS) $(TEST_INCLUDE_DIRS) $^
	@echo "report generated: $(CPPCHECK_REPORT)."
	@echo "completed."

$(CPPCHECK_XML): $(SOURCE_FILES) $(TEST_SOURCE_FILES)
	@echo "cppcheck has started..."
	$(CPPCHECK) $(CPPCHECK_FLAGS) $(CPPCHECK_EXPORT) $(CPPCHECK_SUPPRESS) $(INCLUDE_DIRS) $(TEST_INCLUDE_DIRS) $^
	@echo "report generated: $(CPPCHECK_REPORT)."
	@echo "results written: $(CPPCHECK_XML)."
	@echo "completed."

cppcheck: $(CPPCHECK_REPORT)

report: $(CPPCHECK_XML)
	@echo "cppcheck-htmlreport has started..."
	$(CPPCHECK_HTML_REPORT) $(CPPCHECK_REPORT_FLAGS)
	@echo "completed."

check:
	@for src in $(SOURCE_FILES) $(TEST_SOURCE_FILES) ; do \
		echo "clang-check: $$src" ; \
		$(CLANG-CHECK) $$src -- -c $(CFLAGS) $(INCLUDE_DIRS) $(TEST_INCLUDE_DIRS) ; \
	done
	@echo "completed."

analyze:
	@for src in $(SOURCE_FILES) $(TEST_SOURCE_FILES) ; do \
		echo "clang --analyze: $$src" ; \
		$(CLANG) --analyze $(CFLAGS) $(INCLUDE_DIRS) $(TEST_INCLUDE_DIRS) "$$src" $(CLANG-ANALYZE_FLAGS) ; \
	done
	@echo "completed."

coverage: $(TEST_TARGET)
	@echo "running tests for coverage..."
	LLVM_PROFILE_FILE="$(COVERAGE_PROFRAW)" ./$(TEST_TARGET)
	@echo "generating coverage report..."
	$(LLVM-PROFDATA) merge -sparse $(COVERAGE_PROFRAW) -o $(COVERAGE_PROFDATA)
	$(LLVM-COV) show ./$(TEST_TARGET) -instr-profile=$(COVERAGE_PROFDATA) -path-equivalence=$(BUILD_DIR),$(SOURCE_DIR) -output-dir=$(COVERAGE_DIR) -format=html
	@echo "coverage report generated in $(COVERAGE_DIR)."

show-%:
	@echo $* = $($*)
