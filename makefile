output: main.o chain.h testing.o
	g++ main.o testing.o -o output


main.o: main.cpp testing.h chain.h
	g++ -c main.cpp

testing.o: testing.h chain.h	
	g++ -c testing.cpp

clean:
	rm *.o output
