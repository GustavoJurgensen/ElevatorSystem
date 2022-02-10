#include "pessoa.h"
#include <thread>

int main(){

    Elevador elevador = Elevador(5);

    Pessoa *p1 = new Pessoa(2,3);
    std::thread th_p1 = p1->thread_pessoa(elevador);

    th_p1.join();

    return 0;
}
