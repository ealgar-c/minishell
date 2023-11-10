# COMPILER INFO
CC = cc
LIBFT_PATH = libft/
FLAGS = -Wall -Wextra -Werror
RM = rm -rf
INCLUDE_DIRS = include -I $(LIBFT_PATH) -I /opt/homebrew/Cellar/readline/8.2.1/include
LIBS =  -L$(LIBFT_PATH) -lreadline

SYS	= $(shell uname -s)

ifeq ($(SYS), Darwin)
INCLUDE_DIRS +=	-I /opt/vagrant/embedded/include
LIBS	+= -L/opt/vagrant/embedded/lib
endif

# GENERAL INFO
NAME = minishell
SRC_DIR = src/
SRC = free_utils.c executer.c lexer.c lexer_list_utils.c main.c parser.c\
	builtin_exit.c builtin_echo.c builtin_pwd.c builtin_cd.c lexer_utils.c\
	extensor.c enviroment.c builtin_env.c builtin_export.c builtin_unset.c\
	parser_arguments_utils.c extend_and_quote.c redirections.c signals.c errors.c\
	pipes_config.c builtin_export_utils.c free.c executer_utils.c parser_utils.c\
	builtin_cd_utils.c # ext_and_quo_nodutils.c
OBJ_DIR = objs/
OBJ = $(addprefix $(OBJ_DIR), $(SRC:.c=.o))

# COLOR CODES
GREEN_CODE=\033[0;32m
RED_CODE=\033[0;31m
CEND_CODE=\033[0m

all: libft $(NAME)
$(NAME): $(OBJ)
	@$(CC) $(FLAGS) $(LIBS) -o $(NAME) $(OBJ) libft/*.o
	@ echo "-->$(GREEN_CODE) $(NAME) compiled ✅ $(CEND_CODE)<--"

$(OBJ_DIR)%.o: $(SRC_DIR)%.c
	@mkdir -p $(OBJ_DIR)
	@$(CC) $(FLAGS) -I $(INCLUDE_DIRS) -c $< -o $@

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
