# COMPILER INFO
CC = cc
FLAGS = -Wall -Wextra -Werror
RM = rm -rf

# GENERAL INFO
NAME = minishell
SRC_DIR = src/
SRC = main.c 
OBJ_DIR = objs/
OBJ = $(addprefix $(OBJ_DIR), $(SRC:.c=.o))

# COLOR CODES
GREEN_CODE=\033[0;32m
RED_CODE=\033[0;31m
CEND_CODE=\033[0m

all: libft $(NAME)
$(NAME): $(OBJ)
	@$(CC) $(FLAGS) -lreadline -o $(NAME) $(OBJ) libft/*.o
	@ echo "-->$(GREEN_CODE) $(NAME) compiled ✅ $(CEND_CODE)<--"

$(OBJ_DIR)%.o: $(SRC_DIR)%.c
	@mkdir -p $(OBJ_DIR)
	@$(CC) $(FLAGS) -c $< -o $@

libft:
	@make -C libft/

clean:
	@$(RM) -r $(OBJ_DIR)
	@make -C libft/ clean
	@ echo "-->$(RED_CODE) $(NAME) cleaned 🗑 $(CEND_CODE)<--"

fclean: clean
	@$(RM) $(NAME) $(NAME_B)
	@make -C libft/ fclean

re: fclean all

.PHONY: all libft clean fclean re
