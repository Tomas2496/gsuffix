CXX ?= g++
CXXFLAGS = -std=c++20 -O3

all : gsuffix 

gsuffix: main.o reader.o
	$(CXX) $(CXXFLAGS) main.o reader.o -o gsuffix.out

.PHONY: clean
clean:
	rm -f *.o gsuffix.out