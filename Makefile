CC=clang++
CXXFLAGS=-g -std=c++17
DEBUGFLAGS=-D GIZMOS

INCLUDES=-I./external_includes/ -I./include/ 
LIBS=

CORESRC=src/core/*.cpp src/core/*/*.cpp
GAMESRC=src/game/*.cpp

GAMENAME=creative-refresh-platformer

ifeq ($(OS),Windows_NT)     # is Windows_NT on XP, 2000, 7, Vista, 10...
	CC       :=g++
	CXXFLAGS :=-D MINGW $(CXXFLAGS) -static-libgcc -static-libstdc++
	LIBS     +=-lmingw32 -lSDL2main -lSDL2 -lSDL2_ttf -lSDL_image -mwindows -L libwinpthread-1.dll
	GAMENAME :=$(GAMENAME).exe
else ifeq ($(shell uname -s),Darwin)     # is MACOSX
	CXXFLAGS :=-D MAC $(CXXFLAGS)
	LIBS     +=-F/Library/Frameworks -framework SDL2 -framework SDL2_ttf -framework SDL2_image
	INCLUDES +=-I/Library/Frameworks/SDL2.framework/Headers -I/Library/Frameworks/SDL2_ttf.framework/Headers -I/Library/Frameworks/SDL2_image.framework/Headers
	GAMENAME :=$(GAMENAME).out
else
	CXXFLAGS :=-D LINUX $(CXXFLAGS)
	LIBS     +=-lSDL2 -lSDL2_ttf -lSDL2_image -ldl
	GAMENAME +=.out
	GAMENAME :=$(GAMENAME).out
endif

all: game

game:
	$(CC) $(CXXFLAGS) -o $(GAMENAME) $(INCLUDES) $(CORESRC) $(GAMESRC) $(LIBS)

debug:
	$(CC) $(CXXFLAGS) $(DEBUGFLAGS) -o $(GAMENAME) $(INCLUDES) $(CORESRC) $(GAMESRC) $(LIBS)

RM=rm -rf
ifeq ($(OS),Windows_NT)     # is Windows_NT on XP, 2000, 7, Vista, 10...
	RM:=del
endif

fmt:
	clang-format -i include/*/*.h include/*/*.hpp include/*/*/*.hpp src/*/*.cpp src/*/*/*.cpp

clean:
	$(RM) *.dSYM .DS_Store **/.DS_Store **/*.o *.out *.exe
