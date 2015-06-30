#ifndef HUD_H
#define HUD_H

#include "config.h"

struct Jogo;

struct Hud {
	ALLEGRO_FONT *fonte=NULL;
	ALLEGRO_BITMAP *life=NULL;
	int score, score_posicao_x;
	int lives, lives_posicao_x;

	int posicao_y;
};

void desenha_hud (Hud* hud, Jogo* jogo);

void desenha_score (Hud* hud);

void desenha_lives (Hud* hud, Jogo* jogo);

void inicializa_hud (Hud *hud, Jogo* jogo);

void inicializa_score (Hud* hud);

void inicializa_lives (Hud* hud, Jogo* jogo);

#endif