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
        CCFLAGS += -D LINUX
				SDL = --libs sdl2 -lSDL2_image
    endif
    ifeq ($(UNAME_S),Darwin)
        SDL = -framework SDL2
    endif
CXXFLAGS = -Wall -c -std=c++11
LDFLAGS = $(SDL)
endif

EXE = SDLTest

all: $(EXE)

$(EXE): SDLTest.o 
	$(CXX) $(LDFLAGS) $< -o $@

main.o: SDLTest.cpp
	$(CXX) $(CXXFLAGS) $< -o $@

clean:
	rm *.o && rm $(EXE)
