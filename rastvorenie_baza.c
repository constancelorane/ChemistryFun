#include <stdio.h>
#include "cJSON.h"
/*Подробное описание кода смотри в фале razbavlenie_baza*/ 
int rast_baza(cJSON *comp){
    printf("Введите необходимый объем реактива.\n");
    double v = 0;
    scanf("%lf", &v);
    printf("Введите необходимую концентрацию реактива.\n");
    double c2 = 0;
    scanf("%lf", &c2);
    cJSON *arr = cJSON_GetObjectItem(comp, "data"); // Выбор определенного реактива в базе данных
    int size = cJSON_GetArraySize(arr); // Определение объема массива именно одного реактива
    int i = 0;
    double konc_pred2 = 0;
    double plot_pred2 = 0;
    double konc2 = 0;
    double plot2 = 0;
    for (i = 0; i < size; i++){ // Цикл для определения ближайших значений нужной концентрации
        cJSON *pair = cJSON_GetArrayItem(arr, i); // Комментарии смотри в цикле выше, он такой же
        cJSON *x = cJSON_GetArrayItem(pair, 0);
        cJSON *y = cJSON_GetArrayItem(pair, 1);
        konc2 = x -> valuedouble;
        plot2 = y -> valuedouble;
        if(c2 > konc_pred2 && c2 < konc2){
            break;
        }
        else if(konc2 == c2){
            break;
        }
        konc_pred2 = konc2;
        plot_pred2 = plot2;
        }
    double nuz_plot2 = 0; // Плотность при нужной концентрации
    if(konc2 == c2){
        nuz_plot2 = plot2;
    }
    else{
        nuz_plot2 = plot_pred2 + (((c2 - konc_pred2) * (plot2 - plot_pred2)) / (konc2 - konc_pred2)); // Интерполяция плотности
    }
    double m; // Масса конечного реактива
    m = v * nuz_plot2;
    double m1; // Масса чистого реактива в конечном растворе
    m1 = m * c2 / 100;
    printf("Вам необходимо добавить %.2lf грамм твердого вещества и залить водой до метки.\n", m1);
    return 0;
}