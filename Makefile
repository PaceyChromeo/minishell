SRC = 	main.c \
		prompt.c \
		checking.c \
		utils.c \
		utils2.c \
		ft_split.c \
		all_about_env.c \
		builtins.c

NAME = minishell
CC = gcc
CFLAGS = -Wall -Wextra -Werror -g
OBJ_DIR = obj
SRC_DIR = src
INC_DIR = inc
TEXT = "My job is done. Now it's up to you.\n"
TEXT2 = " Created!\n"
TEXT3 = " deleted!\n"
TEXT4 = "Obj"

OBJ = $(addprefix $(OBJ_DIR)/,$(SRC:.c=.o))

all:
	@$(MAKE) -j $(NAME)
	@printf "\033[33m"$(TEXT)

$(NAME): $(OBJ)
		@${CC} $(CFLAGS) -o $(NAME) $(OBJ) -lreadline
		@printf "\n"
		@printf "\033[0m"$(NAME)$(TEXT2)

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
		@mkdir -p $(OBJ_DIR)
		@printf "\033[0;31m"
		@printf "Please wait... $@\r"
		@${CC} $(CFLAGS) -I $(INC_DIR) -c $< -o $@

clean:
	@rm -rf $(OBJ_DIR)
	@printf "\033[0;31m"$(TEXT4)$(TEXT3)

fclean:	clean
	@rm -rf $(NAME)
	@printf "\033[0m"$(NAME)$(TEXT3)

re: fclean all

.PHONY: all, clean, fclean, re
