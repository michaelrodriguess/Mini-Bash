SRCS			=	./sources/main.c \
					./sources/handling/handle_signals.c \
					./sources/handling/parser.c \
					./sources/tokenization/lst_token2.c\
					./sources/tokenization/lst_token.c\
					./sources/tokenization/lexer.c \
					./sources/tokenization/lexer2.c \

NAME			= minishell
OBJS			= $(SRCS:.c=.o)
LIBS			= sources/libft/libft.a
CC				= cc
RM				= rm -f
CFLAGS			= -Wall -Wextra -Werror -lreadline -L ~/.brew/opt/readline/lib -I ~/.brew/opt/readline/include


$(NAME):	$(SRCS) $(LIBS)
		$(CC) $(CFLAGS) $(SRCS) $(LIBS) -o $(NAME)

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
