#include "pessoa.h"

int main(){

    Elevador elevador;

    Pessoa *pessoa1 = new Pessoa(4,2,&elevador);
    pessoa1->join();
    
    delete pessoa1;

    return 0;
}
