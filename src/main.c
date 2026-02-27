/* main.c
 * Автор: Янушкевич Максим
 * Группа: 12
 */

/*
 * Клиентская программа для задания 4 варианта 24.
 * Обработка данных об автомобилях из файла.
 */

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "car.h"

int main(void)
{
    const char *input_file = "data/cars.txt";
    const char *output_file = "data/audi_older_3.txt";
    const int current_year = 2026;
    
    Car all_cars[MAX_CARS];
    Car audi_cars[MAX_CARS];
    
    printf("\n========================================\n");
    printf("ЗАДАНИЕ 4, ВАРИАНТ 24 (пункт 4)\n");
    printf("Автомобили марки Audi старше 3 лет\n");
    printf("========================================\n\n");
    
    /* 1. Создаём тестовый файл */
    printf("--- Шаг 1: Создание тестового файла ---\n");
    create_test_file(input_file, 20);
    
    /* 2. Читаем данные из файла */
    printf("\n--- Шаг 2: Чтение данных из файла ---\n");
    int count = read_cars_from_file(input_file, all_cars, MAX_CARS);
    if (count == 0) {
        printf("Ошибка: не удалось прочитать данные\n");
        return EXIT_FAILURE;
    }
    printf("Прочитано %d записей\n", count);
    
    /* 3. Выводим все прочитанные данные */
    printf("\n--- Шаг 3: Просмотр содержимого файла ---\n");
    print_all_cars(all_cars, count);
    
    /* 4. Ищем Audi старше 3 лет */
    printf("\n--- Шаг 4: Поиск Audi старше 3 лет ---\n");
    int found = find_audi_older_than_3(all_cars, count, audi_cars, current_year);
    
    if (found == 0) {
        printf("Автомобили Audi старше 3 лет не найдены.\n");
    } else {
        printf("Найдено автомобилей Audi старше 3 лет: %d\n", found);
        printf("\nСписок найденных автомобилей:\n");
        for (int i = 0; i < found; i++) {
            printf("\nAudi %d:\n", i + 1);
            printf("  Год выпуска: %d\n", audi_cars[i].year_manufacture);
            printf("  Цвет: %s\n", audi_cars[i].color);
            printf("  Рег. номер: %s\n", audi_cars[i].reg_number);
            printf("  Цена: %.2f\n", audi_cars[i].price);
        }
    }
    
    /* 5. Сохраняем результаты */
    printf("\n--- Шаг 5: Сохранение результатов ---\n");
    save_cars_to_file(output_file, audi_cars, found);
    
    printf("\n========================================\n");
    printf("Программа завершена.\n");
    printf("========================================\n");
    
    return EXIT_SUCCESS;
}
