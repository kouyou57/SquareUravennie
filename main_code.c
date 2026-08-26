#include <TXLib.h>
#include <stdio.h>
#include <math.h>

struct Refference {
    double a,b,c;
    int nRoots_r;
    double x1_r, x2_r;
}
;

/* solver function */
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
        printf("d = %.20lf\n", d);
        if (d <= 0.0000009) {
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

/* one test */
int Test(double a, double b, double c, int nRoots_r, double x1_r, double x2_r) {
    double x1 = 0, x2 = 0;

    int nRoots = Solver(a,b,c, &x1, &x2);

    if (nRoots == nRoots_r) {
        if ((x1 == x1_r) && (x2 == x2_r)) {
            printf("ok");
            return 0; /* ok */
        }
        else {
            printf("------> error!!\n");
            printf("nRoots ok, nRoots = %d", nRoots);
            printf("expected x1 = %lf, x2 = %lf", x1_r, x2_r);
            printf("got x1 = %lf, x2 = %lf", x1, x2);
            return 1; /* wrong solutions */
        }
    }
    else {
        printf("------> error!!\n");
        printf("expected nRoots = %d\n");
        printf("got nRoots = %d", nRoots_r, nRoots);
        return 2; /* wrong number of solutions */
    }
}

void RunAllTests() {

}

int main() {

    printf("This program solves square equations\n");
    printf("Enter a,b,c through a space (probel)\n");

    double a = 0, b = 0, c = 0; /* koefficients */
    scanf("%lg %lg %lg", &a, &b, &c);
    printf("----------\n");


    double x1 = 0, x2 = 0; /* solutions */

    int nRoots = Solver(a,b,c, &x1, &x2); /* number of solutions */

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
            break;

        default:
            printf("error! nRoots = %d", nRoots);
            break;
    }
    return 0;
}
