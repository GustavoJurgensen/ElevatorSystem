#include "pessoa.h"
#include "elevator_GUI.h"

int main(){
    
    Elevator_GUI janela;

    Elevador elevador(10);

    Pessoa *pessoa1 = new Pessoa(1,4,2,&elevador);
    Pessoa *pessoa2 = new Pessoa(2,2,7,&elevador);
    Pessoa *pessoa3 = new Pessoa(3,7,4,&elevador);

    elevador.join();
    pessoa1->join();
    pessoa2->join();
    pessoa3->join();

    delete pessoa1;

    return 0;
}
