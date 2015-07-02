
#ifndef MOTHERSHIP_H
#define MOTHERSHIP_H

#include "config.h"

struct Jogo;

struct Mothership {
	double posicao_x, posicao_y;
	double delta_x, delta_y;
	double largura, altura;
	double distancia_passo;
	double frequencia;

	ALLEGRO_TIMER *timer;
	ALLEGRO_EVENT_QUEUE *event_queue;

	ALLEGRO_BITMAP *bitmap;
	DIRECAO direcao;

	bool ativo;
};

void inicializa_mothership (Mothership*, Jogo*);

void desenha_mothership (Mothership*);

void reinicia_mothership (Mothership*);

void movimenta_mothership (Mothership*);

bool autoriza_mothership (Mothership*);

void inicializar_timer_mothership (Mothership*);

void colisao_mothership_vs_projetil (Jogo*);

void finaliza_mothership (Mothership*);

int get_posicao_x_max_mothership (Mothership*);

int get_posicao_y_max_mothership (Mothership*);

int get_posicao_x_min_mothership (Mothership*);

int get_posicao_y_min_mothership (Mothership*);

#endif