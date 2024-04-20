NAME	 := push_swap
NAME_BON := checker
CFLAGS	 := -Wextra -Wall -Werror -Wunreachable-code -O3 -g#`-fsanitize=address
LIBFT	 := libft
LIBFT_A	 := libft/libft.a
BUILD	 := build/

HEADERS	:= -I ./include -I $(LIBFT)/include
LIBS	:= $(LIBFT_A) -lm

SRC		:= $(shell find src -iname "*.c") #TODO: PROJECT_END: type out src
OBJ		:= $(addsuffix .o, $(basename $(SRC)))
SRC_BON	:= $(shell find src_bonus -iname "*.c") #TODO: PROJECT_END: type out src_bonus
OBJ_BON	:= $(addsuffix .o, $(basename $(SRC_BON)))

$(LIBFT_A):
	echo "libft.a has been deleted!"

%.o: %.c
	@$(CC) $(CFLAGS) -o $@ -c $< $(HEADERS)

$(BUILD):
	mkdir -p $(BUILD)

$(NAME): $(BUILD) $(OBJ)
	@$(CC) $(OBJ) $(LIBS) $(HEADERS) -o $(NAME)

$(NAME_BON): $(OBJ_BON)
	@$(CC) $(OBJ_BON) $(LIBS) $(HEADERS) -o $(NAME_BON)

all: $(LIBFT_A) $(NAME)

bonus: $(LIBFT_A) $(NAME_BON)

clean:
	rm -f $(OBJ)
	rm -f $(OBJ_BON)
	rm -d $(BUILD)

fclean: clean
	rm -f $(BUILD)$(NAME)
	rm -f $(BUILD)$(NAME_BON)

re: fclean all

rebonus: fclean bonus

.PHONY: all, clean, fclean, re, libmlx
