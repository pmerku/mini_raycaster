SDL_DIR		= sdl

SDL_SOURCES	= init.c loop.c cleanup.c
SDL_SOURCES	:= $(addprefix $(SDL_DIR)/,$(SDL_SOURCES))

SRC		+= $(SDL_SOURCES)
HEADERS	+=
