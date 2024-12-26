## GLOBAL VARIABLES

NAME = minishell
SRCS = main.c
SRCS_FILES = $(addprefix src/, $(SRCS))
BUILTINS_FILES = cd.c export.c pwd.c echo.c env.c env_utils.c unset.c exit.c export_utils.c
UTILS_FILES = get_next.c get_next_utils.c signals.c wait.c history.c free.c \
			  get_set.c my_split.c str_utils.c errors.c some_utils.c
HEREDOC_FILES = heredoc.c heredoc_utils.c
EXPANDER_FILES = expander.c expander_utils.c expander_utils2.c expander_utils3.c
PARSER_FILES = lexer.c lexer_utils.c lexer_utils2.c parser.c parser_utils.c main_parser.c
EXEC_FILES = exec.c exec_utils.c exec_utils3.c redirections.c exec_utils2.c
SRCS_FILES += $(addprefix src/builtins/, $(BUILTINS_FILES))
SRCS_FILES += $(addprefix src/utils/, $(UTILS_FILES))
SRCS_FILES += $(addprefix src/heredoc/, $(HEREDOC_FILES))
SRCS_FILES += $(addprefix src/expander/, $(EXPANDER_FILES))
SRCS_FILES += $(addprefix src/parser/, $(PARSER_FILES))
SRCS_FILES += $(addprefix src/exec/, $(EXEC_FILES))
CFLAGS = -Wall -Wextra -Werror
CC = gcc -g
LINKINGS = -Llibft -lft -lreadline
INCLUDE = -I./libft -I./include
LIBFT = ./libft
RM = rm -rf

## RULES
all: $(NAME)

$(NAME): $(SRCS_FILES)
	make -C $(LIBFT) bonus
	$(CC) $(CFLAGS) $(INCLUDE) $(SRCS_FILES) -o $(NAME) $(LINKINGS)

clean:
	make -C $(LIBFT) clean
	$(RM) *.o */*.o */*/*.o

fclean: clean
	make -C $(LIBFT) fclean
	$(RM) $(NAME)

re: fclean all

valgrind:
	valgrind --leak-check=full --show-leak-kinds=all --suppressions=readline.donto ./$(NAME)

.PHONY: all clean fclean re
