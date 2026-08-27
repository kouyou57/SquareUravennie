#include <TXLib.h>
#include <stdio.h>
#include <math.h>

#define ZERO_BORDER 0.0000009

struct Square_Example {
    double a, b, c;
    int nRoots;
    double x1, x2;
} ;

int Are_Equal(double num1, double num2);
int Solver(double a, double b, double c, double *x1, double *x2);
void Test(struct Square_Example example);
void RunAllTests();

/* compares equal or part-equal double. kills warnings. no warnings, no problems */
int Are_Equal(double num1, double num2) {
    if (fabs(num1 - num2) <= ZERO_BORDER) {
        return 1;
    }
    else {
        return 0;
    }
}

/* solver function */
int Solver(double a, double b, double c, double *x1, double *x2) {

    if (Are_Equal(a, 0)) {
        if (Are_Equal(b, 0)) {
            return (Are_Equal(c, 0)) ? 3 : 0;  /* 3 = infinity */
        }
        else {
            *x1 = *x2 = - c / b;
            return 1;
        }
    }
    else {
        double d = b * b - 4 * a * c;

        if (Are_Equal(d, 0)) {
            *x1 = *x2 = - b / (2 * a);
            return 1;
        }
        else if (d > ZERO_BORDER) {
            double sqrt_d = sqrt(d);
            *x1 = (- b + sqrt_d) / (2 * a);
            *x2 = (- b - sqrt_d) / (2 * a);

            return 2;
        }
        else return 4; /* 4 - d<0 */
    }
}

/* one test */
void Test(struct Square_Example example) {
    double a = example.a;
    double b = example.b;
    double c = example.c;
    int nRoots_example = example.nRoots;
    double x1_example = example.x1;
    double x2_example = example.x2;


    double x1 = 0, x2 = 0;

    int nRoots = Solver(a, b, c, &x1, &x2);

    if (nRoots == nRoots_example) {
        if ((nRoots == 1) || (nRoots == 2)) {

            if ((Are_Equal(x1, x1_example)) && (Are_Equal(x2, x2_example))) {
                printf("ok\n");
            }
            else {
                printf("------> error!!\n");
                printf("nRoots ok, nRoots = %d\n", nRoots);
                printf("expected x1 = %lf, x2 = %lf\n", x1_example, x2_example);
                printf("got x1 = %lf, x2 = %lf\n", x1, x2);
            }
        }
        else {
            printf("ok\n");
        }
    }
    else {
        printf("------> error!!\n");
        printf("expected nRoots = %d\n", nRoots_example);
        printf("got nRoots = %d\n", nRoots);
    }
}

void RunAllTests() {

    struct Square_Example ex0 = {.a = 1, .b = 2, .c = 1, .nRoots = 1, .x1 = -1, .x2 = -1};
    struct Square_Example ex1 = {.a = 1, .b = -2, .c = 1, .nRoots = 2, .x1 = 1, .x2 = 3}; /* wrong */
    struct Square_Example ex2 = {.a = 1, .b = 2, .c = 3, .nRoots = 4, .x1 = 0, .x2 = 0};
    struct Square_Example ex3 = {.a = 0, .b = 1, .c = 2, .nRoots = 1, .x1 = -2, .x2 = -2};
    struct Square_Example ex4 = {.a = 1, .b = -4, .c = -21, .nRoots = 2, .x1 = 7, .x2 = -3};
    struct Square_Example ex5 = {.a = 0, .b = 0, .c = 0, .nRoots = 3, .x1 = 0, .x2 = 0};
    struct Square_Example ex6 = {.a = 0, .b = 0, .c = 1, .nRoots = 0, .x1 = 0, .x2 = 0};
    struct Square_Example ex7 = {.a = 0.3333333, .b = 2, .c = 3, .nRoots = 1, .x1 = -3, .x2 = -3};
    struct Square_Example ex8 = {.a = 5, .b = 3, .c = 10, .nRoots = 4, .x1 = 0, .x2 = 0};
    struct Square_Example ex9 = {.a = 0, .b = 0, .c = 15, .nRoots = 0, .x1 = 0, .x2 = 0};

    struct Square_Example unit_tests[10] = {ex0, ex1, ex2, ex3, ex4, ex5, ex6, ex7, ex8, ex9} ;

    int number_of_tests = sizeof(unit_tests)/sizeof(unit_tests[0]);
    for (int i=0; i < number_of_tests; i++) {
        Test(unit_tests[i]);
    }

}

int main() {

    RunAllTests();

    printf("\n\n\n------------------\n");
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
    printf("\n");
    return 0;
}
