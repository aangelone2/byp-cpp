BUILDDIR=build

CPPFLAGS=-std=c++17 -O3 -Wfatal-errors
CPPWARNINGS=-Wall -Werror -Wextra -Wshadow -Wparentheses -Wpedantic -Wconversion -pedantic
CPPINCLUDES=-Iinclude/

release:
	mkdir -p $(BUILDDIR)
	g++ $(CPPFLAGS) $(CPPWARNINGS) $(CPPINCLUDES) -c src/bcp.cpp -o $(BUILDDIR)/bcp.o
	ar rcs $(BUILDDIR)/bcp.a $(BUILDDIR)/bcp.o

debug:
	mkdir -p $(BUILDDIR)
	g++ $(CPPFLAGS) $(CPPWARNINGS) $(CPPINCLUDES) -DDEBUG -c src/bcp.cpp -o $(BUILDDIR)/bcp.o
	ar rcs $(BUILDDIR)/bcp.a $(BUILDDIR)/bcp.o
