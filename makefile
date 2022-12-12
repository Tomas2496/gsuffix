CC = g++
CFLAGS = -std=c++20

output: main.o gsuffix.o reader.o
	$(CC) $(CFLAGS) main.o gsuffix.o reader.o -o output

main.o: main.cpp
	$(CC) $(CFLAGS) -c main.cpp

gsuffix.o: gsuffix.hpp gsuffix.cpp
	$(CC) $(CFLAGS) -c gsuffix.cpp

reader.o: reader.hpp reader.cpp
	$(CC) $(CFLAGS) -c reader.cpp

clean:
	rm *.o output