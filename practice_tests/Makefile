# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mrojas-e <mrojas-e@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/03/09 17:31:08 by mrojas-e          #+#    #+#              #
#    Updated: 2022/03/12 17:32:52 by mrojas-e         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME 		=	mini
CC			=	gcc
CC_FLAGS	=	-Wall -Werror -Wextra
RM			=	rm -rf
DIR_HEADERS =	./includes/
DIR_SRCS	=	./srcs/
DIR_OBJS	=	./obj/
SRC			=	main.c lexer.c token.c
SRCS		=	$(SRC)
OBJS 		=	$(SRCS:%.c=$(DIR_OBJS)%.o)

all:			$(NAME)

$(NAME):		$(OBJS)
				@tput setaf 05 && printf "Sources Succesfully Compiled!\n"
				@$(CC) $(CC_FLAGS) -I $(DIR_HEADERS) $(OBJS) -o $(NAME)
				@tput setaf 013 && printf "$(NAME) created.\n"

$(OBJS):		$(DIR_OBJS)

$(DIR_OBJS)%.o: $(DIR_SRCS)%.c
#				@tput setaf 207 && printf "\nCompiling sources\n$<"
				@$(CC) $(CC_FLAGS) -I $(DIR_HEADERS) -c $< -o $@
$(DIR_OBJS):
				@mkdir $@

clean:
				@$(RM) $(DIR_OBJS)
				@tput setaf 117 && printf "\nobject files  deleted.\n"
				
fclean:			clean
				@$(RM) $(NAME)
				@tput setaf 117 && printf "FULL CLEAN COMPLETED.\n"

re:				fclean all

.PHONY:			all clean fclean re norm
