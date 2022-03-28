# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mrojas-e <mrojas-e@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/03/09 17:31:08 by mrojas-e          #+#    #+#              #
#    Updated: 2022/03/26 14:51:05 by mrojas-e         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME		=	minishell
CC			=	gcc
CC_FLAGS	=	-Wall -Wextra -Werror -g
# check if mac or linux, different readline flags #
OS := $(shell uname)
ifeq ($(OS), Darwin)
	CPPFLAGS	=	-I/Users/$(USER)/.brew/opt/readline/include
	LDFLAGS		=	-L/Users/$(USER)/.brew/opt/readline/lib -lreadline
	LREADLINE	=
endif
ifeq ($(OS), Linux)
	CPPFLAGS	=
	LDFLAGS		=
	LREADLINE	=	-lreadline
endif
DIR_HEADERS =	./includes/
DIR_SRC		=	./src/
DIR_OBJ		=	./obj/
SRC			=	./src/main.c ./src/lexer/lexer.c ./src/lexer/lexer_init_structs.c ./src/lexer/lexer_utils.c \
				./src/lexer/lexer_free_exit.c ./src/env/pipe_redir_error.c ./src/env/handle_env.c \
				./src/env/parser_expander.c
OBJ			=	$(SRC:$(DIR_SRC)%.c=$(DIR_OBJ)%.o)
LIBFT		=	libft/libft.a

all:			$(NAME)

$(NAME):		$(LIBFT) $(OBJ)
				@tput setaf 05 && printf "Sources Succesfully Compiled!\n"
				@$(CC) $(CC_FLAGS) $(LDFLAGS) $(SRC) $(LIBFT) -o $(NAME) $(LREADLINE)
				@tput setaf 013 && printf "$(NAME) created.\n"

$(LIBFT):
				@tput setaf 117 && printf "*--------checking libft...-------------*\n"
				@make -C ./libft

$(DIR_OBJ)%.o:	$(DIR_SRC)%.c
				@mkdir -p $(dir $@)
				$(CC) $(CC_FLAGS) $(CPPFLAGS) -I $(DIR_HEADERS) -c $< -o $@

clean:
				@rm -rf $(DIR_OBJ)
				@make -C libft clean
				@tput setaf 1 && printf "*--------Object files removed!---------*\n"
				
fclean:			clean
				@rm -rf $(NAME)
				@rm -rf $(LIBFT)
				@tput setaf 117 && printf "*--------Full clean completed!---------*\n"

re:				fclean all

exec:
				@tput setaf 1 && printf   "           (        )       (     (              \n"
				@tput setaf 1 && printf   "           )\ )  ( /(       )\ )  )\ )           \n"
				@tput setaf 1 && printf   "       (  (()/(  )\()) (   (()/( (()/( (         \n"
				@tput setaf 1 && printf   "       )\  /(_))((_)\  )\   /(_)) /(_)))\        \n"
				@tput setaf 1 && printf   "     '((_)(_))   _((_)((_) (_))  (_))  (_)       \n"
				@tput setaf 010 && printf " _ _   (_)/ __| | || || __|| |   | |   (_) _ _   \n"
				@tput setaf 010 && printf "| '  \ | |\__ \ | __ || _| | |__ | |__ | || ' \  \n"
				@tput setaf 010 && printf "|_|_|_||_||___/ |_||_||___||____||____||_||_||_| \n"
				@tput setaf 010 && printf "                                                 \n"
				@tput setaf 007 && printf "*--------executing program!------------*\n"
				./$(NAME)

both:			$(NAME) exec

.PHONY:			all clean fclean re