#ifndef PESSOA_H
#define PESSOA_H

#include "elevador.h"

class Pessoa{
    private:
        int id;
        int andar_atual;
        int andar_destino;
        bool no_elevador;
        std::thread my_thread;
    public:
        Pessoa(){};
        Pessoa(int id, int andar_atual, int andar_destino, Elevador*);
        void requisita_elevador(Elevador*);
        void seleciona_destino(Elevador*);
        void controla_pessoa(Elevador*);
        void join();
        void detach();
        bool get_no_elevador();
        int get_andar_atual();
        int get_andar_destino();
};

#endif
