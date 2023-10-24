.PHONY: build docs

BUILDDIR=build

CC=g++
CPPFLAGS=-std=c++17 -O3 -Wfatal-errors\
				 -Wall -Werror -Wextra -Wshadow -Wparentheses -Wpedantic -Wconversion -pedantic

LIBINC=-Iinclude/
TESTINC=$(LIBINC) -Itests/
CPPLIB=-L$(BUILDDIR)/

# preferred static library for portability concerns
# (dynamic libraries required fixing of LD_LIBRARY_PATH)
build:
	mkdir -p $(BUILDDIR)
	rm -fv $(BUILDDIR)/*.a $(BUILDDIR)/*.o
	$(CC) $(CPPFLAGS) $(LIBINC) -c src/common.cpp -o $(BUILDDIR)/common.o
	$(CC) $(CPPFLAGS) $(LIBINC) -c src/convert.cpp -o $(BUILDDIR)/convert.o
	$(CC) $(CPPFLAGS) $(LIBINC) -c src/parser.cpp -o $(BUILDDIR)/parser.o
	ar rcs $(BUILDDIR)/libbyp-cpp.a\
		$(BUILDDIR)/common.o\
		$(BUILDDIR)/convert.o\
		$(BUILDDIR)/parser.o

test: build
	$(CC) $(CPPFLAGS) $(TESTINC) $(CPPLIB) tests/01.test-basic.cpp -o $(BUILDDIR)/01.test-basic -lbyp-cpp
	$(CC) $(CPPFLAGS) $(TESTINC) $(CPPLIB) tests/02.test-parsing.cpp -o $(BUILDDIR)/02.test-parsing -lbyp-cpp
	$(CC) $(CPPFLAGS) $(TESTINC) $(CPPLIB) tests/03.test-simple_types.cpp -o $(BUILDDIR)/03.test-simple_types -lbyp-cpp
	$(CC) $(CPPFLAGS) $(TESTINC) $(CPPLIB) tests/04.test-errors.cpp -o $(BUILDDIR)/04.test-errors -lbyp-cpp
	$(CC) $(CPPFLAGS) $(TESTINC) $(CPPLIB) tests/05.test-vectors.cpp -o $(BUILDDIR)/05.test-vectors -lbyp-cpp
	$(CC) $(CPPFLAGS) $(TESTINC) $(CPPLIB) tests/06.test-table.cpp -o $(BUILDDIR)/06.test-table -lbyp-cpp
	@echo ''
	@echo 'Beginning testing'
	@echo ''
	cd $(BUILDDIR)/ ; ./01.test-basic
	@echo ''
	cd $(BUILDDIR)/ ; ./02.test-parsing
	@echo ''
	cd $(BUILDDIR)/ ; ./03.test-simple_types
	@echo ''
	cd $(BUILDDIR)/ ; ./04.test-errors
	@echo ''
	cd $(BUILDDIR)/ ; ./05.test-vectors
	@echo ''
	cd $(BUILDDIR)/ ; ./06.test-table
	@echo ''
	@echo 'All tests completed successfully'

docs:
	rm -rf html/
	doxygen doxygen.cnf
