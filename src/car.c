/* car.c
 * Автор: Янушкевич Максим
 * Группа: 12
 */

/*
 * Реализация функций для работы со структурой "Автомобиль".
 */

#include "car.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>

/* Создаёт тестовый файл с данными */
void create_test_file(const char *filename, int count)
{
    FILE *file = fopen(filename, "w");
    if (file == NULL) {
        printf("Ошибка: не удалось создать файл %s\n", filename);
        return;
    }

    /* Массивы для генерации тестовых данных */
    const char *brands[] = {"Audi", "BMW", "Mercedes", "Toyota", "Honda", "Ford", "Volkswagen", "Audi", "Audi", "Renault"};
    const char *colors[] = {"Красный", "Синий", "Чёрный", "Белый", "Серебристый", "Зелёный", "Жёлтый", "Серый", "Коричневый", "Бежевый"};
    int current_year = 2026;
    
    /* Инициализируем генератор случайных чисел */
    srand(time(NULL));
    
    fprintf(file, "%s\t%s\t%s\t%s\t%d\t%d\t%.2f\n", 
            "Марка", "Цвет", "Серийный номер", "Рег. номер", "Год выпуска", "Год техосмотра", "Цена");
    
    for (int i = 0; i < count; i++) {
        /* Выбираем случайные данные */
        const char *brand = brands[rand() % 10];
        const char *color = colors[rand() % 10];
        char serial[20];
        char reg_number[20];
        
        /* Генерируем серийный номер */
        sprintf(serial, "SN%04d", rand() % 10000);
        
        /* Генерируем регистрационный номер */
        sprintf(reg_number, "%c%03d%c%c", 
                'A' + (rand() % 26), 
                rand() % 1000,
                'A' + (rand() % 26),
                'A' + (rand() % 26));
        
        /* Год выпуска: от 2010 до 2025 */
        int year_manuf = 2010 + (rand() % 16);
        
        /* Год техосмотра: от года выпуска до 2026 */
        int year_insp = year_manuf + (rand() % (current_year - year_manuf + 1));
        
        /* Цена: от 5000 до 50000 */
        float price = (5000 + (rand() % 45001)) / 1.0;
        
        fprintf(file, "%s\t%s\t%s\t%s\t%d\t%d\t%.2f\n", 
                brand, color, serial, reg_number, year_manuf, year_insp, price);
    }
    
    fclose(file);
    printf("Создан тестовый файл '%s' с %d записями\n", filename, count);
}

/* Читает данные из файла */
int read_cars_from_file(const char *filename, Car cars[], int max_count)
{
    FILE *file = fopen(filename, "r");
    if (file == NULL) {
        printf("Ошибка: не удалось открыть файл %s\n", filename);
        return 0;
    }
    
    char buffer[256];
    int count = 0;
    
    /* Пропускаем заголовок */
    fgets(buffer, sizeof(buffer), file);
    
    while (fgets(buffer, sizeof(buffer), file) != NULL && count < max_count) {
        /* Убираем символ новой строки */
        buffer[strcspn(buffer, "\n")] = 0;
        
        /* Разбираем строку на поля (разделитель - табуляция) */
        char *token = strtok(buffer, "\t");
        if (token) strncpy(cars[count].brand, token, MAX_STRING);
        
        token = strtok(NULL, "\t");
        if (token) strncpy(cars[count].color, token, MAX_STRING);
        
        token = strtok(NULL, "\t");
        if (token) strncpy(cars[count].serial, token, MAX_STRING);
        
        token = strtok(NULL, "\t");
        if (token) strncpy(cars[count].reg_number, token, MAX_STRING);
        
        token = strtok(NULL, "\t");
        if (token) cars[count].year_manufacture = atoi(token);
        
        token = strtok(NULL, "\t");
        if (token) cars[count].year_inspection = atoi(token);
        
        token = strtok(NULL, "\t");
        if (token) cars[count].price = atof(token);
        
        count++;
    }
    
    fclose(file);
    return count;
}

/* Выводит информацию об автомобиле */
void print_car(const Car *car)
{
    printf("  Марка: %s\n", car->brand);
    printf("  Цвет: %s\n", car->color);
    printf("  Серийный номер: %s\n", car->serial);
    printf("  Рег. номер: %s\n", car->reg_number);
    printf("  Год выпуска: %d\n", car->year_manufacture);
    printf("  Год техосмотра: %d\n", car->year_inspection);
    printf("  Цена: %.2f\n", car->price);
    printf("  ------------------------\n");
}

/* Выводит все автомобили */
void print_all_cars(const Car cars[], int count)
{
    printf("\n=== Список всех автомобилей (%d шт.) ===\n", count);
    for (int i = 0; i < count; i++) {
        printf("\nАвтомобиль %d:\n", i + 1);
        print_car(&cars[i]);
    }
}

/* Проверяет, является ли автомобиль Audi старше 3 лет */
int is_audi_older_than_3(const Car *car, int current_year)
{
    /* Проверяем марку (без учёта регистра) */
    if (strcasecmp(car->brand, "Audi") != 0) {
        return 0;
    }
    
    /* Вычисляем возраст автомобиля */
    int age = current_year - car->year_manufacture;
    
    return (age > 3);
}

/* Находит автомобили Audi старше 3 лет */
int find_audi_older_than_3(const Car cars[], int count, Car result[], int current_year)
{
    int found = 0;
    
    for (int i = 0; i < count; i++) {
        if (is_audi_older_than_3(&cars[i], current_year)) {
            result[found] = cars[i];
            found++;
        }
    }
    
    return found;
}

/* Сохраняет массив автомобилей в файл */
void save_cars_to_file(const char *filename, const Car cars[], int count)
{
    FILE *file = fopen(filename, "w");
    if (file == NULL) {
        printf("Ошибка: не удалось создать файл %s\n", filename);
        return;
    }
    
    fprintf(file, "%s\t%s\t%s\t%s\t%s\t%s\t%s\n", 
            "Марка", "Цвет", "Серийный номер", "Рег. номер", "Год выпуска", "Год техосмотра", "Цена");
    
    for (int i = 0; i < count; i++) {
        fprintf(file, "%s\t%s\t%s\t%s\t%d\t%d\t%.2f\n", 
                cars[i].brand,
                cars[i].color,
                cars[i].serial,
                cars[i].reg_number,
                cars[i].year_manufacture,
                cars[i].year_inspection,
                cars[i].price);
    }
    
    fclose(file);
    printf("\nРезультаты сохранены в файл '%s' (%d записей)\n", filename, count);
}
