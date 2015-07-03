#ifndef CONFIG_H
#define CONFIG_H

#define LARGURA_DISPLAY 800
#define ALTURA_DISPLAY 600
#define BARREIRA_LATERAL_DISPLAY 15
#define SCALE_BITMAPS true

//CORES
#define MARROM_ESCURO al_map_rgb(20, 20, 12)
#define MARROM_CLARO al_map_rgb(247, 180, 109)
#define AMARELO al_map_rgb(255, 180, 0)
#define BRANCO al_map_rgb(255, 255, 255)
#define CINZA al_map_rgb(211, 211, 211)
#define VERDE al_map_rgb(0, 250, 0)

//INPUT
#define N_KEYS 8
enum MYKEYS { KEY_UP, KEY_DOWN, KEY_LEFT, KEY_RIGHT, KEY_Z, KEY_ESCAPE, KEY_ENTER, KEY_SPACE };

//DIRECAO
enum MOVIMENTO { COM_INERCIA, SEM_INERCIA };
enum DIRECAO { ESQUERDA = -1, DIREITA = 1, CIMA, BAIXO, PARADA = 0};
enum MODO_DE_JOGO { CLASSIC, INFINITE };

//PONTOS
#define PONTOS_MOTHERSHIP 500
#define PONTOS_ALIEN 200

//MENU
#define MENU_FPS 10
#define MAX_BOTOES 32
#define GAME_FPS 60
#define N_TELAS 14
enum TELA { PAUSE, OPTIONS, GAME_OVER, TITLE_SCREEN, RESOLUTIONS, LANGUAGES, MECHANICS, MODES, INSTRUCTIONS, SUBMIT_SCORE, HIGH_SCORES, PLAYER_MOVEMENT };

//ALIEN
#define LARGURA_SPRITES_ALIEN 28
#define ALTURA_SPRITES_ALIEN 28
#define LINHAS_TROPA 5
#define COLUNAS_TROPA 10
#define DISTANCIA_PASSO_ALIEN 20

//MOTHERSHIP
#define LARGURA_MOTHERSHIP 32
#define ALTURA_MOTHERSHIP 32
#define FREQUENCIA_MOTHERSHIP 15
#define VELOCIDADE_MOTHERSHIP 3

//PLAYER
#define LARGURA_PLAYER 48
#define ALTURA_PLAYER 48
#define NUMERO_VIDAS 3
#define DISTANCIA_PASSO_PLAYER 1

//PROJETIL
#define LARGURA_PROJETIL 8
#define ALTURA_PROJETIL 16
#define PROJETIL_COOLDOWN 20
#define VELOCIDADE_PROJETIL 15
#define MAX_PROJETEIS 32

//SHIELD
#define LARGURA_SHIELD 96
#define ALTURA_SHIELD 48
#define NUMERO_SHIELDS 4
#define PARTES_X 4
#define PARTES_Y 2
enum ESTADO { INTEIRO, DANIFICADO, DESTRUIDO };

#endif
