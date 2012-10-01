SOURCE = grid.cpp

all:
	g++ -L./SFML/lib -I./SFML/include $(SOURCE) -o test.exe -lsfml-graphics -lsfml-window -lsfml-system -DSFML_STATIC
