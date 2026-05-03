#include <stdio.h>

#include "rastvorenie.h"
#include "razbavlenie.h"
int main() {
  printf("Выберите желаемый расчет.\n");
  printf("1 - Растворение твердого вещества в воде в мерной колбе.\n");
  printf("2 - Разбавлене жидкого реагента.\n");
  short a;  // Выбор режима работы проги, 1 или 2
  scanf("%hd", &a);
  if (a == 1) {
    rastvorenie();
  } else if (a == 2) {
    razbavlenie();
  } else
    printf("Некорректный выбор режима программы.");
  return 0;
}
