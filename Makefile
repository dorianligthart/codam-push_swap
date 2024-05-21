NAME	 := push_swap
NAME_BON := checker_linux
CFLAGS	 := -Wextra -Wall -Werror -Wunreachable-code -g
CC       := gcc
HEADERS	:= -I ./include

SRC		:= $(shell find src -iname "*.c") #TODO: PROJECT_END: type out src
OBJ		:= $(addsuffix .o, $(basename $(SRC)))
SRC_BON	:= $(shell find src_bonus -iname "*.c") #TODO: PROJECT_END: type out src_bonus
OBJ_BON	:= $(addsuffix .o, $(basename $(SRC_BON)))

%.o: %.c
	@$(CC) $(CFLAGS) -o $@ -c $< $(HEADERS)

$(NAME): $(OBJ)
	$(CC) $(OBJ) $(HEADERS) -o $(NAME)

$(NAME_BON): $(OBJ_BON)
	$(CC) $(OBJ_BON) $(HEADERS) -o $(NAME_BON)

all: $(NAME)
bonus: $(NAME_BON)
clean:
	@rm -f $(OBJ) $(OBJ_BON)
fclean: clean
	@rm -f $(NAME) $(NAME_BON)
re: fclean all

# fsanitize: CFLAGS += -g -fsanitize=address 
# fsanitize: re

.PHONY: all clean fclean re 
