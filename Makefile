NAME = minishell

SRC_DIR = src/
INC_DIR = inc/

DISPLAY_DIR = $(addprefix ${SRC_DIR}, display/)
LEXING_DIR = $(addprefix ${SRC_DIR}, lexing/)
EXEC_DIR = $(addprefix ${SRC_DIR}, execution/)
PARSING_DIR = $(addprefix ${SRC_DIR}, parsing/)
UTILS_DIR = $(addprefix ${SRC_DIR}, utils/)

SRC = main.c
SRC_DISPLAY = prompt.c
SRC_EXEC =	builtins.c
SRC_LEXING =	lexer.c \
				token.c
SRC_PARSING =	clean_redirection.c \
				final_split.c \
				ft_split_pipe.c \
				ft_split_space.c \
				quotes.c
SRC_UTILS =	ft_split.c \
			get_path.c \
			utils_color.c \
			utils.c \
			utils2.c

SRCS = $(addprefix ${SRC_DIR}, ${SRC})
SRCS_DISPLAY = $(addprefix ${DISPLAY_DIR}, ${SRC_DISPLAY})
SRCS_LEXING = $(addprefix ${LEXING_DIR}, ${SRC_LEXING})
SRCS_EXEC = $(addprefix ${EXEC_DIR}, ${SRC_EXEC})
SRCS_PARSING = $(addprefix ${PARSING_DIR}, ${SRC_PARSING})
SRCS_UTILS = $(addprefix ${UTILS_DIR}, ${SRC_UTILS})

OBJ = $(SRCS:.c=.o)
OBJ_DISPLAY = ${SRCS_DISPLAY:.c=.o}
OBJ_LEXING = ${SRCS_LEXING:.c=.o}
OBJ_EXEC = ${SRCS_EXEC:.c=.o}
OBJ_PARSING = ${SRCS_PARSING:.c=.o}
OBJ_UTILS = ${SRCS_UTILS:.c=.o}
OBJS = ${OBJ} ${OBJ_DISPLAY} ${OBJ_LEXING} ${OBJ_EXEC} ${OBJ_PARSING} ${OBJ_UTILS}

CC = gcc
CFLAGS = -Wall -Wextra -Werror -g

TEXT = "My job is done. Now it's up to you.\n"
TEXT2 = " Created!\n"
TEXT3 = " deleted!\n"
TEXT4 = "Obj"

%.o: %.c
		@printf "\033[0;31m"
		@printf "Please wait... $@\r"
		@${CC} $(CFLAGS) -I $(INC_DIR) -c $< -o $@

$(NAME): $(OBJS)
		@${CC} $(CFLAGS) -o $(NAME) $(OBJS) -lreadline
		@printf "\n"
		@printf "\033[0m"$(NAME)$(TEXT2)

all:
	@$(MAKE) -j $(NAME)
	@printf "\033[33m"$(TEXT)

clean:
	@rm -rf $(OBJS)
	@printf "\033[0;31m"$(TEXT4)$(TEXT3)

fclean:	clean
	@rm -rf $(NAME)
	@printf "\033[0m"$(NAME)$(TEXT3)

re: fclean all

.PHONY: all, clean, fclean, re
