PLATFORM = $(shell uname)
CXX = g++

# Flags:
#	 -O0 = reduce compilation time and make debugging produce the expected
#	 results (default, see man g++)
#	 -g = does not affect code generation, only the symbol table and debug
#	 metadata are changed (from stackoverflow)
#	 -Wall = turns on all optional warnings
#	 -Wextra = enables some extra warning flags that are not enabled by -Wall
#	 -Wshadow = warn whenever a local variable or type declaration shadows
#	 another (warns if a local var shadows an explicit typedef, but not if it
#	 shadows a struct/class/enum)
#	 -Weffc++ = warn about violations of the style guidelines from Scott
#	 Meyers' Effective C++ series of books

#CXXFLAGS = -O0 -g -std=c++11 -Wall -Wextra -Wshadow -pedantic -Werror -Weffc++
CXXFLAGS = -O0 -g -std=c++11 -Wall -Wextra -Wshadow -pedantic -Werror
LIBS = -lfltk -lfltk_images
#LIBS = -lfltk `fltk-config --cxxflags --ldflags --use-gl --use-images`

SOURCES := main.cpp Graph.cpp GUI.cpp Window.cpp Simple_window.cpp
TARGETS := main

all:
	$(CXX) $(SOURCES) $(CXXFLAGS) $(LIBS) -o $(TARGETS)

clean:
	@-rm -f $(TARGETS)

distclean: clean
	@-rm -f *~
