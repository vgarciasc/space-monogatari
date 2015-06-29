
#ifndef MOTHERSHIP_H
#define MOTHERSHIP_H

#include "config.h"

struct Jogo;

struct Mothership {
	ALLEGRO_BITMAP *imagem = NULL;
	ALLEGRO_TIMER *tempo = NULL;
	ALLEGRO_EVENT_QUEUE *fila_evento = NULL;

	int posicao_x, posicao_y, delta_x, delta_y;
	bool ativo;
	int altura_sprite,largura_sprite;
	int largura_tela;
};

//desenha a mothership de acordo com as coordenadas
//apenas essa aqui será usada no loop do jogo
void desenha_mothership (Mothership*);

// por enquanto apenas coloca posicao_x=0 e posicao_y=0[depois faz mais]
// AINDA PRECISA REINICIAR O CONTADOR AQUI
void reinicia_mothership (Mothership*);

// responsável pela mudança nas coordenadas
void movimenta_mothership (Mothership*);

// carrega a imagem em mothership->imagem, reinicia as posições e define a velocidade
//utilizar antes da inicialização do loop do jogo
void inicializa_mothership (Mothership*, Jogo*);

//função que controla se a mothership mae aparece ou n
bool autoriza_mothership (Mothership*);

void inicializar_timer_mothership (Mothership*);

void colisao_mothership_vs_projetil (Jogo*);

//destroi a mothership mae
void finaliza_mothership (Mothership*);

int get_posicao_x_max_mothership (Mothership*);

int get_posicao_y_max_mothership (Mothership*);

int get_posicao_x_min_mothership (Mothership*);

int get_posicao_y_min_mothership (Mothership*);

#endif