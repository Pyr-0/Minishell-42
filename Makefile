# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: shaas <shaas@student.42heilbronn.de>       +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/03/09 17:31:08 by mrojas-e          #+#    #+#              #
#    Updated: 2022/07/05 21:23:31 by shaas            ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME		=		minishell
CC			=		gcc
CC_FLAGS	=		-Wall -Wextra -Werror -g 
# check if mac or linux, different readline flags #
OS := $(shell uname)
ifeq ($(OS), Darwin)
	CPPFLAGS	=	-I$(HOME)/.brew/opt/readline/include
	LDFLAGS		=	-L$(HOME)/.brew/opt/readline/lib -lreadline
	LREADLINE	=
endif
ifeq ($(OS), Linux)
	CPPFLAGS	=
	LDFLAGS		=
	LREADLINE	=	-lreadline
endif
DIR_HEADERS =		./includes/
DIR_SRC		=		./src/
DIR_OBJ		=		./obj/
SRC			=		./src/print_stuff.c \
					./src/main.c \
					./src/pipe_redir_error.c \
					./src/sighandlers.c \
					./src/signals.c \
					./src/startup.c \
					./src/env/get_env.c \
					./src/env/init_env.c \
					./src/env/env_utils.c \
					./src/env/env_free_exit.c \
					./src/lexer/lexer.c \
					./src/lexer/lexer_init_structs.c \
					./src/lexer/lexer_advance_and_collect.c \
					./src/lexer/lexer_utils.c \
					./src/lexer/lexer_free_exit.c \
					./src/expander/expander.c \
					./src/expander/expand_dollar_sign.c \
					./src/expander/expand_quotes.c \
					./src/expander/expander_utils.c \
					./src/parser/parser.c \
					./src/parser/parser_free_exit.c \
					./src/parser/parser_init_structs.c \
					./src/parser/parser_add.c \
					./src/parser/parser_utils.c \
					./src/redir_creator/redir_creator.c \
					./src/redir_creator/redir_creator_free_exit.c \
					./src/redir_creator/redir_creator_utils.c \
					./src/redir_creator/redir_creator_init_exec_blocks.c \
					./src/redir_creator/handle_heredocs.c \
					./src/redir_creator/handle_heredoc_utils.c \
					./src/redir_creator/handle_redir_files.c \
					./src/executor/executor.c \
					./src/executor/handle_inbuilt.c \
					./src/executor/handle_non_inbuilt.c \
					./src/executor/find_cmd_path.c \
					./src/executor/envp_argv_creator.c \
					./src/builtins/cmd_pwd.c \
					./src/builtins/cmd_echo.c \
					./src/builtins/cmd_cd.c \
					./src/builtins/builtins_utils.c\
					./src/builtins/cmd_env.c \
					./src/builtins/cmd_export.c \
					./src/builtins/cmd_unset.c \
					./src/builtins/cmd_exit.c \

OBJ			=		$(SRC:$(DIR_SRC)%.c=$(DIR_OBJ)%.o)
LIBFT		=		libft/libft.a

all:			$(NAME)

$(NAME):		$(LIBFT) $(OBJ)
				@tput setaf 05 && printf "Sources Succesfully Compiled!\n"
				@$(CC) $(CC_FLAGS) $(CPPFLAGS) $(LDFLAGS) $(OBJ) $(LIBFT) -o $(NAME) $(LREADLINE)
				@tput setaf 013 && printf "$(NAME) created.\n"
				@printf "\e[0m"

$(LIBFT):		libft/*.c
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
				@tput setaf 1 && printf "*--------Full clean completed!---------*\n"

re:				fclean all

exec:
				./$(NAME)

both:			$(NAME) exec

.PHONY:			all clean fclean re
