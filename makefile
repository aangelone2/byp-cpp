BUILDDIR=build

CPPFLAGS=-std=c++17 -O3 -Wfatal-errors
CPPWARNINGS=-Wall -Werror -Wextra -Wshadow -Wparentheses -Wpedantic -Wconversion -pedantic

CPPINCLUDES=-Iinclude/
CPPLIB=-L$(BUILDDIR)/

# preferred static library for portability concerns
# (dynamic libraries required fixing of LD_LIBRARY_PATH)
cpp:
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

test-cpp: cpp
	g++ $(CPPFLAGS) $(CPPWARNINGS) $(CPPINCLUDES) $(CPPLIB) tests/test-01.cpp -o $(BUILDDIR)/test-01 -lbcp
	cd $(BUILDDIR)/ ; ./test-01
