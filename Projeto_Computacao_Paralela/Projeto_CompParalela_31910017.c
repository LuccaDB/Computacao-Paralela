//Lucca Dias Bartholomei - 31910017
//gcc-11 Projeto_CompParalela_31910017.c -o teste -fopenmp -lm
#include <stdio.h>
#include <stdlib.h>
#include <omp.h>
#include <time.h>

#define t_tot 100
#define T 1000

double h, sum = 0;
double local_n = (double)(T/t_tot);

void function(double* sum);
void soma();

int main(){
    int para = 0;

    time_t t_ini;
    time(&t_ini);

    long counter = 0;
    while(para == 0){
        if(counter%100 == 0 && counter > 0){
            printf("Digite:\n");
            printf("0 - Continuar   |   1 - Parar\n");
            scanf("%i", &para);
            printf("\n");
            if(para != 0)break;
        }
        soma();
        counter++;
    }
    time_t t_fim;
    time(&t_fim); 

    double dt = difftime(t_fim, t_ini);
    printf("Resultado: %f \n", sum);
    return 0;
}

void soma(){
    #pragma omp parallel num_threads(t_tot)
        function(&sum);
}

void function(double* sum){
    long my_rank = omp_get_thread_num();
    int my_first_i =local_n*my_rank;
    int my_last_i = my_first_i + local_n;

    double my_sum = 0;
    for(int i = my_first_i; i< my_last_i; i++)my_sum += i>0 ? (double)(1/i) : 0;
    printf("Soma: %f \n", my_sum);
    #pragma omp critical
        *sum += (double)my_sum/100;
}
