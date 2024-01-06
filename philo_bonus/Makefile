# declare makefile variables
NAME = philo_bonus
CC = cc
CFLAGS = -Wall -Wextra -Werror -g
RM = rm -f

# philo targets
INC = -I ./includes
TARGET = main_bonus.c init_bonus.c routine_bonus.c actions_bonus.c \
	exit_utils_bonus.c message_utils_bonus.c \
	string_utils_bonus.c time_utils_bonus.c
SRCS = $(addprefix srcs_bonus/, $(TARGET))

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
