#ifndef ELEVATOR_GUI
#define ELEVATOR_GUI

#include <SFML/Graphics.hpp>
#include <iostream>

#include <thread>
#include "elevador.h"
#include "pessoa.h"

class Elevator_GUI{
    private:
        std::thread my_thread;
        sf::RenderWindow janela;
        sf::Event evento;

        Elevador* ptr_elevador;
        Pessoa* ptr_pessoa;
        Pessoa* ptr_pessoa2;
        Pessoa* ptr_pessoa3;

        // Background
        sf::Texture background_img;
        sf::Sprite background_sprite;

        //Elevador
        sf::Texture elevador_img;
        sf::Sprite elevador_sprite;

        //Pessoa
        sf::Texture pessoa_img;
        sf::Sprite pessoa_sprite;

        void loop();
    public:
        Elevator_GUI();
        void update();
        void render();

        void atualiza_elevador();
        void atualiza_pessoas();

};

#endif