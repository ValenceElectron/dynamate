FILES = ./src/main.cpp ./src/Draw.hpp ./src/Draw.cpp ./src/utils/Camera.hpp ./src/utils/Camera.cpp ./src/utils/OGLSetup.hpp ./src/utils/OGLSetup.cpp ./src/render/objects/DrawableObject.hpp ./src/render/objects/DrawableObject.cpp ./src/render/DrawableObjectManager.hpp ./src/render/DrawableObjectManager.cpp ./src/utils/ObjectLoader.hpp ./src/utils/ObjectLoader.cpp ./src/render/objects/UserInterfaceElement.hpp ./src/render/objects/UserInterfaceElement.cpp ./src/utils/Loader.hpp ./src/utils/Loader.cpp ./src/utils/UILoader.hpp ./src/utils/UILoader.cpp
CFLAGS = -std=c++17
LDFLAGS = -lglfw -lGLEW -lGL -lGLU

MakeMain: ./src/main.cpp
	rm -f main && g++ $(CFLAGS) $(FILES) -o main $(LDFLAGS) && clear

.PHONY: test clean

test: main
	./main

clean:
	rm -f main
