NAME	 := push_swap
NAME_BON := checker
CFLAGS	 := -Wextra -Wall -Werror -Wunreachable-code -O3 -g#`-fsanitize=address
LIBFT	 := ./libft
LIBFT_A	 := ./libft/libft.a

HEADERS	:= -I ./include -I $(LIBFT)/include
LIBS	:= $(LIBFT_A) -lm

SRC		:= $(shell find ./src -iname "*.c") #TODO: PROJECT_END: type out src
OBJ		:= ${SRC:.c=.o}
SRC_BON	:= $(shell find ./src_bonus -iname "*.c") #TODO: PROJECT_END: type out src_bonus
OBJ_BON	:= ${SRC_BON:.c=.o}

all: $(LIBFT_A) $(NAME)

$(LIBFT_A):
	echo "libft.a has been deleted!"

%.o: %.c
	@$(CC) $(CFLAGS) -o $@ -c $< $(HEADERS)

$(NAME): $(OBJ)
	@$(CC) $(OBJ) $(LIBS) $(HEADERS) -o $(NAME)

$(NAME_BON): $(OBJ_BON)
	@$(CC) $(OBJ_BON) $(LIBS) $(HEADERS) -o $(NAME_BON)

clean:
	@rm -rf $(OBJ)
	@rm -rf $(OBJ_BON)

bonus:
	@$(CC) $(OBJ_BON) $(LIBS) $(HEADERS) -o $(NAME_BON)

fclean: clean
	@rm -rf $(NAME)
	@rm -rf $(NAME_BON)

re: fclean all

.PHONY: all, clean, fclean, re, libmlx
