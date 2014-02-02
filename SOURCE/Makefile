CC=g++

INCLUDES_FRAMEWORKS=-I./lunENG/ -I./lunENG/Frameworks/linux/include -I./lunENG/Frameworks/glm

INCLUDES_CODE=-I./lunENG/core \
		-I./lunENG/GLutils \
		-I./lunENG/input \
		-I./lunENG/modules \
		-I./lunENG/shared \
		-I./lunENG/utils

CFLAGS=$(INCLUDES_FRAMEWORKS) $(INCLUDES_CODE)
LDFLAGS=-lSDL2 -lSDL2_image -lSDL2_ttf -lGL -lGLU -lGLEW


CFLAGS+=-Wall -Wextra -Winit-self -Woverloaded-virtual -Wuninitialized -Wint-to-pointer-cast -Weffc++ -O3 -std=c++11 -msse3


SOURCES=./lunENG/core/main.cpp ./lunENG/core/renderer.cpp ./lunENG/core/tools.cpp \
	./lunENG/GLutils/drawfont.cpp ./lunENG/GLutils/GLstuff.cpp ./lunENG/GLutils/shader.cpp ./lunENG/GLutils/sprites.cpp \
	./lunENG/input/keys.cpp \
	./lunENG/modules/freecam.cpp ./lunENG/modules/terrain.cpp \
	./lunENG/shared/OBJparser.cpp ./lunENG/shared/shared.cpp \
	./lunENG/utils/INIparser.cpp ./lunENG/utils/SDLgraph.cpp ./lunENG/utils/setup.cpp
 
EXECUTABLE=luna

all: $(EXECUTABLE)

$(EXECUTABLE): $(SOURCES)
	$(CC) $(CFLAGS) $(LDFLAGS) -o $(EXECUTABLE) $(SOURCES) 
