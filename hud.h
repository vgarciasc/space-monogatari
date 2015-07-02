#ifndef HUD_H
#define HUD_H

#include "config.h"

struct Hud {
	int score, score_posicao_x;
	int lives, lives_posicao_x;
	double altura_bitmap_vida, largura_bitmap_vida;

	ALLEGRO_FONT *font;
	ALLEGRO_BITMAP *life;

	int posicao_y;
};

void inicializa_hud (Hud *hud);

void inicializa_score (Hud* hud);

void inicializa_lives (Hud* hud);

void desenha_hud (Hud* hud);

void desenha_score (Hud* hud);

void desenha_lives (Hud* hud);

#endif