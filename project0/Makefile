proj0.out: Driver.o Continent.o Country.o
	g++ -Wall -std=c++11 -o proj0 Driver.o Continent.o Country.o

Driver.o: Driver.cpp Continent.h Country.h
	g++ -Wall -std=c++11 -c Driver.cpp

Continent.o: Continent.cpp Continent.h Country.h
	g++ -Wall -std=c++11 -c Continent.cpp

Country.o: Country.cpp Country.h
	g++ -Wall -std=c++11 -c Country.cpp

clean:
	rm -rf *.o
	rm -f *.out
	rm -f *~ *.h.gch *#

run:
	./proj0
