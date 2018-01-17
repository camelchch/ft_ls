# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: saxiao <marvin@42.fr>                      +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2017/11/07 10:44:51 by saxiao            #+#    #+#              #
#    Updated: 2017/12/21 23:34:37 by saxiao           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

.PHONY: all clean fclean re

CC = gcc
FLAGS = -c -Wall -Wextra -Werror
SRC = ft_atoi.c ft_bzero.c ft_isalnum.c ft_isalpha.c ft_isascii.c\
		ft_isdigit.c ft_isprint.c ft_memalloc.c ft_memchr.c ft_memcmp.c\
		ft_memcpy.c ft_memdel.c ft_memmove.c ft_memset.c ft_strcat.c\
		ft_strchr.c ft_strclr.c ft_strcmp.c ft_strcpy.c ft_strdel.c\
		ft_strdup.c ft_strequ.c ft_striter.c ft_striteri.c ft_strlcat.c\
		ft_strlen.c ft_strmap.c ft_strmapi.c ft_strncat.c ft_strncmp.c\
		ft_strncpy.c ft_strnew.c ft_strnstr.c ft_strrchr.c ft_strstr.c\
		ft_tolower.c ft_toupper.c ft_strnequ.c ft_strsub.c ft_strjoin.c\
		ft_strtrim.c ft_strsplit.c ft_itoa.c ft_putchar.c ft_putstr.c\
		ft_putendl.c ft_putnbr.c ft_putchar_fd.c ft_putstr_fd.c ft_putnexit.c\
		ft_putendl_fd.c ft_putnbr_fd.c ft_lstnew.c ft_lstdelone.c ft_strrev.c\
		ft_memccpy.c ft_lstdel.c ft_lstadd.c ft_lstiter.c ft_lstmap.c\
		ft_swap.c
OBJS = $(SRC:.c=.o)
INCLUDE = -I .
NAME = libft.a

PRINTF_SRCNAME = cacul.c con_cp.c con_d.c con_o.c con_s.c con_u.c con_x.c \
		   convert_base.c ft_printf.c put.c set_print_oux.c set_print_d.c \
		   set_castflag.c itoa_max.c itoa_hexbase.c for_print_oux.c ini_set.c
PRINTF_PATH = ft_printf/srcs/
PRINTF_INC = -I ft_printf/includes
PRINTF_OBJS = $(PRINTF_SRCNAME:.c=.o)
PRINTF_SRC = $(addprefix $(PRINTF_PATH), $(PRINTF_SRCNAME))
PRINTF_NAME = libftprintf.a

all:$(NAME)

$(NAME):$(OBJS)
	@ar rc $(NAME) $(OBJS)
	@ranlib $(NAME)
	@$(CC) $(FLAGS) $(PRINTF_INC) $(PRINTF_SRC)
	@ar rc $(PRINTF_NAME) $(PRINTF_OBJS) $(NAME)
	@ranlib $(PRINTF_NAME)


$(OBJS):$(SRC)
	@$(CC) $(FLAGS) $(INCLUDE) $(SRC)

clean:
	@rm -rf $(OBJS)
	@rm -rf $(PRINTF_OBJS)

fclean:clean
	@rm -rf $(NAME)
	@rm -rf $(PRINTF_NAME)

re:fclean all
