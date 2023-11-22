FILES = ./src/main.cpp ./src/Draw.hpp ./src/Draw.cpp ./src/utils/Camera.hpp ./src/utils/Camera.cpp ./src/utils/OGLSetup.hpp ./src/utils/OGLSetup.cpp ./src/utils/objects/DrawableObject.hpp ./src/utils/objects/DrawableObject.cpp ./src/utils/DrawableObjectManager.hpp ./src/utils/DrawableObjectManager.cpp ./src/utils/ObjectLoader.hpp ./src/utils/ObjectLoader.cpp
CFLAGS = -std=c++17
LDFLAGS = -lglfw -lGLEW -lGL -lGLU

MakeMain: ./src/main.cpp
	rm -f main && g++ $(CFLAGS) $(FILES) -o main $(LDFLAGS) && clear

.PHONY: test clean

test: main
	./main

clean:
	rm -f main
