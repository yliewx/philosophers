# declare makefile variables
NAME = philo
CC = cc
CFLAGS = -Wall -Wextra -Werror
RM = rm -f

# philo targets
INC = -I ./includes
TARGET = main.c init.c routine.c actions.c \
	exit_message_utils.c string_utils.c time_utils.c
SRCS = $(addprefix srcs/, $(TARGET))

# colours
GREEN = \033[0;32m
B_GREEN = \033[1;32m
BROWN = \033[0;33m
B_BROWN = \033[1;33m
END = \033[0m

# RULES

all: $(NAME)

$(NAME): $(SRCS)
	@echo "\n$(B_BROWN)[ COMPILING: $(NAME) ]$(END)"
	@$(CC) $(CFLAGS) $(SRCS) -o $(NAME) $(INC)
	@echo "$(B_GREEN)$(NAME) compiled.$(END)"

clean:
	@$(RM) $(NAME)
	@echo "$(B_GREEN)Removed $(NAME).$(END)"

fclean: clean

re: fclean all

# declare phony
.PHONY: all clean fclean re
