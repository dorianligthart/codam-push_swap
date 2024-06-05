NAME	 := push_swap
NAME_BON := checker_linux
# CFLAGS	 := -Wextra -Wall -Werror -Wunreachable-code -g
CC       := clang
INCLUDE	 := -I ./include
HEADERS  := $(shell find include -iname "*.h")

#TODO: add libft :_)
SRC		:= $(shell find src -iname "*.c") #TODO: PROJECT_END: type out src
OBJ		:= $(addsuffix .o, $(basename $(SRC)))
SRC_BON	:= $(shell find src_bonus -iname "*.c") src/libft.c #TODO: PROJECT_END: type out src_bonus
OBJ_BON	:= $(addsuffix .o, $(basename $(SRC_BON)))

%.o: %.c
	@$(CC) $(CFLAGS) -o $@ -c $< $(INCLUDE)

$(NAME): $(HEADERS) $(OBJ)
#	@echo -n "Are you sure you want to: $(CC) $(OBJ) $(INCLUDE) -o $(NAME) [y/N] " && read ans && [ $${ans:-N} = y ]
	$(CC) $(OBJ) $(INCLUDE) -o $(NAME)

$(NAME_BON): $(HEADERS) $(OBJ_BON)
#	@echo -n "Are you sure you want to: $(CC) $(OBJ_BON) $(INCLUDE) -o $(NAME_BON) [y/N] " && read ans && [ $${ans:-N} = y ]
	$(CC) $(OBJ_BON) $(INCLUDE) -o $(NAME_BON)

all: $(NAME)
bonus: $(NAME_BON)
clean:
	@rm -f $(OBJ) $(OBJ_BON)
fclean: clean
	@rm -f $(NAME) $(NAME_BON)
re: fclean all

.PHONY: all clean fclean re 
