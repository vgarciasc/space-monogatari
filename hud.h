#ifndef HUD_H
#define HUD_H

struct Hud {
	ALLEGRO_FONT *fonte=NULL;
	ALLEGRO_BITMAP *life=NULL;
	int score, score_posicao_x, score_posicao_y;
	int lives, lives_posicao_x, lives_posicao_y;

};

void desenha_hud(Hud*);
void desenha_score(Hud*);
void desenha_lives(Hud*);

void inicializa_hud(Hud*);
void inicializa_score(Hud*);
void inicializa_lives(Hud*);
#endif
