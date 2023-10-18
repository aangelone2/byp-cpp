BUILDDIR=build

CPPFLAGS=-std=c++17 -O3 -Wfatal-errors
CPPWARNINGS=-Wall -Werror -Wextra -Wshadow -Wparentheses -Wpedantic -Wconversion -pedantic

CPPINCLUDES=-Iinclude/
CPPLIB=-L$(BUILDDIR)/

# preferred static library for portability concerns
# (dynamic libraries required fixing of LD_LIBRARY_PATH)
cpp:
	mkdir -p $(BUILDDIR)
	g++ $(CPPFLAGS) $(CPPWARNINGS) $(CPPINCLUDES) -c src/bcp.cpp -o $(BUILDDIR)/bcp.o
	ar rcs $(BUILDDIR)/libbcp.a $(BUILDDIR)/bcp.o

test-cpp: cpp
	g++ $(CPPFLAGS) $(CPPWARNINGS) $(CPPINCLUDES) $(CPPLIB) tests/test-01.cpp -o $(BUILDDIR)/test-01 -lbcp
	cd $(BUILDDIR)/ ; ./test-01
