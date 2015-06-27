#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <allegro5/allegro.h>
#include <allegro5/allegro_primitives.h>

#include "menu.h"

#define MARROM_ESCURO al_map_rgb(20,20,12)
#define MARROM_CLARO al_map_rgb(247, 180, 109)
#define BRANCO al_map_rgb(255, 255, 255)

void inicializa_menus (Menu* menu) {
  menu->event_queue = NULL;
  menu->timer = NULL;
  
  inicializa_timer_menu_pause (menu);
  inicializa_event_queue_menu_pause(menu);

  menu->botao_selecionado = 0;
  //botoes e telas funcionam com logica de array (primeiro botao 0, segundo botao 1, etc)
  
  menu->numero_de_telas = 5;

  menu->numero_de_botoes[0] = 3;
  menu->numero_de_botoes[1] = 2;
  menu->numero_de_botoes[2] = 1;
  menu->numero_de_botoes[3] = 2;

  menu->font_size = 24;

	menu->font_title = al_load_font("resources/verdana.ttf", menu->font_size*2, 0);
  menu->font_items = al_load_font("resources/verdana.ttf", menu->font_size, 0);

	if (menu->font_title == NULL || menu->font_items == NULL) {
		puts("Erro ao carregar o arquivo resources/verdana.ttf");
		exit(0);
	}

}

void desenha_fundo_menu_pause () {
	al_clear_to_color(MARROM_ESCURO);
}

void desenha_menu_pause (Menu* menu) {
  desenha_fundo_menu_pause ();

  char tela_0_botoes[menu->numero_de_botoes[0]][40];
  strcpy(tela_0_botoes[0], "RESUME");
  strcpy(tela_0_botoes[1], "OPTIONS");
  strcpy(tela_0_botoes[2], "TITLE SCREEN");
  strcpy(tela_0_botoes[3], "QUIT GAME");

  if (menu->tela_selecionada == 0) {
  al_draw_text(menu->font_title, BRANCO, 640/2, (480/4), ALLEGRO_ALIGN_CENTRE, "PAUSE");
    for (int i = 0; i < menu->numero_de_botoes[menu->tela_selecionada] + 1; i++) {
      if (menu->botao_selecionado == i)
        al_draw_text(menu->font_items, MARROM_CLARO, 640/2, 240 + (menu->font_size + 6)*i, ALLEGRO_ALIGN_CENTRE, tela_0_botoes[i]);
      else
        al_draw_text(menu->font_items, BRANCO, 640/2, 240 + (menu->font_size + 6)*i, ALLEGRO_ALIGN_CENTRE, tela_0_botoes[i]);
    }
  }

  char tela_1_botoes[menu->numero_de_botoes[1]][20];
  strcpy(tela_1_botoes[0], "RESOLUTIONS");
  strcpy(tela_1_botoes[1], "LANGUAGES");
  strcpy(tela_1_botoes[2], "<===");

  if (menu->tela_selecionada == 1) {
  al_draw_text(menu->font_title, BRANCO, 640/2, (480/4), ALLEGRO_ALIGN_CENTRE, "PAUSE");  
    for (int i = 0; i < menu->numero_de_botoes[menu->tela_selecionada] + 1; i++) {
      if (menu->botao_selecionado == i)
        al_draw_text(menu->font_items, MARROM_CLARO, 640/2, 240 + (menu->font_size + 6)*i, ALLEGRO_ALIGN_CENTRE, tela_1_botoes[i]);
      else
        al_draw_text(menu->font_items, BRANCO, 640/2, 240 + (menu->font_size + 6)*i, ALLEGRO_ALIGN_CENTRE, tela_1_botoes[i]);
    }
  }

  char tela_2_botoes[menu->numero_de_botoes[2]][20];
  strcpy(tela_2_botoes[0], "NEW GAME");
  strcpy(tela_2_botoes[1], "QUIT GAME");

  if (menu->tela_selecionada == 2) {
  al_draw_text(menu->font_title, BRANCO, 640/2, (480/4), ALLEGRO_ALIGN_CENTRE, "GAME OVER");
    for (int i = 0; i < menu->numero_de_botoes[menu->tela_selecionada] + 1; i++) {
      if (menu->botao_selecionado == i)
        al_draw_text(menu->font_items, MARROM_CLARO, 640/2, 240 + (menu->font_size + 6)*i, ALLEGRO_ALIGN_CENTRE, tela_2_botoes[i]);
      else
        al_draw_text(menu->font_items, BRANCO, 640/2, 240 + (menu->font_size + 6)*i, ALLEGRO_ALIGN_CENTRE, tela_2_botoes[i]);
    }
  }

  char tela_3_botoes[menu->numero_de_botoes[3]][20];
  strcpy(tela_3_botoes[0], "NEW GAME");
  strcpy(tela_3_botoes[1], "HIGH SCORES");
  strcpy(tela_3_botoes[2], "QUIT GAME");

  if (menu->tela_selecionada == 3) {
  al_draw_text(menu->font_title, BRANCO, 640/2, (480/4), ALLEGRO_ALIGN_CENTRE, "space monogatari");
    for (int i = 0; i < menu->numero_de_botoes[menu->tela_selecionada] + 1; i++) {
      if (menu->botao_selecionado == i)
        al_draw_text(menu->font_items, MARROM_CLARO, 640/2, 240 + (menu->font_size + 6)*i, ALLEGRO_ALIGN_CENTRE, tela_3_botoes[i]);
      else
        al_draw_text(menu->font_items, BRANCO, 640/2, 240 + (menu->font_size + 6)*i, ALLEGRO_ALIGN_CENTRE, tela_3_botoes[i]);
    }
  }  
}    

