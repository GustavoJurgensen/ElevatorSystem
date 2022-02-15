#include "pessoa.h"
#include "elevator_GUI.h"

int main(){

    Elevador elevador(4);

    Pessoa *pessoa1 = new Pessoa(1,4,2,&elevador);
    Pessoa *pessoa2 = new Pessoa(2,2,4,&elevador);
    Pessoa *pessoa3 = new Pessoa(3,1,4,&elevador);

    Elevator_GUI janela(pessoa1,pessoa2,pessoa3,&elevador);

    elevador.join();
    pessoa1->join();
    pessoa2->join();
    pessoa3->join();


    delete pessoa1;

    return 0;
}
