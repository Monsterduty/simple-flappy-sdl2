flappy: main.cpp

	g++ main.cpp -lSDL2 -lSDL2_image -lSDL2_ttf -lSDL2_mixer -o flappy

withDeps: main.cpp
	
		g++ main.cpp -I deps/SDL2/include/SDL2 -L deps/SDL2/lib -lSDL2 -lSDL2_image -lSDL2_ttf -lSDL2_mixer -o flappy
