#ifndef ELEVADOR_H
#define ELEVADOR_H

#include <mutex>
#include <thread>
#include <vector>
#include <iostream>
#include <algorithm>
#include <chrono>
#include <ctime>

class Elevador{
    enum Sentido{ UP, DOWN, STOP, IDLE };
	Sentido sentido;

    private:
        bool _requisitado;
        bool _movimentando;
        bool porta_aberta;
        int andar_atual;
        std::vector<int> andar_requisitado;
        int andares; //Número máx de andares (1->X)
        int n_pessoas;
        std::thread my_thread;
        std::mutex mtx;

    public:
        Elevador();
        Elevador(int andares);
        
        //Adiciona andares na fila (logica diferente para requisição para entrar e sair do elevador)
        //Return 1 if for success and 0 for fail
        bool entrada_req(int andar); 
        bool destino_req(int andar);

        // void requisitado(int andar); DESCONTINUADA

        void abre_porta();
        void fecha_porta();

        bool get_status_porta(); //return 1 if porta aberta e 0 if porta fechada
        int get_andar_atual();
        int get_destino_atual();

        void periodic();
        void join();



    private:

        void act();

        void prox_requisicao();
        int checa_requisicao(int andar) const;
        
        void set_sentido(int andar);
        
        void print_andar();

        void subindo();
        void descendo();

        bool andar_disponivel(int andar); // return 1 se andar existir, 0 caso não exista
        bool movimenta_elevador(); //return 1 if success, 0 if fail
        
};

#endif