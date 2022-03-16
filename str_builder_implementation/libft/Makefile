# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mrojas-e <mrojas-e@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/07/27 12:46:02 by mrojas-e          #+#    #+#              #
#    Updated: 2021/08/23 17:36:25 by mrojas-e         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = libft.a
SRC = 		ft_isalnum.c\
			ft_atoi.c\
			ft_isalpha.c\
			ft_isdigit.c\
			ft_memmove.c\
			ft_memchr.c\
			ft_memset.c\
			ft_strlen.c\
			ft_tolower.c\
			ft_bzero.c\
			ft_isascii.c\
			ft_isprint.c\
			ft_memcpy.c\
			ft_memcmp.c\
			ft_strlcpy.c\
			ft_strncmp.c\
			ft_toupper.c\
			ft_strlcat.c\
			ft_strchr.c\
			ft_strrchr.c\
			ft_strnstr.c\
			ft_calloc.c\
			ft_strdup.c\
			ft_substr.c\
			ft_strjoin.c\
			ft_strtrim.c\
			ft_split.c\
			ft_itoa.c\
			ft_strmapi.c\
			ft_striteri.c\
			ft_putchar_fd.c\
			ft_putstr_fd.c\
			ft_putendl_fd.c\
			ft_putnbr_fd.c\

BONUS =		\
			ft_lstnew.c\
			ft_lstadd_front.c\
			ft_lstsize.c\
			ft_lstlast.c\
			ft_lstadd_back.c\
			ft_lstdelone.c\
			ft_lstclear.c\
			ft_lstiter.c\
			ft_lstmap.c

all: $(NAME)

$(NAME):
	gcc  -Wall -Werror -Wextra -c $(SRC)
	ar -crs $(NAME) *.o 

clean: 
	rm -f *.o
	rm -f *~

fclean: clean
	rm -f $(NAME)

re: fclean all

bonus: $(NAME)
	gcc  -Wall -Werror -Wextra -c $(BONUS)
	ar -crs $(NAME) *.o 
