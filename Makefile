output: main.o pessoa.o elevador.o
	g++ -std=c++11 -pthread main.o pessoa.o elevador.o -o output

main.o: main.cpp
	g++ -c main.cpp

pessoa.o: pessoa.cpp pessoa.h
	g++ -c pessoa.cpp

elevador.o: elevador.cpp elevador.h
	g++ -c elevador.cpp

clean:
	rm *.o output