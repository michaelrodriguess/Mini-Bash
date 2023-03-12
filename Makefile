SRCS			=	./sources/main.c \
					./sources/handling/handle_signals.c \
					./sources/handling/parser.c \
					./sources/handling/parser_builtin.c \
					./sources/handling/clear_memory.c \
					./sources/handling/handle_error.c \
					./sources/tokenization/lst_token2.c\
					./sources/tokenization/lst_token.c\
					./sources/tokenization/lexer.c \
					./sources/tokenization/lexer2.c \
					./sources/built-ins/util_builtins.c \
					./sources/built-ins/pwd.c \
					./sources/built-ins/echo.c \
					./sources/built-ins/cd.c \
					./sources/built-ins/exit.c \
					./sources/built-ins/env.c \
					./sources/built-ins/unset.c \
					./sources/built-ins/export.c \
					./sources/handling/parse_str.c \
					./sources/handling/expand_envvar.c \

NAME			= minishell
OBJS			= $(SRCS:.c=.o)
LIBS			= sources/libft/libft.a
CC				= cc
RM				= rm -f
CFLAGS			= -Wall -Wextra -Werror -lreadline -L ~/.brew/opt/readline/lib -I ~/.brew/opt/readline/include ##MAC
##CFLAGS			= -Wall -Wextra -Werror ##LINUX


$(NAME):	$(SRCS) $(LIBS)
		$(CC) $(CFLAGS) $(SRCS) $(LIBS) -g -lreadline -o $(NAME)

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
