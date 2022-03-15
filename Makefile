COMPILADOR = g++
FLAGS = -Wall -std=c++11 -pthread
FLAGS_GUI = -lsfml-graphics -lsfml-window -lsfml-system
FLAGS_TEST = -lgtest -lgtest_main
NOME_EXECUTAVEL = aplication
NOME_TEST = testeAplication


all: main.o pessoa.o elevador.o elevator_GUI.o
	$(COMPILADOR) main.o pessoa.o elevador.o elevator_GUI.o -o $(NOME_EXECUTAVEL) $(FLAGS) $(FLAGS_GUI)

test: mainTest.o elevatorTest.o pessoa.o elevador.o
	$(COMPILADOR) mainTest.o elevatorTest.o pessoa.o elevador.o -o $(NOME_TEST) $(FLAGS) $(FLAGS_TEST)

valgrind:all
	sudo valgrind --leak-check=full --show-leak-kinds=all ./$(NOME_EXECUTAVEL)

runTest:test
	./$(NOME_TEST)

run:all
	./$(NOME_EXECUTAVEL)

elevatorTest.o: elevatorTest.cpp
	$(COMPILADOR) -c elevatorTest.cpp

mainTest.o: mainTest.cpp
	$(COMPILADOR) -c mainTest.cpp

main.o: main.cpp
	$(COMPILADOR) -c main.cpp 

pessoa.o: pessoa.cpp pessoa.h
	$(COMPILADOR) -c pessoa.cpp

elevador.o: elevador.cpp elevador.h
	$(COMPILADOR) -c elevador.cpp

elevator_GUI.o: elevator_GUI.cpp elevator_GUI.h
	$(COMPILADOR) -c elevator_GUI.cpp

clean:
	rm *.o

clean_bin:
	rm *.out $(NOME_EXECUTAVEL) $(NOME_TEST)

clean_all:
	rm *.o *.out $(NOME_EXECUTAVEL) $(NOME_TEST)