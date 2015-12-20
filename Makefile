MAIN				= SDLTest

CXX					= clang++
CFLAGS				= -std=c++11 -Wall -O3
LDFLAGS				= 
OBJDIR				= build
SRCDIR				= src

PKG_CONFIG			= pkg-config
PKG_CONFIG_PKGS		= sdl2 SDL2_image

SDL2_CFLAGS			:= $(shell $(PKG_CONFIG) $(PKG_CONFIG_PKGS) --cflags)
SDL2_LDFLAGS		:= $(shell $(PKG_CONFIG) $(PKG_CONFIG_PKGS) --libs)

ifeq ($(strip $(SDL2_CFLAGS)),)
	ifeq ($(strip $(SDL2_LDFLAGS)),)
		# if pkg-config doesn't exist or the packages aren't found, we'll
		# end up with these variables blank.
		
		# on Mac OS X, fall back to trying a framework.
		ifeq ($(shell uname -s),Darwin)
			SDL2_CFLAGS		= -DUSING_OSX_FRAMEWORKS=1
			SDL2_LDFLAGS	= -framework SDL2 -framework SDL2_image
		endif
	endif
endif

CFLAGS += $(SDL2_CFLAGS)
LDFLAGS += $(SDL2_LDFLAGS)

all: $(MAIN)

# include dependency info generated by compiler
-include $(OBJDIR)/*.d

$(MAIN): $(OBJDIR)/SDLTest.cpp.o 
	$(CXX) $(LDFLAGS) $< -o $@

$(OBJDIR)/%.cpp.o: $(SRCDIR)/%.cpp $(OBJDIR)
	$(CXX) $(CFLAGS) -MMD -c $< -o $@

$(OBJDIR):
	mkdir $(OBJDIR)

clean:
	rm -f $(MAIN)
	rm -Rf $(OBJDIR)