bool loop_menu (Menu* menu, int numero_tela) {
  al_start_timer(menu->timer);
  ALLEGRO_EVENT ev;

  menu->tela_selecionada = numero_tela;
  
  bool doexit = false;
  bool redraw = true;
  
  while (!doexit) {
    al_wait_for_event(menu->event_queue, &ev);

		if (ev.type == ALLEGRO_EVENT_TIMER) {
      redraw = true;
    }

  	else if (ev.type == ALLEGRO_EVENT_KEY_DOWN) {
    	switch(ev.keyboard.keycode) {
        	case ALLEGRO_KEY_UP: 
        		  navega_botoes_cima(menu);
              break;

        	case ALLEGRO_KEY_DOWN:
           		navega_botoes_baixo(menu);
              break;

          case ALLEGRO_KEY_Z:
              //PAUSE
              if (menu->tela_selecionada == 0) {
                switch (menu->botao_selecionado) {
                  case 0:
                      return false;
                      break;
                  case 1:
                      seleciona_nova_tela(menu, 1);
                      break;
                  case 2:
                      seleciona_nova_tela(menu, 3);
                      break;                      
                  case 3:
                      return true;
                      break;
                  }
              }
              //OPTIONS
              else if (menu->tela_selecionada == 1) {
                switch (menu->botao_selecionado) {
                  case 0:
                      seleciona_nova_tela(menu, 0);
                      break;
                  case 1:
                      seleciona_nova_tela(menu, 0);
                      break;
                  case 2:
                      seleciona_nova_tela(menu, 0);
                      break;
                  }   
              }
              //GAME OVER
              else if (menu->tela_selecionada == 2) {
                switch (menu->botao_selecionado) {
                  case 0:
                      return true;
                      break;
                  case 1:
                      return true;
                      break;                        
                  }
              }
              //TITLE SCREEN
              else if (menu->tela_selecionada == 3) {
                switch (menu->botao_selecionado) {
                  case 0:
                      menu->new_game = 1;
                      return true;
                      break;
                  case 1:
                      // seleciona_nova_tela(menu, 4);
                      return true;
                      break;
                  case 2:
                      return true;
                      break;                        
                  }
              }                  
              break;

          case ALLEGRO_KEY_ESCAPE:
              return false;
              break;

      }
    }
 
    	if (redraw && al_is_event_queue_empty(menu->event_queue)) {
        	redraw = false;

          desenha_menu_pause(menu);

        	al_flip_display();
      	}
   }
}

void seleciona_nova_tela (Menu* menu, int numero_tela) {
  menu->tela_selecionada = numero_tela;
  menu->botao_selecionado = 0;
}

void navega_botoes_cima (Menu* menu) {
  if (menu->botao_selecionado == 0) {
    menu->botao_selecionado = menu->numero_de_botoes[menu->tela_selecionada];
  }
  else {
    menu->botao_selecionado--;
  }
}

void navega_botoes_baixo (Menu* menu) {
  if (menu->botao_selecionado == menu->numero_de_botoes[menu->tela_selecionada]) {
    menu->botao_selecionado = 0;
  }
  else {
    menu->botao_selecionado++;
  }
}

void inicializa_event_queue_menu_pause (Menu* menu) {
	menu->event_queue = al_create_event_queue();

	if(!menu->event_queue) {
		fprintf(stderr, "Falha em executar lista de eventos do menu!\n");
		exit(-1);
	}
  al_install_keyboard();
  al_register_event_source(menu->event_queue, al_get_keyboard_event_source());
  al_register_event_source(menu->event_queue, al_get_timer_event_source(menu->timer));
}

void inicializa_timer_menu_pause (Menu* menu) {
	menu->timer = al_create_timer(1.0/FPS);

	if(!menu->timer){
		fprintf(stderr, "Falha em executar timer do menu!\n");
		exit(-1);
	}
}