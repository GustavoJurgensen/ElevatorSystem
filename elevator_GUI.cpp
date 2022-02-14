#include "elevator_GUI.h"

Elevator_GUI::Elevator_GUI(){
    this->janela.create(sf::VideoMode(640,480), "Elevator System", sf::Style::Titlebar | sf::Style::Close);
    this->background_img.loadFromFile("Imagens/Background.png");
    this->background_sprite.setTexture(this->background_img);
    
    this->elevador_img.loadFromFile("Imagens/Elevador.png");
    this->elevador_sprite.setTexture(this->elevador_img);
    this->elevador_sprite.setPosition(288,138);
    
    this->pessoa_img.loadFromFile("Imagens/Pessoa.png");
    this->pessoa_sprite.setTexture(this->pessoa_img);
    this->pessoa_sprite.setPosition(140,80);
    //this->pessoa_sprite.setPosition(320,160);


    while(this->janela.isOpen()){
        while (this->janela.pollEvent(this->evento))
        {
            if(this->evento.type == sf::Event::Closed) this->janela.close();
        }
        this->janela.clear(); // Limpa o frame anterior
        this->janela.draw(background_sprite);
        this->janela.draw(elevador_sprite);
        //std::cout << elevador_sprite.getPosition().x << std::endl;
        elevador_sprite.setPosition(288,elevador_sprite.getPosition().y+0.01);
        this->janela.draw(pessoa_sprite);
        this->janela.display(); // Escreve o frame atual

        
    }
}