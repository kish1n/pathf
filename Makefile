# Указываем компилятор и флаги
CC = clang
CFLAGS = -std=c11 -Wall -Wextra -Werror -Wpedantic

# Пути к директориям
SRC_DIR = ./src
LIBMX_SRC_DIR = ./libmx/src
INC_DIR = ./inc
LIBMX_INC_DIR = ./libmx/inc
OBJ_DIR = ./obj

# Название библиотеки и программы
LIB_NAME = libmx.a
TARGET = pathfinder

# Находим все .c файлы и превращаем их в объектные файлы
SRC_FILES = $(wildcard $(SRC_DIR)/*.c)
LIBMX_SRC_FILES = $(wildcard $(LIBMX_SRC_DIR)/*.c)
OBJ_FILES = $(SRC_FILES:$(SRC_DIR)/%.c=$(OBJ_DIR)/%.o)
LIBMX_OBJ_FILES = $(LIBMX_SRC_FILES:$(LIBMX_SRC_DIR)/%.c=$(OBJ_DIR)/%.o)

# Правило для сборки программы
all: $(TARGET)

# Правило для сборки библиотеки и программы
$(TARGET): $(OBJ_FILES) $(LIB_NAME)
	$(CC) $(CFLAGS) -o $@ $(OBJ_FILES) -L. -lmx

# Правило для сборки библиотеки libmx
$(LIB_NAME): $(LIBMX_OBJ_FILES)
	ar rcs $@ $^

# Компиляция объектных файлов для программы
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	@mkdir -p $(OBJ_DIR)
	$(CC) $(CFLAGS) -I$(INC_DIR) -I$(LIBMX_INC_DIR) -c $< -o $@

# Компиляция объектных файлов для библиотеки
$(OBJ_DIR)/%.o: $(LIBMX_SRC_DIR)/%.c
	@mkdir -p $(OBJ_DIR)
	$(CC) $(CFLAGS) -I$(LIBMX_INC_DIR) -c $< -o $@

# Очистка собранных файлов
clean:
	rm -rf $(OBJ_DIR)

# Полная очистка
fclean: clean
	rm -f $(TARGET) $(LIB_NAME)

# Пересобрать все с нуля
re: fclean all

run:
	make
