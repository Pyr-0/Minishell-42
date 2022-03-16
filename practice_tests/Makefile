# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mrojas-e <mrojas-e@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/03/09 17:31:08 by mrojas-e          #+#    #+#              #
#    Updated: 2022/03/16 11:01:55 by mrojas-e         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME		=	minishell
CC			=	gcc
CC_FLAGS	=	-lreadline $(LDFLAGS) $(CPPFLAGS) -Wall -Wextra -Werror
LDFLAGS		=	"-L/Users/$(USER)/.brew/opt/readline/lib"
CPPFLAGS	=	"-I/Users/$(USER)/.brew/opt/readline/include"
DIR_HEADERS =	./includes/
DIR_SRCS	=	./srcs/
DIR_OBJS	=	./obj/
SRC			=	./srcs/main.c ./srcs/lexer.c ./srcs/token.c
OBJS		=	$(SRC:%.c=$(DIR_OBJS)%.o)
LIBFT		=	libft/libft.a

all:			$(NAME)

$(NAME):		$(LIBFT) $(OBJ)
				@tput setaf 05 && printf "Sources Succesfully Compiled!\n"
				@ $(CC) $(CC_FLAGS) $(SRC) $(LIBFT) -o $(NAME)
				@tput setaf 013 && printf "$(NAME) created.\n"

$(LIBFT):
				@tput setaf 117 && printf "*--------checking libft...-------------*\n"
				@make -C ./libft

$(DIR_OBJS)%.o:	$(DIR_SRCS)%.c
				@mkdir -p $(dir $@)
				$(CC) $(CC_FLAGS) -I $(DIR_HEADERS) -c $< -o $@

clean:
				@$(RM) $(DIR_OBJS)
				make -C libft clean
				@tput setaf 01 && printf "*--------Object files removed!---------*\n"
				
fclean:			clean
				@rm -rf $(NAME)
				@rm -rf $(LIBFT)
				@tput setaf 117 && printf "*--------Full clean completed!---------*\n"

re:				fclean all

exec:
				@tput setaf 117 && printf "*--------executing program!------------*\n"
				./$(NAME)

both:			$(NAME) exec

.PHONY:			all clean fclean re norm
