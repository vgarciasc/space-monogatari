#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <allegro5/allegro.h>
#include <allegro5/allegro_primitives.h>

#include "menu.h"

void inicializa_menus (Menu* menu) {
    menu->event_queue = NULL;
    menu->timer = NULL;

    inicializa_timer_menu_pause (menu);
    inicializa_event_queue_menu_pause(menu);

    menu->botao_selecionado = 0;

    menu->numero_de_botoes[0] = 3;
    menu->numero_de_botoes[1] = 3;
    menu->numero_de_botoes[2] = 1;
    menu->numero_de_botoes[3] = 2;
    menu->numero_de_botoes[4] = 3;
    menu->numero_de_botoes[5] = 3;
    menu->numero_de_botoes[6] = 2;

    menu->font_size = 24;
    menu->font_title = al_load_font("resources/acknowledge.ttf", menu->font_size*2, 0);
    menu->font_items = al_load_font("resources/acknowledge.ttf", menu->font_size, 0);

    if (menu->font_title == NULL || menu->font_items == NULL) {
        puts("Erro ao carregar o arquivo \"resources/acknowledge.ttf\"");
        exit(0);
    }

    for(int i = 0; i < N_KEYS; i++)
        menu->key[i] = false;
}

void desenha_fundo_menu_pause () {
	al_clear_to_color(MARROM_ESCURO);
}

