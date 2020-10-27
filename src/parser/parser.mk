PARSER_DIR		= parser

PARSER_SOURCES	= parser.c
PARSER_SOURCES 	:= $(addprefix $(PARSER_DIR)/,$(PARSER_SOURCES))

SRC		+= $(PARSER_SOURCES)
HEADERS	+= parser.h
