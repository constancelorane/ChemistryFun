#include <stdio.h>
#include <cjson/cJSON.h>
int razb_baza(cJSON *comp){
    printf("Введите необходимый объем реактива.\n");
    double v = 0;
    scanf("%lf", &v);
    printf("Введите начальную концентрацию реактива.\n");
    double c1 = 0;
    scanf("%lf", &c1);
    printf("Введите необходимую концентрацию реактива.\n");
    double c2 = 0;
    scanf("%lf", &c2);
    cJSON *arr = cJSON_GetObjectItem(comp, "data"); // Выбор определенного реактива в базе данных
    int size = cJSON_GetArraySize(arr); // Определение объема массива именно одного реактива
    int i = 0;
    double konc_pred1 = 0; // Предыдущая концентрация для цикла
    double plot_pred1 = 0; // Предыдущая плотность для цикла
    double konc1 = 0; // Концентрация в цикле
    double plot1 = 0; // Плотность в цикле
    for (i = 0; i < size; i++){ // Цикл для определения ближайших значений начальной концентрации
        cJSON *pair = cJSON_GetArrayItem(arr, i); // Определение одной пары значений концентрация - плотность
        cJSON *x = cJSON_GetArrayItem(pair, 0); // Определение значения концентрации в паре
        cJSON *y = cJSON_GetArrayItem(pair, 1); // Определение значения плотности в паре
        konc1 = x -> valuedouble; // Присвоение значения концентрации переменной
        plot1 = y -> valuedouble; // Присвоение значения плотности переменной 
        if(c1 > konc_pred1 && c1 < konc1){ // Обрыв цикла for если нужная концентрация попала в промежуток
            break;
        }
    else if(konc1 == c1){ // Обрыв цикла for если нужная концентрация оказалась записанной в базе данных
        break;
        }
    konc_pred1 = konc1;
    plot_pred1 = plot1;
    }
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
    double nuz_plot1 = 0; // Плотность при исходной концентрации 
    if(konc1 == c1){
        nuz_plot1 = plot1;
    }    
    else{
        nuz_plot1 = plot_pred1 + (((c1 - konc_pred1) * (plot1 - plot_pred1)) / (konc1 - konc_pred1)); // Интерполяция плотности    
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
    double m2; // Сколько чистого реактива содержиться в исходном
    m2 = m1 * 100 / c1;
    double v1; // Сколько нужно взять исходного реактива по объему
    v1 = m2 / nuz_plot1;
    double v2; // Сколько нужно взять воды
    v2 = m - m2;
    printf("Необхожимое количество реактива: %.2lf мл.\n", v1);
    printf("Необходимое количество воды: %.2lf мл.\n", v2);
    return 0;
}
