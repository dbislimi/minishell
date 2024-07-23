LIBFT_PATH 	= ./libft
LIBFT      	= $(LIBFT_PATH)/libft.a

LEXER_PATH 		= ./lexer
PARSER_PATH 	= ./parser
EXTENDER_PATH 	= ./extender
EXECUTION_PATH	= ./execution
BUILTINS_PATH 	= ./builtins

SRCS 	= main.c ${addprefix ${EXTENDER_PATH}/, env_init.c env_build.c env_clear.c print_env.c} ${addprefix ${BUILTINS_PATH}/, signals.c echo.c}
OBJS 	= ${SRCS:.c=.o}


NAME 	= minishell
CC 		= cc
CFLAGS	= -Wall -Wextra -Werror -g3
LDFLAGS = -lreadline
RM 		= rm -rf
INCLUDES = -Iincludes

all : ${NAME}

${NAME} : ${LIBFT} ${OBJS}
	${CC} ${CFLAGS} -o ${NAME} ${OBJS} ${LIBFT} ${LDFLAGS}

$(LIBFT):
	${MAKE} -C $(LIBFT_PATH) all

%.o: %.c
	$(CC) $(CFLAGS) -c -o $@ $< $(INCLUDES)
	
clean:
	@${MAKE} clean --silent -C ${LIBFT_PATH}
	@${RM} ${OBJS}
	@printf "MAKEFILE CLEAN\n"

fclean: clean
	@${MAKE} fclean --silent -C ${LIBFT_PATH}
	@${RM} ${NAME}
	@printf "MAKEFILE FCLEAN\n"

re: fclean all

.PHONY: all clean fclean re