GRIDSOURCE = src/core/grid.cpp
GUISOURCE = src/gui/gui.cpp
CC = g++

all:
	$(CC) -L./SFML/lib -I./SFML/include $(GRIDSOURCE) -o test.exe -lsfml-graphics -lsfml-window -lsfml-system -DSFML_STATIC

gui:
	$(CC) -L./SFML/lib -L./libs -I./SFML/include -I./boost $(GUISOURCE) -o SFML/test.exe -lsfml-graphics -lsfml-window -lsfml-system -lboost_thread -lboost_system -DSFML_STATIC -g

asd:
	$(CC) -L./SFML/lib -I./SFML/include asd.cpp -o SFML/test.exe -lsfml-graphics -lsfml-window -lsfml-system -DSFML_STATIC

startg:
	./SFML/test
