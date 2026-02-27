# Makefile для tpmp-lab2-task4
# Автор: Янушкевич Максим
# Группа: 12

# Компилятор и флаги
CC = gcc
CFLAGS = -Iinclude -Wall -Wextra -std=c99 -g
LDFLAGS =

# Директории
SRC_DIR = src
INCLUDE_DIR = include
OBJ_DIR = obj
BIN_DIR = bin
DATA_DIR = data

# Исходные файлы
SRCS = $(SRC_DIR)/main.c $(SRC_DIR)/car.c
OBJS = $(OBJ_DIR)/main.o $(OBJ_DIR)/car.o
TARGET = $(BIN_DIR)/lab4-task24

# Цель по умолчанию
all: $(TARGET) | $(DATA_DIR)

# Сборка исполняемого файла
$(TARGET): $(OBJS) | $(BIN_DIR)
	$(CC) $(OBJS) -o $@ $(LDFLAGS)
	@echo "Сборка завершена. Исполняемый файл: $@"

# Компиляция main.c
$(OBJ_DIR)/main.o: $(SRC_DIR)/main.c $(INCLUDE_DIR)/car.h | $(OBJ_DIR)
	$(CC) $(CFLAGS) -c $< -o $@

# Компиляция car.c
$(OBJ_DIR)/car.o: $(SRC_DIR)/car.c $(INCLUDE_DIR)/car.h | $(OBJ_DIR)
	$(CC) $(CFLAGS) -c $< -o $@

# Создание директорий
$(BIN_DIR) $(OBJ_DIR) $(DATA_DIR):
	mkdir -p $@

# Очистка проекта
clean:
	rm -rf $(OBJ_DIR) $(BIN_DIR) $(DATA_DIR)
	@echo "Проект очищен."

# Запуск программы
run: $(TARGET)
	$(TARGET)

# Для GitHub Actions
check: all
	@echo "Проверка сборки завершена."

# Просмотр результатов
show:
	@if [ -f $(DATA_DIR)/audi_older_3.txt ]; then \
		echo "=== Содержимое файла с результатами ==="; \
		cat $(DATA_DIR)/audi_older_3.txt; \
	else \
		echo "Файл с результатами ещё не создан. Запустите программу."; \
	fi

# Псевдо-цели
.PHONY: all clean run check show
