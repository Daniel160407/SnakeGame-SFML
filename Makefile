all: compile link

compile:
	g++ -Isrc/include -c application.cpp Food.cpp Snake.cpp Game.cpp

link:
	g++ application.o Food.o Snake.o Game.o -o application -Lsrc/lib -lsfml-graphics -lsfml-audio -lsfml-window -lsfml-system