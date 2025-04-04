all: compile link

compile:
	g++ -Isrc/include -c application.cpp Food.cpp Snake.cpp Game.cpp Wall.cpp WallsGenerator.cpp

link:
	g++ application.o Food.o Snake.o Game.o Wall.o WallsGenerator.o -o application -Lsrc/lib -lsfml-graphics -lsfml-audio -lsfml-window -lsfml-system