.PHONY: build docs

CC=g++
BUILDDIR=build

CPPFLAGS=-std=c++17 -O3 -Wfatal-errors
CPPWARNINGS=-Wall -Werror -Wextra -Wshadow -Wparentheses -Wpedantic -Wconversion -pedantic

CPPINCLUDES=-Iinclude/
CPPLIB=-L$(BUILDDIR)/

# preferred static library for portability concerns
# (dynamic libraries required fixing of LD_LIBRARY_PATH)
build:
	mkdir -p $(BUILDDIR)
	rm -fv $(BUILDDIR)/*.a $(BUILDDIR)/*.o
	$(CC) $(CPPFLAGS) $(CPPWARNINGS) $(CPPINCLUDES) -c src/byp_loader.cpp -o $(BUILDDIR)/byp_loader.o
	$(CC) $(CPPFLAGS) $(CPPWARNINGS) $(CPPINCLUDES) -c src/get.cpp -o $(BUILDDIR)/get.o
	$(CC) $(CPPFLAGS) $(CPPWARNINGS) $(CPPINCLUDES) -c src/convert.cpp -o $(BUILDDIR)/convert.o
	$(CC) $(CPPFLAGS) $(CPPWARNINGS) $(CPPINCLUDES) -c src/read.cpp -o $(BUILDDIR)/read.o
	ar rcs $(BUILDDIR)/libbyp-cpp.a\
		$(BUILDDIR)/byp_loader.o\
		$(BUILDDIR)/get.o\
		$(BUILDDIR)/convert.o\
		$(BUILDDIR)/read.o

test: build
	$(CC) $(CPPFLAGS) $(CPPWARNINGS) $(CPPINCLUDES) $(CPPLIB) tests/01.test-basic.cpp -o $(BUILDDIR)/01.test-basic -lbyp-cpp
	$(CC) $(CPPFLAGS) $(CPPWARNINGS) $(CPPINCLUDES) $(CPPLIB) tests/02.test-parsing.cpp -o $(BUILDDIR)/02.test-parsing -lbyp-cpp
	$(CC) $(CPPFLAGS) $(CPPWARNINGS) $(CPPINCLUDES) $(CPPLIB) tests/03.test-simple_types.cpp -o $(BUILDDIR)/03.test-simple_types -lbyp-cpp
	$(CC) $(CPPFLAGS) $(CPPWARNINGS) $(CPPINCLUDES) $(CPPLIB) tests/04.test-errors.cpp -o $(BUILDDIR)/04.test-errors -lbyp-cpp
	$(CC) $(CPPFLAGS) $(CPPWARNINGS) $(CPPINCLUDES) $(CPPLIB) tests/05.test-vectors.cpp -o $(BUILDDIR)/05.test-vectors -lbyp-cpp
	cd $(BUILDDIR)/ ; ./01.test-basic
	cd $(BUILDDIR)/ ; ./02.test-parsing
	cd $(BUILDDIR)/ ; ./03.test-simple_types
	cd $(BUILDDIR)/ ; ./04.test-errors
	cd $(BUILDDIR)/ ; ./05.test-vectors

docs:
	rm -rf html/
	doxygen doxygen.cnf
