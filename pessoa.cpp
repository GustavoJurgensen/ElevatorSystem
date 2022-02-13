#include "pessoa.h"

Pessoa::Pessoa(int andar_atual,int andar_destino, Elevador* elevador){
    this->andar_atual = andar_atual;
    this->andar_destino = andar_destino;
    this->no_elevador = false;
    my_thread = std::thread([=] { controla_pessoa(elevador); });
}

void Pessoa::join(){
    my_thread.join();
}

void Pessoa::controla_pessoa(Elevador* elevador){
    std::cout << "controla_pessoa" << std::endl;
    if(this->no_elevador == false){
        requisita_elevador(elevador);
    }else{
        seleciona_destino(elevador);
    }
}

void Pessoa::requisita_elevador(Elevador* elevador){
    std::cout << "requisita_elevador" << std::endl;
    //chama o elevador e aguarda chegar (Elevador::requisitado)
    elevador->entrada_req(this->andar_atual);
    elevador->periodic();
    //quando chegar
    while (elevador->get_andar_atual() != this->andar_atual)
    {
        std::cout << "Esperando o elevador" << std::endl;
    }
    
    this->no_elevador = true;
    seleciona_destino(elevador);

}

void Pessoa::seleciona_destino(Elevador* elevador){
    std::cout << "seleciona_destino" << std::endl;
    //chama o elevador e aguarda chegar (Elevador::requisitado)
    elevador->requisitado(this->andar_destino);
    //quando chegar
    this->no_elevador = false;
}