CC = clang
CFLAGS = -std=c11 -Wall -Wextra -Werror -Wpedantic

LIB_NAME = libmx.a

SRC_DIR = src
OBJ_DIR = obj
INC_DIR = inc

SRC_FILES = $(wildcard $(SRC_DIR)/*.c)
OBJ_FILES = $(patsubst $(SRC_DIR)/%.c, $(OBJ_DIR)/%.o, $(SRC_FILES))

INC_FILES = $(wildcard $(INC_DIR)/*.h)

all: $(LIB_NAME)

$(LIB_NAME): $(OBJ_FILES)
	ar rcs $@ $^

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c $(INC_FILES)
	@mkdir -p $(OBJ_DIR)
	$(CC) $(CFLAGS) -I$(INC_DIR) -c $< -o $@

clean:
	rm -rf $(OBJ_DIR)

fclean: clean
	rm -f $(LIB_NAME)

re: fclean all

.PHONY: all clean fclean re
