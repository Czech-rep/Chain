output: main.o chain.o testing.o
	g++ main.o chain.o testing.o -o output


main.o: main.cpp testing.h chain.h
	g++ -c main.cpp

testing.o: testing.h chain.h	
	g++ -c testing.cpp

clean:
	rm *.o output