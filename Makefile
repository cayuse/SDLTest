## windows shit.. that i con't care about and won't ever be fixing
ifeq ($(OS),Windows_NT)
		CCFLAGS += -D WIN32
		ifeq ($(PROCESSOR_ARCHITECTURE),AMD64)
				CCFLAGS += -D AMD64
		endif
		ifeq ($(PROCESSOR_ARCHITECTURE),x86)
				CCFLAGS += -D IA32
		endif
else
CXX = clang++
		UNAME_S := $(shell uname -s)
		ifeq ($(UNAME_S),Linux)
				SDL = `pkg-config --cflags --libs sdl2` -lSDL2_image
				SDL_INCLUDE = `pkg-config --cflags --libs sdl2`
		endif
		ifeq ($(UNAME_S),Darwin)
				SDL = -framework SDL2
				SDL_INCLUDE = -I "/Library/Frameworks/SDL2.framework/Headers/"
        SDL_INCLUDE += -I "/Library/Frameworks/SDL2_image.framework/Headers/"
		endif
CXXFLAGS = -Wall -c -std=c++11 $(SDL_INCLUDE)
LDFLAGS = $(SDL)
endif

EXE = SDLTestapp

all: $(EXE)

$(EXE): SDLTest.o 
	$(CXX) $(LDFLAGS) $< -o $@

main.o: SDLTest.cpp
	$(CXX) $(CXXFLAGS) $< -o $@

clean:
	rm *.o && rm $(EXE)
