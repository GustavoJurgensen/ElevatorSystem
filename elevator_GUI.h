#ifndef ELEVATOR_GUI
#define ELEVATOR_GUI

#include <SFML/Graphics.hpp>
#include <iostream>

class Elevator_GUI{
    private:
        sf::RenderWindow janela;
        sf::Event evento;
        // Background
        sf::Texture background_img;
        sf::Sprite background_sprite;

        //Elevador
        sf::Texture elevador_img;
        sf::Sprite elevador_sprite;

        //Pessoa
        sf::Texture pessoa_img;
        sf::Sprite pessoa_sprite;

    public:
        Elevator_GUI();
        void update();
        void render();


};

#endif