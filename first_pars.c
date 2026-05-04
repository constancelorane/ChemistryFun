#include "first_pars.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <cjson/cJSON.h>
char* first_pars(const char* filename){ // Функция для первичного парсинга файла
    FILE* f = fopen(filename, "r"); // Задаем имя файла f открытием data только для чтения
    if (!f) return NULL; // Если файл по какой-либо причине не открылся, возвращаем null
    fseek(f, 0, SEEK_END); // Перемещаем курсор в конец файла
    long size = ftell(f); // размер файла = позиция курсора
    rewind(f); // Возвращаем курсор в начало файла
    char* data = malloc(size + 1); // Выделение необходимого количества памяти с учетом '\0'
    if (!data) { // Если памяти не хватит, то вернется null
        fclose(f);
        return NULL;
    }
    if(fread(data, 1, size, f) != size){// Чтение файла, запись в data, если прочитал меньше, то файл оборвался
        fclose(f);
        free(data);
        return NULL;
    }
    data[size] = '\0';
    fclose(f);
    return data;
}