void desenha_menu_pause (Menu* menu) {
    desenha_fundo_menu_pause ();

    //PAUSE
    char tela_0_botoes[menu->numero_de_botoes[0]][MAX_BOTOES];
    strcpy(tela_0_botoes[0], "RESUME");
    strcpy(tela_0_botoes[1], "OPTIONS");
    strcpy(tela_0_botoes[2], "TITLE SCREEN");
    strcpy(tela_0_botoes[3], "QUIT GAME");

    if (menu->tela_selecionada == 0) {
        al_draw_text(menu->font_title, BRANCO, LARGURA_DISPLAY/2, (ALTURA_DISPLAY/4), ALLEGRO_ALIGN_CENTRE, "PAUSE");

        for (int i = 0; i < menu->numero_de_botoes[menu->tela_selecionada] + 1; i++) {
            if (menu->botao_selecionado == i)
                al_draw_text(menu->font_items, MARROM_CLARO, LARGURA_DISPLAY/2, ALTURA_DISPLAY/2 + (menu->font_size + 6)*i, ALLEGRO_ALIGN_CENTRE, tela_0_botoes[i]);
            else
                al_draw_text(menu->font_items, BRANCO, LARGURA_DISPLAY/2, ALTURA_DISPLAY/2 + (menu->font_size + 6)*i, ALLEGRO_ALIGN_CENTRE, tela_0_botoes[i]);
        }
    }

    //PAUSE
    char tela_1_botoes[menu->numero_de_botoes[1]][MAX_BOTOES];
    strcpy(tela_1_botoes[0], "RESOLUTIONS");
    strcpy(tela_1_botoes[1], "LANGUAGES");
    strcpy(tela_1_botoes[2], "MECHANICS");
    strcpy(tela_1_botoes[3], "<===");

    if (menu->tela_selecionada == 1) {
        al_draw_text(menu->font_title, BRANCO, LARGURA_DISPLAY/2, (ALTURA_DISPLAY/4), ALLEGRO_ALIGN_CENTRE, "PAUSE");

        for (int i = 0; i < menu->numero_de_botoes[menu->tela_selecionada] + 1; i++) {
            if (menu->botao_selecionado == i)
                al_draw_text(menu->font_items, MARROM_CLARO, LARGURA_DISPLAY/2, ALTURA_DISPLAY/2 + (menu->font_size + 6)*i, ALLEGRO_ALIGN_CENTRE, tela_1_botoes[i]);
            else
                al_draw_text(menu->font_items, BRANCO, LARGURA_DISPLAY/2, ALTURA_DISPLAY/2 + (menu->font_size + 6)*i, ALLEGRO_ALIGN_CENTRE, tela_1_botoes[i]);
        }
    }

    //GAME_OVER
    char tela_2_botoes[menu->numero_de_botoes[2]][MAX_BOTOES];
    strcpy(tela_2_botoes[0], "NEW GAME");
    strcpy(tela_2_botoes[1], "QUIT GAME");

    if (menu->tela_selecionada == 2) {
        al_draw_text(menu->font_title, BRANCO, LARGURA_DISPLAY/2, (ALTURA_DISPLAY/4), ALLEGRO_ALIGN_CENTRE, "GAME OVER");

        for (int i = 0; i < menu->numero_de_botoes[menu->tela_selecionada] + 1; i++) {
            if (menu->botao_selecionado == i)
                al_draw_text(menu->font_items, MARROM_CLARO, LARGURA_DISPLAY/2, ALTURA_DISPLAY/2 + (menu->font_size + 6)*i, ALLEGRO_ALIGN_CENTRE, tela_2_botoes[i]);
            else
                al_draw_text(menu->font_items, BRANCO, LARGURA_DISPLAY/2, ALTURA_DISPLAY/2 + (menu->font_size + 6)*i, ALLEGRO_ALIGN_CENTRE, tela_2_botoes[i]);
        }
    }

    //TITLE_SCREEN
    char tela_3_botoes[menu->numero_de_botoes[3]][MAX_BOTOES];
    strcpy(tela_3_botoes[0], "NEW GAME");
    strcpy(tela_3_botoes[1], "HIGH SCORES");
    strcpy(tela_3_botoes[2], "QUIT GAME");

    if (menu->tela_selecionada == 3) {
        al_draw_text(menu->font_title, BRANCO, LARGURA_DISPLAY/2, (ALTURA_DISPLAY/4), ALLEGRO_ALIGN_CENTRE, "space monogatari");
    
        for (int i = 0; i < menu->numero_de_botoes[menu->tela_selecionada] + 1; i++) {
            if (menu->botao_selecionado == i)
                al_draw_text(menu->font_items, MARROM_CLARO, LARGURA_DISPLAY/2, ALTURA_DISPLAY/2 + (menu->font_size + 6)*i, ALLEGRO_ALIGN_CENTRE, tela_3_botoes[i]);
            else
                al_draw_text(menu->font_items, BRANCO, LARGURA_DISPLAY/2, ALTURA_DISPLAY/2 + (menu->font_size + 6)*i, ALLEGRO_ALIGN_CENTRE, tela_3_botoes[i]);
        }
    } 

    //RESOLUTIONS
    char tela_4_botoes[menu->numero_de_botoes[4]][MAX_BOTOES];
    strcpy(tela_4_botoes[0], "640 x 480");
    strcpy(tela_4_botoes[1], "800 x 600");
    strcpy(tela_4_botoes[2], "1024 x 768");
    strcpy(tela_4_botoes[3], "<===");

    if (menu->tela_selecionada == 4) {
        al_draw_text(menu->font_title, BRANCO, LARGURA_DISPLAY/2, (ALTURA_DISPLAY/4), ALLEGRO_ALIGN_CENTRE, "RESOLUTIONS");
    
        for (int i = 0; i < menu->numero_de_botoes[menu->tela_selecionada] + 1; i++) {
            if (menu->botao_selecionado == i)
                al_draw_text(menu->font_items, MARROM_CLARO, LARGURA_DISPLAY/2, ALTURA_DISPLAY/2 + (menu->font_size + 6)*i, ALLEGRO_ALIGN_CENTRE, tela_4_botoes[i]);
            else
                al_draw_text(menu->font_items, BRANCO, LARGURA_DISPLAY/2, ALTURA_DISPLAY/2 + (menu->font_size + 6)*i, ALLEGRO_ALIGN_CENTRE, tela_4_botoes[i]);
        }
    }  

    //LANGUAGES
    char tela_5_botoes[menu->numero_de_botoes[5]][MAX_BOTOES];
    strcpy(tela_5_botoes[0], "PORTUGUESE");
    strcpy(tela_5_botoes[1], "ENGLISH");
    strcpy(tela_5_botoes[2], "CHINESE (ORIENTAL MANDARIN)");
    strcpy(tela_5_botoes[3], "<===");

    if (menu->tela_selecionada == 5) {
        al_draw_text(menu->font_title, BRANCO, LARGURA_DISPLAY/2, (ALTURA_DISPLAY/4), ALLEGRO_ALIGN_CENTRE, "LANGUAGES");
    
        for (int i = 0; i < menu->numero_de_botoes[menu->tela_selecionada] + 1; i++) {
            if (menu->botao_selecionado == i)
                al_draw_text(menu->font_items, MARROM_CLARO, LARGURA_DISPLAY/2, ALTURA_DISPLAY/2 + (menu->font_size + 6)*i, ALLEGRO_ALIGN_CENTRE, tela_5_botoes[i]);
            else
                al_draw_text(menu->font_items, BRANCO, LARGURA_DISPLAY/2, ALTURA_DISPLAY/2 + (menu->font_size + 6)*i, ALLEGRO_ALIGN_CENTRE, tela_5_botoes[i]);
        }
    }  

    //MECHANICS
    char tela_6_botoes[menu->numero_de_botoes[6]][MAX_BOTOES];
    strcpy(tela_6_botoes[0], "ALIEN MOVEMENT");
    strcpy(tela_6_botoes[1], "PLAYER MOVEMENT");
    strcpy(tela_6_botoes[2], "<===");

    if (menu->tela_selecionada == 6) {
        al_draw_text(menu->font_title, BRANCO, LARGURA_DISPLAY/2, (ALTURA_DISPLAY/4), ALLEGRO_ALIGN_CENTRE, "MECHANICS");
    
        for (int i = 0; i < menu->numero_de_botoes[menu->tela_selecionada] + 1; i++) {
            if (menu->botao_selecionado == i)
                al_draw_text(menu->font_items, MARROM_CLARO, LARGURA_DISPLAY/2, ALTURA_DISPLAY/2 + (menu->font_size + 6)*i, ALLEGRO_ALIGN_CENTRE, tela_6_botoes[i]);
            else
                al_draw_text(menu->font_items, BRANCO, LARGURA_DISPLAY/2, ALTURA_DISPLAY/2 + (menu->font_size + 6)*i, ALLEGRO_ALIGN_CENTRE, tela_6_botoes[i]);
        }
    }  
}    

