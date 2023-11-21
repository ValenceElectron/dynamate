FILES = main.cpp ./render/Draw.hpp ./render/Draw.cpp ./render/utils/Camera.hpp ./render/utils/Camera.cpp ./render/utils/OGLSetup.hpp ./render/utils/OGLSetup.cpp ./render/objects/DrawableObject.hpp ./render/objects/DrawableObject.cpp ./render/utils/DrawableObjectManager.hpp ./render/utils/DrawableObjectManager.cpp ./render/utils/ObjectLoader.hpp ./render/utils/ObjectLoader.cpp
CFLAGS = -std=c++17
LDFLAGS = -lglfw -lGLEW -lGL -lGLU

MakeMain: main.cpp
	rm -f main && g++ $(CFLAGS) $(FILES) -o main $(LDFLAGS) && clear

.PHONY: test clean

test: main
	./main

clean:
	rm -f main
