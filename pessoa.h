#include "elevador.h"
#include <iostream>
#include <thread>

class Pessoa{
    private:
        int andar_atual;
        int andar_destino;
        bool no_elevador;
        std::thread my_thread;
    public:
        Pessoa(int andar_atual, int andar_destino, Elevador*);
        void requisita_elevador(Elevador*);
        void seleciona_destino(Elevador*);
        void controla_pessoa(Elevador*);
        void join();
};