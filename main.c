#include <stdio.h>
#include <string.h>
#include "cJSON.h"
#include <stdlib.h>

#include "rastvorenie.h"
#include "razbavlenie.h"
#include "first_pars.h"
#include "razbavlenie_baza.h"
#include "rastvorenie_baza.h"
int main() {
  char *data = first_pars(); // Выгрузка базы данных в память 
  if(!data){
    printf("Ошибка чтения файла");
    return 1;
  }
  printf("Введите название реактива.\n");
  char name[50]; // Место хранение вводимого реактива
  if(fgets(name, sizeof(name), stdin)){ // Прием вводимого значение и запись его в name
    name[strcspn(name, "\n")] = '\0'; // Замена \n в конце на \0
  }
  cJSON *root = cJSON_Parse(data); // Построение древа для чтения базы данных
  if(!root){
    printf("Ошибка парсинга.");
    free(data);
    return 1;
  }
  short b = 0; // Проверка есть ли реактив для потом
  cJSON *comp = cJSON_GetObjectItem(root, name); // Поиск нужного реактива по древу
  if(!comp){
    printf("Реактива нет в базе данных.\n");
    printf("Необхожимо ввести некоторые данные вручную.\n");
    b = 1; // Ввод ручками
  }
  else{
    printf("Реактив найден.\n");
    b = 2;
  }
  printf("Выберите желаемый расчет.\n");
  printf("1 - Растворение твердого вещества в воде в мерной колбе.\n");
  printf("2 - Разбавлене жидкого реактива.\n");
  short a;  // Выбор режима работы проги, 1 или 2
  scanf("%hd", &a);
  if (a == 1 && b == 1) {
    rastvorenie();
  } 
  else if (a == 2 && b == 1) {
    razbavlenie();
  } 
  else if (a == 2 && b == 2){
    razb_baza(comp);
  }
  else if (a == 1 && b == 2){
    rast_baza(comp);
  }
  else
    printf("Некорректный выбор режима программы.");
  return 0;
}
