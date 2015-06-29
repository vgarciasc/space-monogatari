#ifndef SHIELD_H
#define SHIELD_H

#include "config.h"

struct Jogo;

struct Shield {
	double posicao_x, posicao_y;
	ALLEGRO_BITMAP* part_bitmap[PARTES_X][PARTES_Y];
	ESTADO part_state[PARTES_X][PARTES_Y];

	ALLEGRO_BITMAP* bitmap_inteiro;
	ALLEGRO_BITMAP* bitmap_danificado;
};

void inicializa_shield (Shield* shield, double posicao_x, double posicao_y);

void desenha_shield (Shield* shield); 

void colisao_shield_vs_projetil (Jogo *jogo, Shield *shield);

#endif