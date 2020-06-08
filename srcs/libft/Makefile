# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: pminne <pminne@student.42lyon.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/10/13 19:22:26 by pramella          #+#    #+#              #
#    Updated: 2020/05/07 00:03:47 by pminne           ###   ########lyon.fr    #
#                                                                              #
# **************************************************************************** #


SRCS_DIR = srcs/

SRCS	= $(SRCS_DIR)ft_atoi.c\
		  $(SRCS_DIR)ft_bzero.c\
		  $(SRCS_DIR)ft_calloc.c\
		  $(SRCS_DIR)ft_fprintf.c\
		  $(SRCS_DIR)ft_fprintf_conversions.c\
		  $(SRCS_DIR)ft_fprintf_conversions2.c\
		  $(SRCS_DIR)ft_fprintf_format.c\
		  $(SRCS_DIR)ft_fprintf_utils.c\
		  $(SRCS_DIR)ft_isalnum.c\
		  $(SRCS_DIR)ft_isalpha.c\
		  $(SRCS_DIR)ft_isascii.c\
		  $(SRCS_DIR)ft_isdigit.c\
		  $(SRCS_DIR)ft_isinset.c\
		  $(SRCS_DIR)ft_isprint.c\
		  $(SRCS_DIR)ft_isspace.c\
		  $(SRCS_DIR)ft_itoa.c\
		  $(SRCS_DIR)ft_lstadd_back.c\
  		  $(SRCS_DIR)ft_lstadd_front.c\
  		  $(SRCS_DIR)ft_lstclear.c\
   		  $(SRCS_DIR)ft_lstdelone.c\
   		  $(SRCS_DIR)ft_lstiter.c\
   		  $(SRCS_DIR)ft_lstlast.c\
   		  $(SRCS_DIR)ft_lstmap.c\
  		  $(SRCS_DIR)ft_lstnew.c\
		  $(SRCS_DIR)ft_lstrm.c\
  		  $(SRCS_DIR)ft_lstsize.c\
		  $(SRCS_DIR)ft_memccpy.c\
		  $(SRCS_DIR)ft_memchr.c\
		  $(SRCS_DIR)ft_memcmp.c\
		  $(SRCS_DIR)ft_memcpy.c\
		  $(SRCS_DIR)ft_memmove.c\
		  $(SRCS_DIR)ft_memset.c\
		  $(SRCS_DIR)ft_printf.c\
		  $(SRCS_DIR)ft_printf_conversions.c\
		  $(SRCS_DIR)ft_printf_conversions2.c\
		  $(SRCS_DIR)ft_printf_format.c\
		  $(SRCS_DIR)ft_printf_utils.c\
		  $(SRCS_DIR)ft_putchar_fd.c\
		  $(SRCS_DIR)ft_putendl_fd.c\
		  $(SRCS_DIR)ft_putnbr_fd.c\
		  $(SRCS_DIR)ft_putstr_fd.c\
		  $(SRCS_DIR)ft_split.c\
		  $(SRCS_DIR)ft_split_free.c\
		  $(SRCS_DIR)ft_strchr.c\
		  $(SRCS_DIR)ft_strdup.c\
		  $(SRCS_DIR)ft_strjoin.c\
		  $(SRCS_DIR)ft_strlcat.c\
		  $(SRCS_DIR)ft_strlcpy.c\
		  $(SRCS_DIR)ft_strlen.c\
		  $(SRCS_DIR)ft_strmapi.c\
		  $(SRCS_DIR)ft_strncmp.c\
		  $(SRCS_DIR)ft_strnstr.c\
		  $(SRCS_DIR)ft_strrchr.c\
		  $(SRCS_DIR)ft_strtrim.c\
		  $(SRCS_DIR)ft_substr.c\
		  $(SRCS_DIR)ft_tolower.c\
		  $(SRCS_DIR)ft_toupper.c\
		  $(SRCS_DIR)get_next_line.c\
		  $(SRCS_DIR)get_next_line_utils.c

OBJS	= $(SRCS:.c=.o)

HEADER	= $(SRCS_D)libft.h

NAME	= libft.a

CC		= gcc

CFLAGS	= -Wall -Werror -Wextra

RM		= rm -f

%.o: 	%.c
		@$(CC) $(CFLAGS) -c $< -o $(<:.c=.o)

all:	$(NAME)

$(NAME):$(OBJS)
		@ar rc $(NAME) $(OBJS)
		@ranlib $(NAME)

clean:
		@$(RM) $(OBJS) $(B_OBJS)

fclean:	clean
		@$(RM) $(NAME)

re: 		fclean all

.PHONY: 	all clean fclean re
