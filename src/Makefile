FILES = main.cpp ./utils/OGLSetup.hpp ./utils/OGLSetup.cpp ./utils/Camera.hpp ./utils/Camera.cpp
CFLAGS = -std=c++11
LDFLAGS = -lglfw -lGLEW -lGL -lGLU -lX11

MakeMain: main.cpp
	g++ $(CFLAGS) $(FILES) -o main $(LDFLAGS)

.PHONY: test clean

test: main
	./main

clean:
	rm -f main
