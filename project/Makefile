# ---- Elérési utak ----
SDL2_PATH = C:/Suli/sdl2/SDL2-devel-2.26.5-mingw/SDL2-2.26.5/i686-w64-mingw32

INCLUDE_DIRS = -Iinclude -I$(SDL2_PATH)/include
LIB_DIRS = -L$(SDL2_PATH)/lib
LIBS = -lmingw32 -lSDL2main -lSDL2 -lopengl32 -lm

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
