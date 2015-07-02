#ifndef PROJETIL_H
#define PROJETIL_H

#include <stdio.h>
#include <stdlib.h>

#include "player.h"
#include "config.h"

struct Jogo;

struct Projetil {
	double posicao_x, posicao_y;
	double largura, altura;
	double velocidade;

	ALLEGRO_BITMAP* bitmap;
	DIRECAO direcao;
};

void inicializa_projetil (Projetil* projetil, double posicao_x, double posicao_y, DIRECAO direcao);

void inicializa_bitmap_projetil (Projetil* projetil);

void desenha_projetil (Projetil* projetil);

void move_projetil (Projetil* projetil);

void finaliza_projetil (Projetil* projetil);

void copy_projetil (Projetil* destino, Projetil* origem);

int get_posicao_x_min_projetil (Projetil* projetil);

int get_posicao_x_max_projetil (Projetil* projetil);

int get_posicao_y_min_projetil (Projetil* projetil);

int get_posicao_y_max_projetil (Projetil* projetil);

#endif