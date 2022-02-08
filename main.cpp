#include "elevador.h"
#include "pessoa.h"
#include <thread>

int main(){

    Elevador elevador = new Elevador(5)

    Pessoa p1 = new Pessoa(2,3);
    std::thread th_p1(p1.controla_pessoa,elevador);
    // Pessoa p2 = new Pessoa(1,4);
    // std::thread th_p2(p2.controla_pessoa,elevador);

    th_p1.join();
    // th_p2.join();

    return 0;
}