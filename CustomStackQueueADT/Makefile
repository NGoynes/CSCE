output.out: Driver.o Node221.o List221.o Stack221.o Queue221.o
	g++ -Wall -std=c++11 -o output Driver.o Node221.o List221.o Stack221.o Queue221.o

Driver.o: Driver.cpp Stack221.h Queue221.h
	g++ -Wall -std=c++11 -c Driver.cpp

Stack221.o: Stack221.cpp Stack221.h Queue221.h List221.h
	g++ -Wall -std=c++11 -c Stack221.cpp

Queue221.o: Queue221.cpp Queue221.h Stack221.h List221.h
	g++ -Wall -std=c++11 -c Queue221.cpp

List221.o: List221.cpp List221.h Node221.h
	g++ -Wall -std=c++11 -c List221.cpp

clean:
	rm -rf *.o
	rm -f *.out
	rm -f *~ *.h.gch *#

run:
	./output
