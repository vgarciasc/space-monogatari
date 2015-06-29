<<<<<<< HEAD
all: game.o player.o projetil.o menu.o alien.o mothership.o hud.o shield.o
	g++ main.cpp game.o player.o projetil.o menu.o alien.o mothership.o hud.o shield.o -o main -g -std=c++11 -lallegro -lallegro_image -lallegro_primitives -lallegro_font -lallegro_ttf
=======
all: game.o player.o projetil.o menu.o alien.o mothership.o hud.o
	g++ main.cpp game.o player.o projetil.o menu.o alien.o mothership.o hud.o -o main -g -std=c++11 -lallegro -lallegro_image -lallegro_primitives -lallegro_font -lallegro_ttf
>>>>>>> 00a5a2ad6cdbba4eaf3f3c8ef5aab7000430e263
	rm game.o
	rm player.o
	rm projetil.o
	rm menu.o
	rm alien.o
	rm mothership.o
	rm hud.o
<<<<<<< HEAD
	rm shield.o
=======
>>>>>>> 00a5a2ad6cdbba4eaf3f3c8ef5aab7000430e263
game.o:
	g++ -c game.cpp
player.o:
	g++ -c player.cpp
projetil.o:
	g++ -c projetil.cpp
menu.o:
	g++ -c menu.cpp
alien.o:
	g++ -c alien.cpp
mothership.o:
	g++ -c mothership.cpp
hud.o:
<<<<<<< HEAD
	g++ -c hud.cpp
shield.o:
	g++ -c shield.cpp
=======
	g++ -c hud.cpp
>>>>>>> 00a5a2ad6cdbba4eaf3f3c8ef5aab7000430e263
