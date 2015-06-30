#include <stdio.h>
#include <allegro5/allegro.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>

#include "game.h"
#include "hud.h"

void desenha_hud (Hud *hud){
	desenha_score(hud);
	desenha_lives(hud);
}

void desenha_score (Hud *hud){
	al_draw_text(hud->fonte,
				 CINZA,
				 hud->score_posicao_x, 
				 hud->posicao_y, 
				 0, 
				 "SCORE: ");

	al_draw_textf(hud->fonte, 
				  VERDE, 
				  hud->score_posicao_x+80, 
				  hud->posicao_y, 
				  0, 
				  "%d", 
				  hud->score);
}

void desenha_lives (Hud *hud){
	al_draw_text(hud->fonte, 
				 CINZA,
				 hud->lives_posicao_x,
				 hud->posicao_y,
				 0,
				 "LIVES:");

	for (int i = 0; i < hud->lives; i++)
		al_draw_bitmap(hud->life,
					   hud->lives_posicao_x + 80 + (al_get_bitmap_width(hud->life)*1.25) *(i),
					   hud->posicao_y,
					   0);
}

void inicializa_hud (Hud *hud){
	hud->fonte = al_load_font("resources/acknowledge.ttf", 20, 0);
	if (hud->fonte == NULL){
		puts("Erro ao carregar \"resources/acknowledge.ttf\"");
		exit(0);
	}

	hud->posicao_y = 10;

	inicializa_score(hud);
	inicializa_lives(hud);
}

void inicializa_score (Hud *hud){
	hud->score = 0;
	hud->score_posicao_x = 40;
}

void inicializa_lives (Hud *hud){
	hud->life = al_load_bitmap("resources/life2.png");
	if(hud->life == NULL){
		puts("Erro ao carregar \"resources/life2.png\"");
		exit(0);
	}

	hud->lives = NUMERO_VIDAS;
	hud->lives_posicao_x = 440;
}