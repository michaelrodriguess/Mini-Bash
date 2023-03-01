SRCS			=	./sources/tokenization/lexer.c \
					./sources/tokenization/lst_token.c \
					./sources/tokenization/validation.c

NAME			= minishell
OBJS			= $(SRCS:.c=.o)
LIBS			= sources/libft/libft.a
CC				= cc
RM				= rm -f
CFLAGS			= -g -Wall -Wextra -Werror


$(NAME):	$(SRCS) $(LIBS)
		$(CC) $(CFLAGS) $(SRCS) $(LIBS) -lreadline -o $(NAME)

$(LIBS): sources/libft
	make -C sources/libft/ all

all: $(NAME)

clean:
		$(RM) $(OBJS)
		make -C sources/libft/ clean

fclean:	clean
	   	$(RM) $(NAME) $(LIBS)

re: fclean all

.PHONY: all clean fclean re
