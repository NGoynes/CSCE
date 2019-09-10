driver.out: Driver.o TicTacTrie.o TicTacToe.o TicTacNode.o
	g++ -Wall -std=c++11 -o driver Driver.o TicTacNode.o TicTacToe.o TicTacTrie.o

Driver.o: Driver.cpp TicTacTrie.h TicTacToe.h
	g++ -Wall -std=c++11 -c Driver.cpp

TicTacTrie.o: TicTacTrie.cpp TicTacTrie.h TicTacToe.h TicTacNode.h
	g++ -Wall -std=c++11 -c TicTacTrie.cpp

TicTacToe.o: TicTacToe.cpp TicTacToe.h TicTacNode.h
	g++ -Wall -std=c++11 -c TicTacToe.cpp

TicTacNode.o: TicTacNode.cpp TicTacNode.h
	g++ -Wall -std=c++11 -c TicTacNode.cpp

clean:
	rm -rf *.o
	rm -f *.out
	rm -f *~ *.h.gch *#

run:
	./driver $(FILE)
