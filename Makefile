all: compile link run

compile:
	g++ -Isrc/include -c main.cpp bola.cpp

link:
	g++ main.o bola.o -o main -Lsrc/lib -lsfml-graphics -lsfml-window -lsfml-system -lopengl32

run:
	./main