.PHONY: build

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
	g++ $(CPPFLAGS) $(CPPWARNINGS) $(CPPINCLUDES) -c src/bcp_loader.cpp -o $(BUILDDIR)/bcp_loader.o
	g++ $(CPPFLAGS) $(CPPWARNINGS) $(CPPINCLUDES) -c src/get.cpp -o $(BUILDDIR)/get.o
	g++ $(CPPFLAGS) $(CPPWARNINGS) $(CPPINCLUDES) -c src/convert.cpp -o $(BUILDDIR)/convert.o
	g++ $(CPPFLAGS) $(CPPWARNINGS) $(CPPINCLUDES) -c src/read.cpp -o $(BUILDDIR)/read.o
	ar rcs $(BUILDDIR)/libbcp.a\
		$(BUILDDIR)/bcp_loader.o\
		$(BUILDDIR)/get.o\
		$(BUILDDIR)/convert.o\
		$(BUILDDIR)/read.o

test: build
	g++ $(CPPFLAGS) $(CPPWARNINGS) $(CPPINCLUDES) $(CPPLIB)\
		tests/01.test-basic.cpp -o $(BUILDDIR)/01.test-basic -lbcp
	g++ $(CPPFLAGS) $(CPPWARNINGS) $(CPPINCLUDES) $(CPPLIB)\
		tests/02.test-parsing.cpp -o $(BUILDDIR)/02.test-parsing -lbcp
	g++ $(CPPFLAGS) $(CPPWARNINGS) $(CPPINCLUDES) $(CPPLIB)\
		tests/03.test-simple_types.cpp -o $(BUILDDIR)/03.test-simple_types -lbcp
	g++ $(CPPFLAGS) $(CPPWARNINGS) $(CPPINCLUDES) $(CPPLIB)\
		tests/04.test-errors.cpp -o $(BUILDDIR)/04.test-errors -lbcp
	cd $(BUILDDIR)/ ; ./01.test-basic
	cd $(BUILDDIR)/ ; ./02.test-parsing
	cd $(BUILDDIR)/ ; ./03.test-simple_types
	cd $(BUILDDIR)/ ; ./04.test-errors

docs:
	rm -rf html/
	doxygen doxygen.cnf
