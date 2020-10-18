# Constants
NAME			= mini_raycaster

# Compiler
CFLAGS			= -std=c++17 -O2
LDFLAGS			= -lglfw -lvulkan -ldl -lpthread -lX11 -lXxf86vm -lXrandr -lXi
DFLAGS			= -g
CC++ 			= clang++
# Files
SRC_DIR			= src
OUT_DIR			= out
INC_DIR			= include
SRC				= main.c
HEADERS			=

LIBDIR			= lib
LIBFT			= lib/libft.a
INC_LIBFT		= lib/include

# Sub-modules
#include src/.mk

# Fix sources and headers
OBJ				= $(patsubst %.c,%.o,$(SRC))
HEADERS			:= $(addprefix $(INC_DIR)/,$(HEADERS))

# Colours
DARK_GREEN		= \033[0;32m
GREEN			= \033[0;92m
END				= \033[0;0m

PREFIX			= $(DARK_GREEN)$(NAME) $(END)\xc2\xbb

all: $(NAME)

deps:
	@echo "$(SRC)"

$(NAME): $(addprefix $(OUT_DIR)/,$(OBJ)) $(LIBFT)
	@echo "$(PREFIX)$(GREEN) Bundling objects...$(END)"
	@$(CC++) $(CFLAGS) $(DFLAGS) $(LDFLAGS) -I$(INC_DIR) -I$(INC_LIBFT) -o $@ $(addprefix $(OUT_DIR)/,$(OBJ)) -L$(LIBDIR) -lft

$(OUT_DIR)/%.o: $(SRC_DIR)/%.c $(HEADERS)
	@echo "$(PREFIX)$(GREEN) Compiling file $(END)$< $(GREEN)to $(END)$@"
	@mkdir -p $(dir $@)
	@$(CC++) $(CFLAGS) $(DFLAGS) $(LDFLAGS) -I$(INC_DIR) -I$(INC_LIBFT) -o $@ -c $<

$(LIBFT):
	@echo "$(PREFIX)$(GREEN) Bundling $(LIBDIR)...$(END)"
	@$(MAKE) -C $(LIBDIR) > /dev/null

clean:
	@echo "$(PREFIX)$(GREEN) Removing directory $(END)$(OUT_DIR), $(LIBDIR)/out"
	@rm -rf $(OUT_DIR)
	@$(MAKE) -C $(LIBDIR) clean > /dev/null

fclean: clean
	@echo "$(PREFIX)$(GREEN) Removing file $(END)$(NAME), $(LIBFT)"
	@rm -f $(NAME)
	@$(MAKE) -C $(LIBDIR) fclean > /dev/null

re: fclean $(NAME)

exec: $(NAME)
	./$(NAME)

valgrind: $(NAME)
	valgrind --undef-value-errors=no --leak-check=full ./$(NAME)

.PHONY: all clean fclean re exec valgrind
