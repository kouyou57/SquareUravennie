#include <TXLib.h>
#include <stdio.h>
#include <math.h>

#define ZERO_BORDER 1e-6

struct SquareExample {
    double a, b, c;
    int nRoots;
    double x1, x2;
} ;

enum Roots {
    inf_roots = -1,
    zero_roots = 0,
    one_root = 1,
    two_roots = 2,

} ;

int IsZero(double x);
int AreEqual(double num1, double num2);
int Solver(double a, double b, double c, double *x1, double *x2);
void Test(struct SquareExample ex);
void RunAllTests();

/* checks double to be near zero */
int IsZero(double x) {
    return fabs(x) <= ZERO_BORDER;
}

/* compares equal or part-equal double */
int AreEqual(double num1, double num2) {
    return IsZero(num1 - num2);
}

/* solver function */
int Solver(double a, double b, double c, double *x1, double *x2) {

    if (IsZero(a)) {
        if (IsZero(b)) {
            return (IsZero(c)) ? inf_roots : zero_roots;
        }
        else {
            *x1 = *x2 = - c / b;
            return one_root;
        }
    }
    else {
        double d = b * b - 4 * a * c;

        if (IsZero(d)) {
            *x1 = *x2 = -b / (2 * a);
            return one_root;
        }
        else if (d > 0) {
            double sqrt_d = sqrt(d);
            *x1 = (-b + sqrt_d) / (2 * a);
            *x2 = (-b - sqrt_d) / (2 * a);

            return two_roots;
        }
        else return zero_roots;
    }
}

/* one test */
void Test(struct SquareExample ex) {

    double x1 = 0, x2 = 0;

    int nRoots = Solver(ex.a, ex.b, ex.c, &x1, &x2);

    if (nRoots == ex.nRoots) {
        if ((nRoots == 1) || (nRoots == 2)) {

            if ((AreEqual(x1, ex.x1)) && (AreEqual(x2, ex.x2))) {
                printf("ok\n");
            }
            else {
                printf("------> error!!\n");
                printf("nRoots ok, nRoots = %d\n", nRoots);
                printf("expected x1 = %lf, x2 = %lf\n", ex.x1, ex.x2);
                printf("got x1 = %lf, x2 = %lf\n", x1, x2);
            }
        }
        else {
            printf("ok\n");
        }
    }
    else {
        printf("------> error!\n");
        printf("expected nRoots = %d\n", ex.nRoots);
        printf("got nRoots = %d\n", nRoots);
    }
}

/* all tests checking Solver() */
void RunAllTests() {

    struct SquareExample unit_tests[10] = {} ;

    unit_tests[0] = {.a = 1,         .b = 2,    .c = 1,     .nRoots = 1,    .x1 = -1,   .x2 = -1};
    unit_tests[1] = {.a = 1,         .b = -2,   .c = 1,     .nRoots = 2,    .x1 = 1,    .x2 = 3}; /* wrong, nRoots = 1 */
    unit_tests[2] = {.a = 1,         .b = 2,    .c = 3,     .nRoots = 0,    .x1 = 0,    .x2 = 0};
    unit_tests[3] = {.a = 0,         .b = 1,    .c = 2,     .nRoots = 1,    .x1 = -2,   .x2 = -2};
    unit_tests[4] = {.a = 1,         .b = -4,   .c = -21,   .nRoots = 2,    .x1 = 5,    .x2 = 4}; /*wrong, x1 = 7, x2 = -3 */
    unit_tests[5] = {.a = 0,         .b = 0,    .c = 0,     .nRoots = -1,   .x1 = 0,    .x2 = 0};
    unit_tests[6] = {.a = 0,         .b = 0,    .c = 1,     .nRoots = 0,    .x1 = 0,    .x2 = 0};
    unit_tests[7] = {.a = 0.3333333, .b = 2,    .c = 3,     .nRoots = 1,    .x1 = -3,   .x2 = -3};
    unit_tests[8] = {.a = 5,         .b = 3,    .c = 10,    .nRoots = 2,    .x1 = 0,    .x2 = 0}; /*wrong, nRoots = 0 */
    unit_tests[9] = {.a = 0,         .b = 0,    .c = 15,    .nRoots = 0,    .x1 = 0,    .x2 = 0};


    int number_of_tests = sizeof(unit_tests)/sizeof(unit_tests[0]);
    for (int i = 0; i < number_of_tests; i++) {
        Test(unit_tests[i]);
    }

}

int main() {

    RunAllTests();

    printf("\n\n\n------------------\n");
    printf("This program solves square equations\n");
    printf("Enter a, b, c through a space (probel)\n");

    double a = 0, b = 0, c = 0; /* koefficients */
    scanf("%lg %lg %lg", &a, &b, &c);
    printf("----------\n");


    double x1 = 0, x2 = 0; /* roots */

    int nRoots = Solver(a, b, c, &x1, &x2); /* number of roots */

    switch(nRoots) {
        case inf_roots:
            printf("infinity roots!\n");
            break;

        case zero_roots:
            printf("no roots!\n");
            break;

        case one_root:
            printf("x = %lf\n", x1);
            break;

        case two_roots:
            printf("x1 = %lf, x2 = %lf\n", x1, x2);
            break;

        default:
            printf("error! nRoots = %d\n", nRoots);
            break;
    }
    return 0;
}
