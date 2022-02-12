#include "elevador.h"
#include <iostream>

Elevador::Elevador(){
    this->andares = 4;
    this->andar_atual = 1;
    this->andar_requisitado.clear();
    this->andar_requisitado.push_back(1);
    this->porta_aberta = false;
    this->_requisitado = false;
    this->_movimentando = false;
};

Elevador::Elevador(int andares) : Elevador(){
    this->andares = andares;
    // this->andar_atual = 1;
    // this->andar_requisitado = 1;
    // this->porta_aberta = false;
    // this->_requisitado = false;
    // this->_movimentando = false;
};

void Elevador::subindo(){
    std::cout << "Elevador Subindo" << std::endl;
    while(this->andar_atual < this->andar_requisitado[0]){
        this->andar_atual++;
        this->_movimentando = true;
        std::cout << "Andar: "<< this->andar_atual <<"\n";
    }
    this->_movimentando = false;
    return;
};

void Elevador::descendo(){
    std::cout << "Elevador Descendo" << std::endl;
    while(this->andar_atual > this->andar_requisitado[0]){
        this->andar_atual--;
        this->_movimentando = true;
        std::cout << "Andar: "<< this->andar_atual <<"\n";
    }
    this->_movimentando = false;
    return;
};

void Elevador::requisitado(int andar){
    mtx.lock();
    int checa_requsicao = checa_requisicao(andar);
    if(checa_requsicao == 3){
        mtx.unlock();
        return;
    }

    set_sentido(andar);
    this->andar_requisitado[0] = andar;

    if(this->andar_requisitado[0] == this->andar_atual){
        this->abre_porta();
        mtx.unlock();
        return;
    }
    else{
        this->fecha_porta();

        if(this->sentido == UP){
            this->subindo();
        }
        else if(this->sentido == DOWN)
        {
            this->descendo();
        }

        this->abre_porta();

        mtx.unlock();
        return;
    }
};

void Elevador::abre_porta(){
    this->porta_aberta = true;
};

void Elevador::fecha_porta(){
    this->porta_aberta = false;
};

int Elevador::checa_requisicao(int andar) const{
    if (sentido == UP && andar < this->andar_atual){
        std::cout << "WARN: Elevador está subindo\n";
        return 1;
    }
 	else if (sentido == DOWN && andar > this->andar_atual){
        std::cout << "WARN: Elevador está descendo\n";
 		return 2;
    }
 	else if (andar < 1 || andar > this->andares){
        std::cout << "ERROR: Andar não existe\n";
 		return 3;
    }
    else
 		return 0;
}

void Elevador::set_sentido(int andar){
    if(andar > this->andar_atual){
        this->sentido = UP;
    }else if(andar > this->andar_atual){
        this->sentido = DOWN;
    }
}

int Elevador::get_andar_atual(){
    return this->andar_atual;
}