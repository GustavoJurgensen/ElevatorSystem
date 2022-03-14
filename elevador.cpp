#include "elevador.h"


Elevador::Elevador(){
    this->andares = 4;

    this->andar_atual = 1;
    this->andar_requisitado.clear();

    this->porta_aberta = false;
    this->_requisitado = false;
    this->_movimentando = false;

    //this->my_thread = std::thread([=] { periodic(); });
};

Elevador::Elevador(int andares) : Elevador(){
    this->andares = andares;
};

void Elevador::start(){
    this->my_thread = std::thread([=] { periodic(); });
}

void Elevador::print_andar(){
    std::cout << "ELEVADOR: " <<"Andar atual: " << this->andar_atual << " ------- Destino atual: " << this->get_destino_atual() << std::endl;
};

void Elevador::subindo(){    
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
        std::this_thread::sleep_for(std::chrono::seconds(1));
        this->andar_atual++;
        this->print_andar();
    }
    
    return;
};

void Elevador::descendo(){
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
        std::this_thread::sleep_for(std::chrono::seconds(1));
        this->andar_atual--;
        this->print_andar();
    }
    return;
};

bool Elevador::get_status_porta(){
    return this->porta_aberta;
};

void Elevador::act(){
    if(this->sentido == STOP){
        this->_movimentando = false;
        this->prox_requisicao();

        std::cout << "ELEVADOR: " <<"Parei" << std::endl;
        this->abre_porta();
        this->fecha_porta();
 
        if(this->get_destino_atual() != -1){ //return -1 se não houver mais destinos
            std::cout << "ELEVADOR: " <<"Próximo destino: Andar " << this->get_destino_atual() << std::endl;
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
    std::lock_guard<std::mutex> lock(this->mtx);
    this->andar_requisitado.pop_back();
};

void Elevador::periodic(){
    std::cout << "Inicializando ELEVADOR (" << this->andares << " andares)" << std::endl;

    while(1){
        if(this->andar_requisitado.empty() && this->porta_aberta == false){
            if(this->sentido != IDLE) std::cout <<"ELEVADOR: " << "Entrando em estado IDLE" << std::endl;
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
        std::this_thread::sleep_for(std::chrono::milliseconds(10));
    }
};

//return destino atual do elevador
int Elevador::get_destino_atual(){
    std::lock_guard<std::mutex> lock(this->mtx);

    if(this->andar_requisitado.empty()){
        return -1;
    }

    return this->andar_requisitado.back();
};

void Elevador::join(){
    this->my_thread.join();
};

void Elevador::abre_porta(){
    std::cout << "ELEVADOR: " <<"Abrindo porta" << std::endl;
    
    this->porta_aberta = true;
    std::this_thread::sleep_for(std::chrono::seconds(5));

};

void Elevador::fecha_porta(){
    std::cout << "ELEVADOR: " <<"Fechando porta" << std::endl;
    std::this_thread::sleep_for(std::chrono::seconds(1));
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
    }else if(andar < this->andar_atual){
        this->sentido = DOWN;
    }else{
        this->sentido = STOP;
    }
}

int Elevador::get_andar_atual(){
    return this->andar_atual;
}


bool Elevador::entrada_req(int andar){
    std::lock_guard<std::mutex> lock(this->mtx);

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
        
        std::cout << "ELEVADOR: " <<"Andar " << andar << " requisitado" << std::endl;
        return 1;
    }

}

bool Elevador::destino_req(int andar){
    
    std::lock_guard<std::mutex> lock(this->mtx);

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
        std::cout << "ELEVADOR: " <<"Andar " << andar << " priorizado" << std::endl;
        return 1; 

    }else{
        //Andar requisitado add na fila com prioridade
        this->andar_requisitado.push_back(andar);
        std::cout << "ELEVADOR: " <<"Andar " << andar << " requisitado" << std::endl;
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