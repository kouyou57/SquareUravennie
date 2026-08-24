#include <TXLib.h>
#include <stdio.h>
#include <math.h>

int Solver(double a, double b, double c, double *x1, double *x2) {
    if (a==0) {
        if (b==0) {
            return (c==0)? 3 : 0;  /* 3 = infinity */
            }
        else {
        *x1 = *x2 = -c/b;
        return 1;
        }
    }

    else {
        double d = b*b - 4*a*c;
        if (d==0) {
            *x1 = *x2 = -b / (2*a);
            return 1;
        }
        else {
            double sqrt_d = sqrt(d);
            *x1 = (-b + sqrt_d) / (2.0 * a);
            *x2 = (-b - sqrt_d) / (2.0 * a);

            return 2;
        }
}
}


int main() {
    double a,b,c;
    double x1, x2;

    printf("Ёта программа решает квадратные уравнени€\n");
    printf("¬ведите коэффициенты через пробел\n");

    scanf("%lg %lg %lg\n", &a, &b, &c);
    printf("----------");

    int nRoots = Solver(a,b,c, &x1, &x2); /*количество решений и корни*/

    switch(nRoots) {
        case 0: printf("нет решений!");
                break;

        case 1: printf("x = %lg", x1);
                break;

        case 2: printf("x1 = %lg, x2 = %lg", x1, x2);
                break;

        case 3: printf("бесконечно много решений!");
                       break;

        default: printf("error!!! nRoots = %d", nRoots);

    return 0;

}
 }
