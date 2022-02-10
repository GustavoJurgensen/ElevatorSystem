#include "elevador.h"
#include <thread>

class Pessoa{
    private:
        int andar_atual;
        int andar_destino;
        bool no_elevador;

    public:
        Pessoa(int andar_atual,int andar_destino) :
                andar_atual(andar_atual),
                andar_destino(andar_destino),
                no_elevador(false)
                {};
        void requisita_elevador(Elevador elevador);
        void seleciona_destino(Elevador elevador);
        void controla_pessoa(Elevador elevador);
        std::thread thread_pessoa(Elevador elevador);
};