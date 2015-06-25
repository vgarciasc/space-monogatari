all: game.o player.o projetil.o menu.o alien.o
	g++ main.c game.o player.o projetil.o menu.o alien.o -o main -std=c++11 -lallegro -lallegro_dialog -lallegro_image -lallegro_primitives -lallegro_font -lallegro_ttf
	rm game.o
	rm player.o
	rm projetil.o
	rm menu.o
	rm alien.o
game.o:
	g++ -c game.c
player.o:
	g++ -c player.c
projetil.o:
	g++ -c projetil.c
menu.o:
	g++ -c menu.c
alien.o:
	g++ -c alien.c