/* car.h
 * Автор: Янушкевич Максим
 * Группа: 12
 */

#ifndef CAR_H
#define CAR_H

/*
 * Заголовочный файл модуля работы со структурой "Автомобиль".
 * Содержит определение структуры и объявления функций.
 */

#define MAX_STRING 50   /* Максимальная длина строковых полей */
#define MAX_CARS 100    /* Максимальное количество автомобилей */

/* Структура "Автомобиль" */
typedef struct {
    char brand[MAX_STRING];      /* Марка */
    char color[MAX_STRING];      /* Цвет */
    char serial[MAX_STRING];     /* Серийный номер */
    char reg_number[MAX_STRING]; /* Регистрационный номер */
    int year_manufacture;        /* Год выпуска */
    int year_inspection;         /* Год техосмотра */
    float price;                 /* Цена */
} Car;

/*
 * Создаёт тестовый файл с данными об автомобилях.
 * filename - имя создаваемого файла
 * count - количество записей
 */
void create_test_file(const char *filename, int count);

/*
 * Читает данные об автомобилях из файла.
 * filename - имя файла для чтения
 * cars - массив для заполнения
 * max_count - максимальное количество записей
 * Возвращает фактическое количество прочитанных записей
 */
int read_cars_from_file(const char *filename, Car cars[], int max_count);

/*
 * Выводит информацию об автомобиле на экран.
 */
void print_car(const Car *car);

/*
 * Выводит все автомобили из массива на экран.
 */
void print_all_cars(const Car cars[], int count);

/*
 * Проверяет, является ли автомобиль Audi старше 3 лет.
 * Текущий год передаётся для расчёта возраста.
 */
int is_audi_older_than_3(const Car *car, int current_year);

/*
 * Находит автомобили Audi старше 3 лет.
 * cars - исходный массив
 * count - количество записей в исходном массиве
 * result - массив для результатов
 * current_year - текущий год для расчёта возраста
 * Возвращает количество найденных автомобилей
 */
int find_audi_older_than_3(const Car cars[], int count, Car result[], int current_year);

/*
 * Сохраняет массив автомобилей в файл.
 * filename - имя файла для сохранения
 * cars - массив для сохранения
 * count - количество записей
 */
void save_cars_to_file(const char *filename, const Car cars[], int count);

#endif /* CAR_H */
