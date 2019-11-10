CC=g++ -g -Wall -fno-builtin

# List of source files for your pager
HAPPY_SOURCES=happy.cpp

# Generate the names of the pager's object files
HAPPY_OBJS=${HAPPY_SOURCES:.cpp=.o}

all: happy

# Compile happy
happy: ${HAPPY_OBJS}
	${CC} -o $@ $^

# Generic rules for compiling a source file to an object file
%.o: %.cpp
	${CC} -c $<
%.o: %.cc
	${CC} -c $<

clean:
	rm -f ${HAPPY_OBJS} happy
