# Group 4
# Sam Millikan <smillikan@scu.edu>
# Ameen Ahmed <aahmed5@scu.edu>
# Samuel Reiter <sreiter@scu.edu>
# Isaac Amedie <iamedie@scu.edu>

CXX = c++
OPT = -g
STD = -std=c++20
CXXFLAGS = $(OPT) $(STD)

# Compile .cxx files into .o
%.o: %.cxx
	$(CXX) -c $(CXXFLAGS) $<

# Only .cxx files are compiled
SRCS = bagtest.cxx person.cxx
OBJS = $(SRCS:.cxx=.o)

# Default target
all: bag

# Link executable
bag: $(OBJS)
	$(CXX) -o $@ $(CXXFLAGS) $(OBJS)

# Clean build artifacts
clean:
	/bin/rm -f bag $(OBJS)
	/bin/rm -rf $(ALL:=.dSYM)

# Dependencies
person.o: person.cxx person.h
bagtest.o: bagtest.cxx bag.h person.h
