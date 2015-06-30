#include <stdio.h>
#include <allegro5/allegro.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>

#include "hud.h"

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
	hud->life = al_load_bitmap("resources/player4.png");
	if(hud->life == NULL){
		puts("Erro ao carregar \"resources/player4.png\"");
		exit(0);
	}

	hud->altura_sprite_vida = 24;
	hud->largura_sprite_vida = 24;

	hud->lives = NUMERO_VIDAS;
	hud->lives_posicao_x = (LARGURA_DISPLAY/12)*8;
}

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
				  hud->score_posicao_x + LARGURA_DISPLAY/8.5, 
				  hud->posicao_y, 
				  0, 
				  "%d", 
				  hud->score);
}

void desenha_lives (Hud *hud){
	int linha_vidas = 0;
	int coluna_vidas = 0;

	al_draw_text(hud->fonte, 
				 CINZA,
				 hud->lives_posicao_x - LARGURA_DISPLAY/12,
				 hud->posicao_y,
				 0,
				 "LIVES:");

	for (int i = 0; i < hud->lives; i++) {
		if (hud->lives_posicao_x + LARGURA_DISPLAY/12 + hud->largura_sprite_vida*1.25*(coluna_vidas) > LARGURA_DISPLAY - hud->largura_sprite_vida) {
			linha_vidas++;
			coluna_vidas = 0;
		}

		al_draw_scaled_bitmap(hud->life,
							  0, 0,
							  al_get_bitmap_width(hud->life),
							  al_get_bitmap_height(hud->life),
							  hud->lives_posicao_x + LARGURA_DISPLAY/12 + hud->largura_sprite_vida*1.25*(coluna_vidas),
							  hud->posicao_y + linha_vidas*(hud->altura_sprite_vida*1.25),
							  hud->largura_sprite_vida, hud->altura_sprite_vida,
							  0);
		
		coluna_vidas++;
	}
}