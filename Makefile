FILES = ./src/main.cpp ./src/render/Draw.hpp ./src/render/Draw.cpp ./src/render/utils/Camera.hpp ./src/render/utils/Camera.cpp ./src/render/utils/OGLSetup.hpp ./src/render/utils/OGLSetup.cpp ./src/render/objects/DrawableObject.hpp ./src/render/objects/DrawableObject.cpp ./src/render/utils/DrawableObjectManager.hpp ./src/render/utils/DrawableObjectManager.cpp ./src/render/utils/ObjectLoader.hpp ./src/render/utils/ObjectLoader.cpp
CFLAGS = -std=c++17
LDFLAGS = -lglfw -lGLEW -lGL -lGLU

MakeMain: ./src/main.cpp
	rm -f main && g++ $(CFLAGS) $(FILES) -o main $(LDFLAGS) && clear

.PHONY: test clean

test: main
	./main

clean:
	rm -f main
