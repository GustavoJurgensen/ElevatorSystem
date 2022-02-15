#include "elevator_GUI.h"

Elevator_GUI::Elevator_GUI(Pessoa* ptr_pessoa,Pessoa* ptr_pessoa2,Pessoa* ptr_pessoa3,Elevador* ptr_elevador){
    
    this->ptr_pessoa = ptr_pessoa;
    this->ptr_pessoa2 = ptr_pessoa2;
    this->ptr_pessoa3 = ptr_pessoa3;
    this->ptr_elevador = ptr_elevador;


    this->janela.create(sf::VideoMode(640,480), "Elevator System", sf::Style::Titlebar | sf::Style::Close);
    this->background_img.loadFromFile("Imagens/Background.png");
    this->background_sprite.setTexture(this->background_img);
    
    this->elevador_img.loadFromFile("Imagens/Elevador.png");
    this->elevador_sprite.setTexture(this->elevador_img);
    this->elevador_sprite.setPosition(288,138);
    
    this->pessoa_img.loadFromFile("Imagens/Pessoa.png");
    this->pessoa_sprite.setTexture(this->pessoa_img);

    this->pessoa_sprite2.setTexture(this->pessoa_img);

    this->pessoa_sprite3.setTexture(this->pessoa_img);

    
    //this->pessoa_sprite.setPosition(320,160);

    this->my_thread = std::thread([=] { loop(); });
}

void Elevator_GUI::loop(){
    while(this->janela.isOpen()){
        while (this->janela.pollEvent(this->evento))
        {
            if(this->evento.type == sf::Event::Closed) this->janela.close();
        }
        this->janela.clear(); // Limpa o frame anterior

        this->janela.draw(background_sprite);
        
        
        this->atualiza_elevador();
        this->atualiza_pessoas();
        

        this->janela.display(); // Escreve o frame atual
        std::this_thread::sleep_for(std::chrono::milliseconds(10)); // Verificar alternativa de FPS
    }
}

void Elevator_GUI::atualiza_elevador(){
    //std::cout << elevador_sprite.getPosition().x << std::endl;
    //elevador_sprite.setPosition(288,elevador_sprite.getPosition().y+0.01);

    elevador_sprite.setPosition(andares[0],andares[this->ptr_elevador->get_andar_atual()]);
    this->janela.draw(elevador_sprite);
}

void Elevator_GUI::atualiza_pessoas(){
    if(this->ptr_pessoa->get_no_elevador()){
        this->pessoa_sprite.setPosition(andares[0]+20,andares[this->ptr_elevador->get_andar_atual()]+20);
    }else{
        if(this->ptr_pessoa->get_andar_atual() == this->ptr_pessoa->get_andar_destino()){
            this->pessoa_sprite.setPosition(andar_pessoa_out[0],andar_pessoa_out[this->ptr_pessoa->get_andar_destino()]);
        }else{
            this->pessoa_sprite.setPosition(andar_pessoa_in[0],andar_pessoa_in[this->ptr_pessoa->get_andar_atual()]);
        }

    }

    if(this->ptr_pessoa2->get_no_elevador()){
        this->pessoa_sprite2.setPosition(andares[0]+20,andares[this->ptr_elevador->get_andar_atual()]+20);
    }else{
        if(this->ptr_pessoa2->get_andar_atual() == this->ptr_pessoa2->get_andar_destino()){
            this->pessoa_sprite2.setPosition(andar_pessoa_out[0],andar_pessoa_out[this->ptr_pessoa2->get_andar_destino()]);
        }else{
            this->pessoa_sprite2.setPosition(andar_pessoa_in[0],andar_pessoa_in[this->ptr_pessoa2->get_andar_atual()]);
        }

    }

    if(this->ptr_pessoa3->get_no_elevador()){
        this->pessoa_sprite3.setPosition(andares[0]+20,andares[this->ptr_elevador->get_andar_atual()]+20);
    }else{
        if(this->ptr_pessoa3->get_andar_atual() == this->ptr_pessoa3->get_andar_destino()){
            this->pessoa_sprite3.setPosition(andar_pessoa_out[0],andar_pessoa_out[this->ptr_pessoa3->get_andar_destino()]);
        }else{
            this->pessoa_sprite3.setPosition(andar_pessoa_in[0],andar_pessoa_in[this->ptr_pessoa3->get_andar_atual()]);
        }

    }

    this->janela.draw(pessoa_sprite);
    this->janela.draw(pessoa_sprite2);
    this->janela.draw(pessoa_sprite3);


}