FILES = ./src/main.cpp ./src/Draw.cpp ./src/utils/Camera.cpp ./src/utils/OGLSetup.cpp ./src/render/objects/DrawableObject.cpp ./src/render/DrawableObjectManager.cpp ./src/utils/ObjectLoader.cpp ./src/render/objects/UserInterfaceElement.cpp ./src/utils/Loader.cpp ./src/utils/UserInterfaceLoader.cpp ./src/render/ResourceManager.cpp ./src/render/UserInterfaceManager.cpp
HFILES = ./src/Draw.hpp ./src/utils/Camera.hpp ./src/utils/OGLSetup.hpp ./src/render/objects/DrawableObject.hpp ./src/render/DrawableObjectManager.hpp ./src/utils/ObjectLoader.hpp ./src/render/objects/UserInterfaceElement.hpp ./src/utils/Loader.hpp ./src/utils/UserInterfaceLoader.hpp ./src/render/ResourceManager.hpp ./src/render/UserInterfaceManager.hpp
CFLAGS = -std=c++17
LDFLAGS = -lglfw -lGLEW -lGL -lGLU

MakeMain: ./src/main.cpp
	rm -f main && g++ $(CFLAGS) $(FILES) $(HFILES) -o main $(LDFLAGS) && clear

.PHONY: test clean

test: main
	./main

clean:
	rm -f main
