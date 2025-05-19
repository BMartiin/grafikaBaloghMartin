# ---- Elérési utak ----
SDL2_PATH = C:/Suli/sdl2/SDL2-devel-2.26.5-mingw/SDL2-2.26.5/i686-w64-mingw32
SDL2_IMAGE_PATH = C:/Suli/sdl2/SDL2_image-devel-2.26.5-mingw/SDL2_image-2.26.5/i686-w64-mingw32

# ---- Fordító beállítások ----
INCLUDE_DIRS = -Iinclude -I$(SDL2_PATH)/include -I$(SDL2_IMAGE_PATH)/include
LIB_DIRS = -L$(SDL2_PATH)/lib -L$(SDL2_IMAGE_PATH)/lib
LIBS = -lmingw32 -lSDL2main -lSDL2 -lSDL2_image -lopengl32 -lglu32 -lm

# ---- Fordító és fájlok ----
CC = gcc
SRC = $(wildcard src/*.c)
TARGET = gomb.exe

# ---- Célszabályok ----
all: $(TARGET)

$(TARGET): $(SRC)
	$(CC) $(SRC) $(INCLUDE_DIRS) $(LIB_DIRS) -o $(TARGET) $(LIBS)

clean:
	del /Q $(TARGET)

run: all
	$(TARGET)
