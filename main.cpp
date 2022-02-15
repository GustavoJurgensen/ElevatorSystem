#include "pessoa.h"
#include "elevador.h"
#include "elevator_GUI.h"
#include <iostream>
#include <random>

int main(){

    // std::random_device rd; // obtain a random number from hardware
    // std::mt19937 gen(rd()); // seed the generator
    // std::uniform_int_distribution<> distr(25, 63); // define the range

    // for(int n=0; n<40; ++n)
    //     std::cout << distr(gen) << ' ';
    
    // int aux;
    // std::cin >> aux;

    std::cout << std::endl << "#------------------- ELEVATOR SETTINGS -------------------#" << std::endl;
    std::cout << "WARNING: GUI only works properly with 4 floor elevators" << std::endl;
    
    std::string selection;
    std::cout << "Activate graphic user interface [y/n]: ";
    std::cin >> selection;
    
    while(selection != "y" && selection != "n"){
        std::cout << "Invalid input. Answer must be [y/n]" << std::endl;
        std::cout << "Activate graphic user interface [y/n]: ";
        std::cin >> selection;
    }
    
    int n_floors;
    std::cout << "Number of floors [int > 1]: ";
    std::cin >> n_floors;
    
    if(std::cin.fail() || n_floors < 2){
        do{
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(),'\n');
            std::cout << "Invalid input. Answer must be [int > 1]" << std::endl;
            std::cout << "Number of floors [int > 1]: ";
            std::cin >> n_floors;
        }while(std::cin.fail() || n_floors < 2);
    }

    std::cout << "#---------------------------------------------------------#\n" << std::endl;

    Elevador elevador(n_floors);

    //Exemplo Predefinido GUI
    if(selection == "y"){
        Pessoa *pessoa1 = new Pessoa(1,4,2,&elevador);
        Pessoa *pessoa2 = new Pessoa(2,2,4,&elevador);
        Pessoa *pessoa3 = new Pessoa(3,1,4,&elevador);

        Elevator_GUI janela(pessoa1,pessoa2,pessoa3,&elevador);

        elevador.join();
        pessoa1->join();
        pessoa2->join();
        pessoa3->join();
        
        delete pessoa1;
        delete pessoa2;
        delete pessoa3;
    
    }else{
        std::random_device rd; // obtain a random number from hardware
        std::mt19937 gen(rd()); // seed the generator
        std::uniform_int_distribution<> distr(0, 100000); // define the range

        int id = 0;
        while(1){
            if(distr(gen)%100 < 5){
                id++;

                int andar_atual = distr(gen)%n_floors + 1;
                int andar_destino = distr(gen)%n_floors + 1;

                while(andar_atual == andar_destino){
                    andar_destino = distr(gen)%n_floors + 1;
                } 

                Pessoa *pessoa = new Pessoa(id,andar_atual,andar_destino,&elevador);
                pessoa->detach();
            }
            
            std::this_thread::sleep_for(std::chrono::milliseconds(1000));
        }
    }


    return 0;
}
