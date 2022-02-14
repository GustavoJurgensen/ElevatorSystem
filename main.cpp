#include "pessoa.h"
#include "elevator_GUI.h"

int main(){

    Elevator_GUI janela;
    Elevador elevador;

    Pessoa *pessoa1 = new Pessoa(4,2,&elevador);
    pessoa1->join();
    
    delete pessoa1;

    return 0;
}
