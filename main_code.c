#include <TXLib.h>
#include <stdio.h>
#include <math.h>

#define ZERO_BORDER 0.0000009

struct Refference {
    double a,b,c;
    int nRoots_r;
    double x1_r, x2_r;
} ;

int Are_Equal(double num1, double num2);
int Solver(double a, double b, double c, double *x1, double *x2);
void Test(struct Refference ref);
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

        if (Are_Equal(d,0)) {
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
void Test(struct Refference ref) {
    double a = ref.a;
    double b = ref.b;
    double c = ref.c;
    int nRoots_r = ref.nRoots_r;
    double x1_r = ref.x1_r;
    double x2_r = ref.x2_r;


    double x1 = 0, x2 = 0;

    int nRoots = Solver(a,b,c, &x1, &x2);

    if (nRoots == nRoots_r) {
        if ((nRoots == 1) || (nRoots == 2)) {

            if ((Are_Equal(x1, x1_r)) && (Are_Equal(x2, x2_r))) {
                printf("ok\n");
            }
            else {
                printf("------> error!!\n");
                printf("nRoots ok, nRoots = %d\n", nRoots);
                printf("expected x1 = %lf, x2 = %lf\n", x1_r, x2_r);
                printf("got x1 = %lf, x2 = %lf\n", x1, x2);
            }
        }
        else {
            printf("ok");
        }
    }
    else {
        printf("------> error!!\n");
        printf("expected nRoots = %d\n", nRoots_r);
        printf("got nRoots = %d\n", nRoots);
    }
}

void RunAllTests() {

    struct Refference ref0 = {.a = 1, .b = 2, .c = 1, .nRoots_r = 1, .x1_r = -1, .x2_r = -1};
    struct Refference ref1 = {.a = 1, .b = -2, .c = 1, .nRoots_r = 1, .x1_r = 1, .x2_r = 1};
    struct Refference ref2 = {.a = 1, .b = 2, .c = 3, .nRoots_r = 4, .x1_r = 0, .x2_r = 0};
    struct Refference ref3 = {.a = 0, .b = 1, .c = 2, .nRoots_r = 1, .x1_r = -2, .x2_r = -2};
    struct Refference ref4 = {.a = 1, .b = -4, .c = -21, .nRoots_r = 2, .x1_r = 7, .x2_r = -3};
    struct Refference ref5 = {.a = 0, .b = 0, .c = 0, .nRoots_r = 3, .x1_r = 0, .x2_r = 0};
    struct Refference ref6 = {.a = 0, .b = 0, .c = 1, .nRoots_r = 0, .x1_r = 0, .x2_r = 0};
    struct Refference ref7 = {.a = 0.3333333, .b = 2, .c = 3, .nRoots_r = 1, .x1_r = -3, .x2_r = -3};
    struct Refference ref8 = {.a = 5, .b = 10, .c = 3, .nRoots_r = 4, .x1_r = 0, .x2_r = 0};
    struct Refference ref9 = {.a = 0, .b = 0, .c = 15, .nRoots_r = 0, .x1_r = 0, .x2_r = 0};

    struct Refference unit_tests[10] = {ref0, ref1, ref2, ref3, ref4, ref5, ref6, ref7, ref8, ref9} ;

    int number_of_tests = sizeof(unit_tests) ;
    for (int i=0; i < number_of_tests; i++) {
        Test(unit_tests[i]);
    }

}

int main() {

    RunAllTests();
    printf("\n\n\n\n\n--------------\n");

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
