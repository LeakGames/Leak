GRIDSOURCE = src/core/grid.cpp
GUISOURCE = src/gui/gui.cpp
CC = g++

all:
	$(CC) -L./SFML/lib -I./SFML/include $(GRIDSOURCE) -o test.exe -lsfml-graphics -lsfml-window -lsfml-system -DSFML_STATIC

gui:
	$(CC) $(GUISOURCE) -o gui -lsfml-graphics -lsfml-window -lsfml-system -DSFML_STATIC -lboost_thread

startg:
	./gui
