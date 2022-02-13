#include "elevador.h"


Elevador::Elevador(){
    this->andares = 4;

    this->andar_atual = 1;
    this->andar_requisitado.clear();

    this->porta_aberta = false;
    this->_requisitado = false;
    this->_movimentando = false;
};

Elevador::Elevador(int andares) : Elevador(){
    this->andares = andares;
};

void Elevador::print_andar(){
    std::cout << "Andar atual: " << this->andar_atual << std::endl;
};

void Elevador::subindo(){
    std::cout << "Elevador Subindo" << std::endl;
    
    // while(this->andar_atual < this->andar_requisitado[0]){
    //     this->andar_atual++;
    //     this->_movimentando = true;
    //     std::cout << "Andar: "<< this->andar_atual <<"\n";
    // }
    //this->_movimentando = false;

    if (this->andar_atual == this->andares){
        std::cout << "ERRO: Andar atual é o último" << std::endl;
        this->sentido = STOP;
        this->_movimentando = false;
        return;
    }

    if (this->_movimentando){
        this->andar_atual++;
        this->print_andar();
    }
    
    return;
};

void Elevador::descendo(){
    std::cout << "Elevador Descendo" << std::endl;
    
    // while(this->andar_atual > this->andar_requisitado[0]){
    //     this->andar_atual--;
    //     this->_movimentando = true;
    //     std::cout << "Andar: "<< this->andar_atual <<"\n";
    // }
    // this->_movimentando = false;

    if (this->andar_atual == 1){
        std::cout << "ERRO: Andar atual é o primeiro" << std::endl;
        this->sentido = STOP;
        this->_movimentando = false;
        return;
    }

    if (this->_movimentando){
        this->andar_atual--;
        this->print_andar();
    }
    return;
};

void Elevador::act(){
    if(this->sentido == STOP){
        this->_movimentando = false;

        std::cout << "Elevador parou" << std::endl;
        this->abre_porta();
        this->fecha_porta();

        this->prox_requisicao();
 
        if(this->get_destino_atual() != -1){ //return -1 se não houver mais destinos
            std::cout << "Próximo destino: Andar " << this->get_destino_atual() << std::endl;
        }
    }

    else if(this->sentido == UP){
        this->_movimentando = true;
        this->subindo();
    }

    else if(this->sentido == DOWN){
        this->_movimentando = true;
        this->descendo();
    }
};

void Elevador::prox_requisicao(){
    this->andar_requisitado.pop_back();
};

void Elevador::periodic(){
    while(1){
        if(this->andar_requisitado.empty() && this->porta_aberta == false){
            this->sentido = IDLE;
            this->_movimentando = false;

        }
        else if(this->andar_requisitado.empty() && this->porta_aberta == true){
            this->_movimentando = false;
            this->fecha_porta();
        }
        else{
            this->set_sentido(this->get_destino_atual());
            this->act();

        }
    }
};

//return destino atual do elevador
int Elevador::get_destino_atual(){
    if(this->andar_requisitado.empty()){
        return -1;
    }

    return this->andar_requisitado.back();
};

void Elevador::requisitado(int andar){
    mtx.lock();
    int checa_requsicao = checa_requisicao(andar);
    if(checa_requsicao == 3){
        mtx.unlock();
        return;
    }
    set_sentido(andar);

    entrada_req(andar);
  

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
    std::cout << "Abrindo porta";
    this->porta_aberta = true;
};

void Elevador::fecha_porta(){
    std::cout << "Fechando porta";
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
        //std::cout << "WARN: Elevador já se encontra no andar requisitado\n";
 		return 0;
}

void Elevador::set_sentido(int andar){
    if(andar > this->andar_atual){
        this->sentido = UP;
    }else if(andar > this->andar_atual){
        this->sentido = DOWN;
    }else{
        this->sentido = STOP;
    }
}

int Elevador::get_andar_atual(){
    return this->andar_atual;
}


bool Elevador::entrada_req(int andar){
    if(!this->andar_disponivel(andar)){
        std::cout << "ERRO: Andar " << andar << " inexistente" << std::endl;
        return 0;
    }

    if(std::find(this->andar_requisitado.begin(),this->andar_requisitado.end(),andar) != this->andar_requisitado.end()){
        //Andar requsitado já disponivel na fila
        std::cout << "ERRO: Andar " << andar << " já requisitado" << std::endl;
        return 0; 
    }else{
        //Andar requisitado add na fila
        this->andar_requisitado.insert(this->andar_requisitado.begin(),andar);
        std::cout << "Andar " << andar << " requisitado" << std::endl;
        return 1;
    }

}

bool Elevador::destino_req(int andar){
    if(!this->andar_disponivel(andar)){
        std::cout << "ERRO: Andar " << andar << " inexistente" << std::endl;
        return 0;
    }

    auto index_andar = std::find(this->andar_requisitado.begin(),this->andar_requisitado.end(),andar);

    if(index_andar != this->andar_requisitado.end()){
        //Andar requsitado já disponivel na fila, porém agora priorizado

        //copia valor na fila
        int dummy = this->andar_requisitado.at(std::distance(this->andar_requisitado.begin(),index_andar));

        //apaga valor e insere no final da mesma
        this->andar_requisitado.erase(index_andar);
        
        this->andar_requisitado.push_back(dummy);
        std::cout << "Andar " << andar << " priorizado" << std::endl;
        return 1; 

    }else{
        //Andar requisitado add na fila com prioridade
        this->andar_requisitado.push_back(andar);
        std::cout << "Andar " << andar << " requisitado" << std::endl;
        return 1;
    }
}

bool Elevador::andar_disponivel(int andar){
    if (andar > 0 && andar <= this->andares) {
        return 1;
    }else{
        return 0;
    } 
}