all: compile link

compile:
	g++ -Isrc/include -c application.cpp

link:
	g++ application.o -o application -Lsrc/lib -lsfml-graphics -lsfml-window -lsfml-system