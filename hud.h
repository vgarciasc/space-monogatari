#ifndef HUD_H
#define HUD_H

#include "config.h"

struct Hud {
	ALLEGRO_FONT *fonte=NULL;
	ALLEGRO_BITMAP *life=NULL;
	int score, score_posicao_x;
	int lives, lives_posicao_x;

	int altura_sprite_vida, largura_sprite_vida;

	int posicao_y;
};

void inicializa_hud (Hud *hud);

void inicializa_score (Hud* hud);

void inicializa_lives (Hud* hud);

void desenha_hud (Hud* hud);

void desenha_score (Hud* hud);

void desenha_lives (Hud* hud);

#endif