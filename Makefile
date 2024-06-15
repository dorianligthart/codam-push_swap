NAME     = push_swap
NAME_BON = checker_linux
CC       = cc
CFLAGS   = -I ./include -Wall -Wextra -g #-fsanitize=address

SRC = $(shell find src -iname "*.c") #TODO: PROJECT_END: type out src
SRC_BON = $(shell find src_bonus -iname "*.c") #TODO: PROJECT_END: type out src

$(NAME): $(BUILD) $(HEADERS) $(SRC)
#	@echo -n "Are you sure you want to: $(CC) $(CFLAGS) $(SRC) -o $(NAME)\
    [y/N] " && read ans && [ $${ans:-N} = y ]
	@$(CC) $(CFLAGS) $(SRC) -o $(NAME)

$(NAME_BON): $(BUILD) $(HEADERS) $(SRC_BON)
#	@echo -n "Are you sure you want to: $(CC) $(CFLAGS) $(SRC_BON) -o $(NAME_BON)\
    [y/N] " && read ans && [ $${ans:-N} = y ]
	@$(CC) $(CFLAGS) $(SRC_BON) src/libft.c -o $(NAME_BON)

all: $(NAME)
bonus: $(NAME_BON)
clean:
	@rm -f $(NAME)
	@rm -f $(NAME_BON)
fclean: clean
re: fclean $(NAME)

.PHONY: $(NAME) all bonus clean fclean re