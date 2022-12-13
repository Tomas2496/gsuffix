CC = g++
CFLAGS = -std=c++20

output: main.o reader.o
	$(CC) $(CFLAGS) main.o reader.o -o output

main.o: main.cpp
	$(CC) $(CFLAGS) -c main.cpp

reader.o: reader.hpp reader.cpp
	$(CC) $(CFLAGS) -c reader.cpp

clean:
	rm *.o output