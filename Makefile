GRIDSOURCE = src/core/grid.cpp
GUISOURCE = src/gui/gui.cpp
CC = g++

all:
	$(CC) -L./SFML/lib -I./SFML/include $(GRIDSOURCE) -o test.exe -lsfml-graphics -lsfml-window -lsfml-system -DSFML_STATIC

gui:
	$(CC) -L./SFML/lib -std=c++11 -I./SFML/include $(GUISOURCE) -o SFML/test.exe -lsfml-graphics -lsfml-window -lsfml-system -DSFML_STATIC -g

startg:
	./SFML/test
