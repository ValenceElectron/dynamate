FILES = main.cpp ./render/Draw.hpp ./render/Draw.cpp ./render/utils/Camera.hpp ./render/utils/Camera.cpp ./render/utils/OGLSetup.hpp ./render/utils/OGLSetup.cpp ./render/objects/DrawableObjects.hpp ./render/objects/DrawableObjects.cpp
CFLAGS = -std=c++11
LDFLAGS = -lglfw -lGLEW -lGL -lGLU -lX11

MakeMain: main.cpp
	rm -f main && g++ $(CFLAGS) $(FILES) -o main $(LDFLAGS) && clear

.PHONY: test clean

test: main
	./main

clean:
	rm -f main
