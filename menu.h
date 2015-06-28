#ifndef MENU_H
#define MENU_H

#include <stdio.h>
#include <stdlib.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>

#define MENU_FPS 10
#define MAX_BOTOES 20
#define N_KEYS 7

enum MYKEYS { KEY_UP, KEY_DOWN, KEY_LEFT, KEY_RIGHT, KEY_Z, KEY_ESCAPE, KEY_ENTER };

struct Menu {
	ALLEGRO_EVENT_QUEUE* event_queue;
	ALLEGRO_TIMER* timer;

	ALLEGRO_FONT* font_title;
	ALLEGRO_FONT* font_items;
	int font_size;

	int numero_de_botoes[MAX_BOTOES];
	int botao_selecionado;

	int numero_de_telas;
	int tela_selecionada;

	int new_game;

	bool key[N_KEYS];
};

void inicializa_menus (Menu* menu);

void desenha_fundo_menu_pause ();

void desenha_menu_pause (Menu* menu);

bool loop_menu (Menu* menu, int numero_tela);

void seleciona_nova_tela (Menu* menu, int numero_tela);

void navega_botoes_cima (Menu* menu);

void navega_botoes_baixo (Menu* menu);

void inicializa_event_queue_menu_pause (Menu* menu);

void inicializa_timer_menu_pause (Menu* menu);

#endif