#include <TXLib.h>
#include <stdio.h>
#include <math.h>

int Solver(double a, double b, double c, double *x1, double *x2) {
    if (a == 0.0) {
        if (b == 0.0) {
            return (c == 0.0) ? 3 : 0;  /* 3 = infinity */
        }
        else {
            *x1 = *x2 = - c / b;
            return 1;
        }
    }

    else {
        double d = b * b - 4 * a * c;
        if (d == 0.0) {
            *x1 = *x2 = - b / (2 * a);
            return 1;
        }
        else if (d > 0) {
            double sqrt_d = sqrt(d);
            *x1 = (- b + sqrt_d) / (2 * a);
            *x2 = (- b - sqrt_d) / (2 * a);

            return 2;
        }
        else return 4; /* 4 - d<0 */
    }
}


int main() {

    printf("This program solves square equations\n");
    printf("Enter a,b,c through a space (probel)\n");

    double a = 0, b = 0, c = 0; /* koefficients */
    scanf("%lg %lg %lg", &a, &b, &c);
    printf("----------\n");


    double x1 = 0, x2 = 0; /* solves */
    int nRoots = Solver(a,b,c, &x1, &x2); /* number of solves */

    switch(nRoots) {
        case 0:
            printf("no solves!");
            break;

        case 1:
            printf("x = %lf", x1);
            break;

        case 2:
            printf("x1 = %lf, x2 = %lf", x1, x2);
            break;

        case 3:
            printf("infinity solves!");
            break;

        case 4:
            printf("d < 0! zero solves or error");

        default:
            printf("error! nRoots = %d", nRoots);
            break
    }
    return 0;
}
