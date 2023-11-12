# Ensure bash is used
SHELL := bash
# Ensures 100% stopping if step in recipe fails
.SHELLFLAGS := -eu -o pipefail -c

# If a rule fails, its target file is deleted
.DELETE_ON_ERROR:

# Warning if using undefined make variables
MAKEFLAGS += --warn-undefined-variables
# Disables builtin rules (C...)
MAKEFLAGS += --no-builtin-rules




# Targets which are not supposed to generate
# a file with the same name
.PHONY: docs

idir := include
sdir := src
odir := obj
bdir := build
tdir := tests

headers := $(wildcard $(idir)/*.hpp)
sources := $(wildcard $(sdir)/*.cpp)
objects := $(patsubst $(sdir)/%.cpp, $(odir)/%.o, $(sources))
lib := $(bdir)/libbyp-cpp.a

theaders := $(wildcard $(tdir)/*.hpp)
tsources := $(wildcard $(tdir)/*.cpp)
tobjects := $(patsubst $(tdir)/%.cpp, $(bdir)/%, $(tsources))

CC := g++
CXXFLAGS := -std=c++17 -O3 -Wfatal-errors\
						-Wall -Werror -Wextra -Wshadow -Wparentheses\
						-Wconversion -Wpedantic -pedantic
INC := -I$(idir)
LIB := -L$(bdir) -lbyp-cpp




test: $(tobjects)
	@echo ''
	@echo 'Beginning testing'
	@echo ''
	cd $(bdir); ./01.test-basic
	cd $(bdir); ./02.test-parsing
	cd $(bdir); ./03.test-simple_types
	cd $(bdir); ./04.test-errors
	cd $(bdir); ./05.test-vectors
	cd $(bdir); ./06.test-table
	cd $(bdir); ./07.test-format
	cd $(bdir); ./08.test-logger
	@echo 'All tests completed successfully'


# Rule to build test object files
$(tobjects): $(bdir)/%: $(tdir)/%.cpp $(theaders) $(lib)
	$(CC) $(CXXFLAGS) $(INC) $< -o $@ $(LIB)


# Target, which executes the rule to build the library
build: $(lib)


# Rule to build the library
$(lib): $(objects)
	@mkdir -p $(bdir)
	rm -fv $(bdir)/*.a
	ar rcs $(bdir)/libbyp-cpp.a $(objects)


# Rule to build library object files
$(objects): $(odir)/%.o: $(sdir)/%.cpp $(headers)
	@mkdir -p $(odir)
	$(CC) $(CXXFLAGS) $(INC) -c $< -o $@


docs:
	rm -rf html/
	doxygen doxygen.cnf


clean:
	rm -rf build/ html/ obj/
