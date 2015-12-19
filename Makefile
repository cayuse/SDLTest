MAIN				= SDLTest

CXX					= clang++
LDFLAGS				= 
OBJDIR				= build
SRCDIR				= src

PKG_CONFIG			= pkg-config
PKG_CONFIG_PKGS		= sdl2 SDL2_image

SDL2_CFLAGS			:= $(shell $(PKG_CONFIG) $(PKG_CONFIG_PKGS) --cflags)
SDL2_LDFLAGS		:= $(shell $(PKG_CONFIG) $(PKG_CONFIG_PKGS) --libs)

ifeq ($(strip $(SDL2_CFLAGS)),)
	ifeq ($(strip $(SDL2_LDFLAGS)),)
		# if pkg-config doesn't exist or the packags aren't found, we'll
		# end up with these variables blank.
		
		# on Mac OS X, fall back to trying a framework.
		ifeq ($(shell uname -s),Darwin)
			SDL2_CFLAGS = -framework SDL2 -framework SDL2_image
			SDL2_LDFLAGS = $(SDL2_CFLAGS)
		endif
	endif
endif

CFLAGS += $(SDL2_CFLAGS)
CFLAGS += $(SDL2_IMAGE_CFLAGS)

LDFLAGS += $(SDL2_LDFLAGS)
LDFLAGS += $(SDL2_IMAGE_LDFLAGS)

all: $(MAIN)

$(MAIN): $(OBJDIR)/SDLTest.cpp.o 
	$(CXX) $(LDFLAGS) $< -o $@

$(OBJDIR)/%.cpp.o: $(SRCDIR)/%.cpp $(OBJDIR)
	$(CXX) $(CFLAGS) -c $< -o $@

$(OBJDIR):
	mkdir $(OBJDIR)

clean:
	rm -f $(MAIN)
	rm -Rf $(OBJDIR)
