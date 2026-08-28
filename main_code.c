#include <TXLib.h>
#include <stdio.h>
#include <math.h>

#define ZERO_BORDER 10e-6

struct Square_Example {
    double a, b, c;
    int nRoots;
    double x1, x2;
} ;

int Is_Zero(double x);
int Are_Equal(double num1, double num2);
int Solver(double a, double b, double c, double *x1, double *x2);
void Test(struct Square_Example example);
void RunAllTests();

/* checks double to be near zero */
int Is_Zero(double x) {
    if ((- ZERO_BORDER <= x) && (x <= ZERO_BORDER)) {
        return 1;
    }
    else {
        return 0;
    }
}

/* compares equal or part-equal double */
int Are_Equal(double num1, double num2) {
    if (Is_Zero(num1 - num2)) {
        return 1;
    }
    else {
        return 0;
    }
}

/* solver function */
int Solver(double a, double b, double c, double *x1, double *x2) {

    if (Is_Zero(a)) {
        if (Is_Zero(b)) {
            return (Is_Zero(c)) ? -1 : 0;  /* -1 = infinity */
        }
        else {
            *x1 = *x2 = - c / b;
            return 1;
        }
    }
    else {
        double d = b * b - 4 * a * c;

        if (Is_Zero(d)) {
            *x1 = *x2 = - b / (2 * a);
            return 1;
        }
        else if (d > 0) {
            double sqrt_d = sqrt(d);
            *x1 = (- b + sqrt_d) / (2 * a);
            *x2 = (- b - sqrt_d) / (2 * a);

            return 2;
        }
        else return 0;
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
        printf("------> error!\n");
        printf("expected nRoots = %d\n", nRoots_example);
        printf("got nRoots = %d\n", nRoots);
    }
}

void RunAllTests() {

    struct Square_Example unit_tests[10];


    unit_tests[0] = {.a = 1, .b = 2, .c = 1, .nRoots = 1, .x1 = -1, .x2 = -1};
    unit_tests[1] = {.a = 1, .b = -2, .c = 1, .nRoots = 2, .x1 = 1, .x2 = 3}; /* wrong, nRoots = 1 */
    unit_tests[2] = {.a = 1, .b = 2, .c = 3, .nRoots = 0, .x1 = 0, .x2 = 0};
    unit_tests[3] = {.a = 0, .b = 1, .c = 2, .nRoots = 1, .x1 = -2, .x2 = -2};
    unit_tests[4] = {.a = 1, .b = -4, .c = -21, .nRoots = 2, .x1 = 5, .x2 = 4}; /*wrong, x1 = 7, x2 = -3 */
    unit_tests[5] = {.a = 0, .b = 0, .c = 0, .nRoots = -1, .x1 = 0, .x2 = 0};
    unit_tests[6] = {.a = 0, .b = 0, .c = 1, .nRoots = 0, .x1 = 0, .x2 = 0};
    unit_tests[7] = {.a = 0.3333333, .b = 2, .c = 3, .nRoots = 1, .x1 = -3, .x2 = -3};
    unit_tests[8] = {.a = 5, .b = 3, .c = 10, .nRoots = 2, .x1 = 0, .x2 = 0}; /*wrong, nRoots = 0 */
    unit_tests[9] = {.a = 0, .b = 0, .c = 15, .nRoots = 0, .x1 = 0, .x2 = 0};


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

    int nRoots = Solver(a, b, c, &x1, &x2); /* number of solutions */

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

        case -1:
            printf("infinity solves!");
            break;

        default:
            printf("error! nRoots = %d", nRoots);
            break;
    }
    printf("\n");
    return 0;
}
