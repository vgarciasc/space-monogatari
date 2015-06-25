#ifndef ALIEN_H
#define ALIEN_H

#include <stdio.h>
#include <stdlib.h>

#define LINHAS_TROPA 5
#define COLUNAS_TROPA 11
#define DISTANCIA_PASSO 5

enum DIRECAO_ALIEN { alienESQUERDA, alienDIREITA, alienCIMA, alienBAIXO };

struct Alien {
	int posicao_x, posicao_y;
	int delta_x;
	DIRECAO_ALIEN direcao_atual;

	bool vivo;

	int sprite_atual;
	ALLEGRO_BITMAP* sprites[10];
};

void inicializa_alien (Alien* alien, int posicao_x, int posicao_y);

void inicializa_tropa (Alien alien[COLUNAS_TROPA][LINHAS_TROPA], int posicao_x, int posicao_y);

void finaliza_alien (Alien* alien);

void desenha_alien (Alien* alien);

void desenha_tropa (Alien alien[COLUNAS_TROPA][LINHAS_TROPA]);

void inicializa_sprites_alien (Alien* alien);

void finaliza_sprites_alien (Alien* alien);

void move_alien (Alien* alien, DIRECAO_ALIEN direcao);

int get_posicao_x_max_alien (Alien* alien);

int get_posicao_x_min_alien (Alien* alien);

#endif
