class Elevador{
    enum Sentido{ UP, DOWN };
	Sentido sentido;

    private:
        bool _requisitado;
        bool _movimentando;
        bool porta_aberta;
        int andar_atual;
        int andar_requisitado;
        int andares; //Número máx de andares (1->X)
        int n_passoas;

    public:
        Elevador();
        Elevador(int andares);

        void subindo();
        void descendo();
        void requisitado(int andar);
        void abre_porta();
        void fecha_porta();
    private:
        int checa_requisicao(int andar) const;
        void set_sentido(int andar);
};