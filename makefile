all: game.o player.o projetil.o
	g++ main.c game.o player.o projetil.o -o main -std=c++11 -lallegro -lallegro_dialog -lallegro_image -lallegro_primitives
	rm game.o
	rm player.o
	rm projetil.o
game.o:
	g++ -c game.c
player.o:
	g++ -c player.c
projetil.o:
	g++ -c projetil.c