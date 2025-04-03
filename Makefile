all: compile link

compile:
	g++ -Isrc/include -c application.cpp Food.cpp

link:
	g++ application.o Food.o -o application -Lsrc/lib -lsfml-graphics -lsfml-audio -lsfml-window -lsfml-system