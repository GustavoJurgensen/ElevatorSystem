#include "pessoa.h"

std::thread Pessoa::thread_pessoa(Elevador elevador){
    return std::thread([=] { controla_pessoa(elevador); });
}

void Pessoa::controla_pessoa(Elevador elevador){
    if(this->no_elevador == false){
        requisita_elevador(elevador);
    }else{
        seleciona_destino(elevador);
    }
}

void Pessoa::requisita_elevador(Elevador elevador){
    //chama o elevador e aguarda chegar (Elevador::requisitado)
    elevador.requisitado(this->andar_atual);
    //quando chegar
    this->no_elevador = true;
}

void Pessoa::seleciona_destino(Elevador elevador){
    //chama o elevador e aguarda chegar (Elevador::requisitado)
    elevador.requisitado(this->andar_destino);
    //quando chegar
    this->no_elevador = false;
}