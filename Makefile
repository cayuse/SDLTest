CXX = clang++
SDL = -framework SDL2
# If your compiler is a bit older you may need to change -std=c++11 to -std=c++0x
CXXFLAGS = -Wall -c -std=c++11
LDFLAGS = $(SDL)
EXE = SDLTest

all: $(EXE)

$(EXE): SDLTest.o 
	$(CXX) $(LDFLAGS) $< -o $@

main.o: SDLTest.cpp
	$(CXX) $(CXXFLAGS) $< -o $@

clean:
	rm *.o && rm $(EXE)
