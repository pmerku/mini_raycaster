# Constants
NAME			= mini_raycaster

# Compiler
CFLAGS			= -O3
LDFLAGS			= -lSDL2 -lSDL2_image -lSDL2_ttf -lSDL2_mixer -lm
DFLAGS			=

#ifdef DEBUG
DFLAGS			+= -g
#endif

CC				= clang
# Files
SRC_DIR			= src
OUT_DIR			= out
INC_DIR			= include
SRC				= main.c
HEADERS			= raycaster.h

LIBDIR			= lib
LIBFT			= lib/libft.a
INC_LIBFT		= lib/include

# Sub-modules
include src/engine/engine.mk
include src/parser/parser.mk
include src/sdl/sdl.mk

# Fix sources and headers
OBJ				= $(patsubst %.c,%.o,$(SRC))
HEADERS			:= $(addprefix $(INC_DIR)/,$(HEADERS))

# Colours
DARK_GREEN		= \033[0;32m
GREEN			= \033[0;92m
END				= \033[0;0m

UNAME_S := $(shell uname -s)
ifeq ($(UNAME_S),Linux)
	PREFIX			= $(DARK_GREEN)$(NAME) $(END)>>
endif
ifeq ($(UNAME_S),Darwin)
	PREFIX			= $(DARK_GREEN)$(NAME) $(END)\xc2\xbb
endif

all: $(NAME)

deps:
	@printf "$(SRC)\n"

$(NAME): $(addprefix $(OUT_DIR)/,$(OBJ)) $(LIBFT)
	@printf "$(PREFIX)$(GREEN) Bundling objects...$(END)\n"
	@$(CC) $(CFLAGS) $(DFLAGS) $(LDFLAGS) -I$(INC_DIR) -I$(INC_LIBFT) -o $@ $(addprefix $(OUT_DIR)/,$(OBJ)) -L$(LIBDIR) -lft

$(OUT_DIR)/%.o: $(SRC_DIR)/%.c $(HEADERS)
	@printf "$(PREFIX)$(GREEN) Compiling file $(END)$< $(GREEN)to $(END)$@\n"
	@mkdir -p $(dir $@)
	@$(CC) $(CFLAGS) $(DFLAGS) -I/usr/include/SDL2 -I$(INC_DIR) -I$(INC_LIBFT) -o $@ -c $<

$(LIBFT):
	@printf "$(PREFIX)$(GREEN) Bundling $(LIBDIR)...$(END)\n"
	@$(MAKE) -C $(LIBDIR) > /dev/null

clean:
	@printf "$(PREFIX)$(GREEN) Removing directory $(END)$(OUT_DIR), $(LIBDIR)/out\n"
	@rm -rf $(OUT_DIR)
	@$(MAKE) -C $(LIBDIR) clean > /dev/null

fclean: clean
	@printf "$(PREFIX)$(GREEN) Removing file $(END)$(NAME), $(LIBFT)\n"
	@rm -f $(NAME)
	@$(MAKE) -C $(LIBDIR) fclean > /dev/null

re: fclean $(NAME)

exec: $(NAME)
	./$(NAME) --width=640 --height=480

valgrind: $(NAME)
	valgrind --undef-value-errors=no --leak-check=full ./$(NAME)

.PHONY: all clean fclean re exec valgrind
