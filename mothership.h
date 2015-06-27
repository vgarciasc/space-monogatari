#ifndef MOTHERSHIP_H
#define MOTHERSHIP_H

struct Jogo;

struct Mothership{
	ALLEGRO_BITMAP *imagem=NULL;
	int posicao_x;
	int posicao_y;
	int velocidade;
	int status;
	int altura;
	int largura;
};

//desenha a mothership de acordo com as coordenadas
//apenas essa aqui será usada no loop do jogo
void desenha_mothership(Mothership*, Jogo*, Projetil*);

// por enquanto apenas coloca posicao_x=0 e posicao_y=0[depois faz mais]
// AINDA PRECISA REINICIAR O CONTADOR AQUI
void reinicia_mothership(Mothership*);

// responsável pela mudança nas coordenadas
void movimenta_mothership(Mothership*);

// carrega a imagem em mothership->imagem, reinicia as posições e define a velocidade
//utilizar antes da inicialização do loop do jogo
void inicializa_mothership(Mothership*);

//função que controla se a mothership mae aparece ou n
int autoriza_mothership(Mothership*, Jogo*);

void detecta_colisao(Mothership*, Jogo*);

//destroi a mothership mae
void finaliza_mothership(Mothership*);

#endif