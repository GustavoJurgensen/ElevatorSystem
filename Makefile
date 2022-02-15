COMPILADOR = g++
FLAGS = -Wall -std=c++11 -pthread
FLAGS_GUI = -lsfml-graphics -lsfml-window -lsfml-system
NOME_EXECUTAVEL = aplication


all: main.o pessoa.o elevador.o elevator_GUI.o
	$(COMPILADOR) main.o pessoa.o elevador.o elevator_GUI.o -o $(NOME_EXECUTAVEL) $(FLAGS) $(FLAGS_GUI)

valgrind:all
	sudo valgrind --leak-check=full --show-leak-kinds=all ./$(NOME_EXECUTAVEL)

run:all
	./$(NOME_EXECUTAVEL)

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
	rm $(NOME_EXECUTAVEL)