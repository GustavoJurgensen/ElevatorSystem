#include "pessoa.h"

Pessoa::Pessoa(int idPessoa, int andar_atual,int andar_destino, Elevador* elevador){
    this->id = idPessoa;
    this->andar_atual = andar_atual;
    this->andar_destino = andar_destino;
    this->no_elevador = false;
    my_thread = std::thread([=] { controla_pessoa(elevador); });
    std::cout << "PESSOA " << this->id << ": Criada" << std::endl;
}

void Pessoa::join(){
    this->my_thread.join();
}

void Pessoa::controla_pessoa(Elevador* elevador){
    if(this->no_elevador == false){
        requisita_elevador(elevador);
    }else{
        seleciona_destino(elevador);
    }
}

void Pessoa::requisita_elevador(Elevador* elevador){
    std::cout << "PESSOA " << this->id << ": " << "Requisitado elevador no andar " << this->andar_atual << std::endl;
    //chama o elevador e aguarda chegar (Elevador::requisitado)
    elevador->entrada_req(this->andar_atual);
    
    std::cout <<"PESSOA " << this->id << ": " << "Esperando o elevador" << std::endl;
    //quando chegar
    while (elevador->get_andar_atual() != this->andar_atual || elevador->get_status_porta() == false);
    {
            std::this_thread::sleep_for(std::chrono::milliseconds(10));
    }
    
    std::cout << "PESSOA " << this->id << ": " << "Entrando no elevador" << std::endl;
    std::this_thread::sleep_for(std::chrono::seconds(1));
    
    this->no_elevador = true;
    seleciona_destino(elevador);

}

void Pessoa::seleciona_destino(Elevador* elevador){
    std::cout << "PESSOA " << this->id << ": " << "Seleciona destino -> andar " << this->andar_destino << std::endl;
    //chama o elevador e aguarda chegar (Elevador::requisitado)
    elevador->destino_req(this->andar_destino);
    //quando chegar

    while (elevador->get_andar_atual() != this->andar_destino || elevador->get_status_porta() == false){
        std::this_thread::sleep_for(std::chrono::milliseconds(10));
    }
    
    std::this_thread::sleep_for(std::chrono::seconds(1));
    this->no_elevador = false;
    
    std::cout << "PESSOA " << this->id << ": " << "Sai do elevador" << std::endl;
}