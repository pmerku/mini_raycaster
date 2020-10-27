ENGINE_DIR		= engine

ENGINE_SOURCES	= render.c color.c movement.c
ENGINE_SOURCES 	:= $(addprefix $(ENGINE_DIR)/,$(ENGINE_SOURCES))

SRC		+= $(ENGINE_SOURCES)
HEADERS	+= engine.h
