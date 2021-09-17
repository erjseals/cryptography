CPP_SRCS := $(wildcard *.cpp) 
OBJ_SRCS := $(CPP_SRCS:.cpp=.o)

all: exploit 

# $@ matches the target; $< matches the first dependent
exploit: $(OBJ_SRCS) 
	g++ -Wall -g -o $@ $(OBJ_SRCS)

%.o: %.cpp
	g++ -g -Wall -c -o $@ $<

clean:
	rm exploit *.o




