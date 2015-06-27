#ifndef GAME_H
#define GAME_H

#include "alien.h"
#include "player.h"
#include "projetil.h"
#include "menu.h"
#include "mothership.h"

#define N_KEYS 4

enum MYKEYS { KEY_LEFT, KEY_RIGHT, KEY_Z, KEY_ESCAPE };

struct Jogo {
	ALLEGRO_DISPLAY *display;
	ALLEGRO_EVENT_QUEUE* event_queue;
	ALLEGRO_TIMER* timer;
	
	int largura, altura;
	ALLEGRO_BITMAP* fundo;

	Player player;
	Mothership mothership;
	Alien alien[COLUNAS_TROPA][LINHAS_TROPA];
	Menu menu;

	Projetil projetil_stack[50];
	int numero_de_projeteis;

	int loop_count;
	int loop_count_projetil;
	int loop_count_menu_pause;
	int loop_alien_movement;
	
	bool key[N_KEYS];
};

void inicializa_display (Jogo* jogo, int largura, int altura);

void finaliza_display (Jogo* jogo);

void inicializa_jogo (Jogo* jogo);

void finaliza_jogo (Jogo* jogo);

void desenha_jogo (Jogo* jogo);

void loop_de_jogo (Jogo* jogo);

void desenha_fundo_jogo (Jogo* jogo);

void inicializa_teclado (Jogo* jogo);

void inicializa_event_queue_jogo (Jogo* jogo);

void inicializa_timer_jogo (Jogo* jogo);

void tela_boot_jogo (Jogo* jogo);

void inic_funcoes_allegro (void);

void fadein (ALLEGRO_BITMAP* bitmap);

void inic_allegro (void);

void inic_allegro_primitive (void);

void inic_allegro_image (void);

void inic_allegro_font (void);

void inic_allegro_ttf (void);

#endif