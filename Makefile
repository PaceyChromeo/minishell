NAME = minishell

SRC_DIR = src/
INC_DIR = inc/

DIS_DIR = $(addprefix ${SRC_DIR}, display/)
EXE_DIR = $(addprefix ${SRC_DIR}, execution/)
PARS_DIR = $(addprefix ${SRC_DIR}, parsing/)
UTIL_DIR = $(addprefix ${SRC_DIR}, utils/)

SRC = main.c
SRC_DIS = prompt.c
SRC_EXE = builtins.c
SRC_PARS =	cleaning.c \
			lexer.c \
			find_quotes.c \
			split_pipes.c
SRC_UTIL =	ft_split.c \
			utils.c \
			utils2.c \
			get_path.c \
			lst_utils.c

SRCS = $(addprefix ${SRC_DIR}, ${SRC})
SRCS_DIS = $(addprefix ${DIS_DIR}, ${SRC_DIS})
SRCS_EXE = $(addprefix ${EXE_DIR}, ${SRC_EXE})
SRCS_PARS = $(addprefix ${PARS_DIR}, ${SRC_PARS})
SRCS_UTIL = $(addprefix ${UTIL_DIR}, ${SRC_UTIL})

OBJ = $(SRCS:.c=.o)
OBJ_DIS = ${SRCS_DIS:.c=.o}
OBJ_EXE = ${SRCS_EXE:.c=.o}
OBJ_PARS = ${SRCS_PARS:.c=.o}
OBJ_UTIL = ${SRCS_UTIL:.c=.o}
OBJS = ${OBJ} ${OBJ_DIS} ${OBJ_EXE} ${OBJ_PARS} ${OBJ_UTIL}

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