bool loop_menu (Menu* menu, TELA tela) {
    al_start_timer(menu->timer);
    ALLEGRO_EVENT ev;

    menu->tela_selecionada = tela;

    bool doexit = false;
    bool redraw = true;

    while (!doexit) {
        al_wait_for_event(menu->event_queue, &ev);

        if (ev.type == ALLEGRO_EVENT_TIMER)
            redraw = true;

        else if (ev.type == ALLEGRO_EVENT_KEY_DOWN) {
            switch(ev.keyboard.keycode) {

                case ALLEGRO_KEY_UP:
                    navega_botoes(menu, CIMA);
                    break;

                case ALLEGRO_KEY_DOWN:
                    navega_botoes(menu, BAIXO);
                    break;

                case ALLEGRO_KEY_ENTER: case ALLEGRO_KEY_Z:
                    switch (menu->tela_selecionada) {
                        case PAUSE:
                            switch (menu->botao_selecionado) {
                                case 0:
                                    return false;
                                    break;
                                case 1:
                                    seleciona_nova_tela(menu, OPTIONS);
                                    break;
                                case 2:
                                    seleciona_nova_tela(menu, TITLE_SCREEN);
                                    break;                      
                                case 3:
                                    return true;
                                    break;
                            }
                            break;

                        case OPTIONS:
                            switch (menu->botao_selecionado) {
                                case 0:
                                    seleciona_nova_tela(menu, RESOLUTIONS);
                                    break;
                                case 1:
                                    seleciona_nova_tela(menu, LANGUAGES);
                                    break;
                                case 2:
                                    seleciona_nova_tela(menu, MECHANICS);
                                    break;
                                case 3:
                                    seleciona_nova_tela(menu, PAUSE);
                                    break;
                            }  
                            break;

                        case GAME_OVER:
                            switch (menu->botao_selecionado) {
                                case 0:
                                    menu->new_game = 1;
                                    return true;
                                    break;
                                case 1:
                                    return true;
                                    break;                        
                            }
                            break;

                        case TITLE_SCREEN:
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
                            break;

                        case RESOLUTIONS:
                            switch (menu->botao_selecionado) {
                                case 0:
                                    menu->new_game = 1;
                                    return true;
                                    break;
                                case 1:
                                    return true;
                                    break;
                                case 2:
                                    return true;
                                    break;
                                case 3:
                                    seleciona_nova_tela(menu, OPTIONS);
                                    break;   
                            } 
                            break;

                        case LANGUAGES:
                            switch (menu->botao_selecionado) {
                                case 0:
                                    menu->new_game = 1;
                                    return true;
                                    break;
                                case 1:
                                    return true;
                                    break;
                                case 2:
                                    return true;
                                    break;
                                case 3:
                                    seleciona_nova_tela(menu, OPTIONS);
                                    break;   
                            } 
                            break;

                        case MECHANICS:
                            switch (menu->botao_selecionado) {
                                case 0:
                                    menu->new_game = 1;
                                    return true;
                                    break;
                                case 1:
                                    return true;
                                    break;
                                case 2:
                                    seleciona_nova_tela(menu, OPTIONS);
                                    break;
                            } 
                            break;              
                    }
                    break; break;
            }                  
        }

        // else if (ev.type == ALLEGRO_EVENT_KEY_DOWN) {
        //     switch(ev.keyboard.keycode) {
        //         case ALLEGRO_KEY_UP: 
        //             menu->key[KEY_UP] = true;
        //             break;

        //         case ALLEGRO_KEY_DOWN:
        //             menu->key[KEY_DOWN] = true;
        //             break;

        //         case ALLEGRO_KEY_Z:
        //             menu->key[KEY_Z] = true;
        //             break;

        //         case ALLEGRO_KEY_ENTER:
        //             menu->key[KEY_ENTER] = true;
        //             break;
        //     }
        // }

        // else if (ev.type == ALLEGRO_EVENT_KEY_UP) {
        //     switch(ev.keyboard.keycode) {
        //         case ALLEGRO_KEY_UP: 
        //             menu->key[KEY_UP] = false;
        //             break;

        //         case ALLEGRO_KEY_DOWN:
        //             menu->key[KEY_DOWN] = false;
        //             break;

        //         case ALLEGRO_KEY_Z:
        //             menu->key[KEY_Z] = false;
        //             break;

        //         case ALLEGRO_KEY_ENTER:
        //             menu->key[KEY_ENTER] = false;
        //             break;
        //     }
        // }

        if (redraw && al_is_event_queue_empty(menu->event_queue)) {
           redraw = false;

           desenha_menu_pause(menu);

           al_flip_display();
        }
    }
}

void seleciona_nova_tela (Menu* menu, TELA tela) {
    menu->tela_selecionada = tela;
    menu->botao_selecionado = 0;
}

void navega_botoes (Menu* menu, DIRECAO direcao) {
    if (direcao == CIMA) {
        if (menu->botao_selecionado == 0)
            menu->botao_selecionado = menu->numero_de_botoes[menu->tela_selecionada];
        else
            menu->botao_selecionado--;
    }

    if (direcao == BAIXO) {
        if (menu->botao_selecionado == menu->numero_de_botoes[menu->tela_selecionada])
            menu->botao_selecionado = 0;
        else
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
	menu->timer = al_create_timer(1.0/MENU_FPS);

	if(!menu->timer){
		fprintf(stderr, "Falha em executar timer do menu!\n");
		exit(-1);
	}
}