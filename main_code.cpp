/*! \file */

#include <stdio.h>
#include <math.h>

#define ZERO_BORDER 1e-6

/**
	\brief different varieties of number of roots: infinity, 0, 1, 2
 */
enum Roots {
    INF_ROOTS 	= -1,
    ZERO_ROOTS	= 0,
    ONE_ROOTS	= 1,
    TWO_ROOTS	= 2,
};

/**
    \brief structure for examples of equations
	\param a, b, c koefficients of the equation: a * x**2 + b * x + c = 0
	\param nRoots number of roots of the equation
	\param x1, x2 roots
*/
struct SquareExample {
    double a, b, c;
    enum Roots nRoots;
    double x1, x2;
};

int IsZero(double x);
int AreEqual(double num1, double num2);
enum Roots LineSolver(double k, double m, double *x);
enum Roots Solver(double a, double b, double c, double *x1, double *x2);
void Test(struct SquareExample ex);
void RunAllTests();

/**
 \brief check double to be near zero. this function made to avoid == comparison with double
 \param x double that needs to be checked
 \return 1 if double is around zero, 0 if not
 */
int IsZero(double x) {
    return fabs(x) <= ZERO_BORDER;
}

/**
 * \brief compares doubles. rhis function was made to avoid == comparison between double
 * \param num1, num2 double numbers to be compared
 * \return 1 if numbers are equal or part-equal, 0 if not
 */
int AreEqual(double num1, double num2) {
    return IsZero(num1 - num2);
}

/**
 * \brief solves line equations
 * \param b, c koefficients : k*x + m = 0
 * \return number of roots. also x is overwrited
 */
enum Roots LineSolver(double k, double m, double *x) {
    if (IsZero(k)) {
        *x = NAN;
        return (IsZero(m)) ? INF_ROOTS : ZERO_ROOTS;
    }
    else {
        *x = -m / k;
        return ONE_ROOTS;
    }
}


/**
 * \brief solver square equation
 * \param a,b,c koefficients of the equation. a * x**2 + b * x + c = 0
 * \param x1,x2 roots
 * \return number of roots. also x1 and x2 are owerwrited, x1 and x2 are the correct roots of the equation
 */
enum Roots Solver(double a, double b, double c, double *x1, double *x2) {

    if (IsZero(a)) { 
        *x2 = NAN;
        return LineSolver(b, c, x1);
    }

    double d = b * b - 4 * a * c;

    if (IsZero(d)) {
        *x1 = -b / (2 * a);
        *x2 = NAN;
        return ONE_ROOTS;
    }

    if (d > 0) {
        double sqrt_d = sqrt(d);
        *x1 = (-b + sqrt_d) / (2 * a);
        *x2 = (-b - sqrt_d) / (2 * a);

        return TWO_ROOTS;
    }
    
    *x1 = NAN;
    *x2 = NAN;
    return ZERO_ROOTS;
    
}



/**
 * \brief tests the result of Solver()
 * \param ex example of the equation, type: struct SquareExample
 * \return prints "ok", if Solver return the same nRoots, x1, x2 as in the example. or prints "error" and explains what error it is
 */
void Test(struct SquareExample ex) {

    double x1 = 0, x2 = 0;

    enum Roots nRoots = Solver(ex.a, ex.b, ex.c, &x1, &x2);

    if (ex.nRoots == nRoots) {

        switch(nRoots) {
            case ZERO_ROOTS:
                if (isnan(x1) && isnan(x2)) {
                    printf("ok\n");
                }
                else {
                    printf("------> error!\n");
                    printf("zero roots, x1 = NAN and x2 = NAN\n");
                    printf("got x1 = %lfc, x2 = %lf\n", x1, x2);
                    printf("<------\n");
                }

            case ONE_ROOTS:
                if (AreEqual(x1, ex.x1)) {
                    printf("ok\n");
                }
                else {
                    printf("------> error!\n");
                    printf("expected one root, ex.x = %lf\n", ex.x1);
                    printf("got x = %lf\n", x1);
                    printf("<------\n");
                }
            
            case TWO_ROOTS:
                if (AreEqual(x1, ex.x1) && AreEqual(x2, ex.x2)) {
                    printf("ok\n");
                }
                else {
                    printf("------> error!\n");
                    printf("expected two roots, x1 = %lf, x2 = %lf\n", ex.x1, ex.x2);
                    printf("got x1 = %lf, x2 = %lf\n", x1, x2);
                    printf("<------\n");
                }

            case INF_ROOTS:
                if (isnan(x1) && isnan(x2)) {
                    printf("ok\n");
                }
                else {
                    printf("------> error!\n");
                    printf("infinity roots, x1 = NAN and x2 = NAN\n");
                    printf("got x1 = %lf, x2 = %lf\n", x1, x2);
                    printf("<------\n");
                }

            default:
                printf("------> error!\n");
                printf("nRoots = %d\n", nRoots);
                printf("<------\n");
        }
    }
    else { /* if (nRoots != ex.nRoots) */
        printf("------> error!\n");
        printf("expected nRoots = %d\n", ex.nRoots);
        printf("got nRoots = %d\n", nRoots);
        printf("<------\n");
    }
}

/**
 * \brief one function to run all tests
 * \return void
 */
void RunAllTests() {

    struct SquareExample unit_tests[10] = {
		(struct SquareExample){.a = 1,			.b = 2,		.c = 1,		.nRoots = ONE_ROOTS,	.x1 = -1,	.x2 = NAN},
    	(struct SquareExample){.a = 1,			.b = -2,	.c = 1,		.nRoots = TWO_ROOTS,	.x1 = 1,	.x2 = 3}, /* wrong, nRoots = 1 */
    	(struct SquareExample){.a = 1,			.b = 2,		.c = 3,		.nRoots = ZERO_ROOTS,	.x1 = NAN,	.x2 = NAN},
    	(struct SquareExample){.a = 0,			.b = 1,		.c = 2,		.nRoots = ONE_ROOTS,	.x1 = -2,	.x2 = NAN},
    	(struct SquareExample){.a = 1,			.b = -4,	.c = -21,	.nRoots = TWO_ROOTS,	.x1 = 5,	.x2 = 4}, /*wrong, x1 = 7, x2 = -3 */
    	(struct SquareExample){.a = 0,			.b = 0,		.c = 0,		.nRoots = INF_ROOTS,	.x1 = NAN,	.x2 = NAN},
    	(struct SquareExample){.a = 0,			.b = 0,		.c = 1,		.nRoots = ZERO_ROOTS,	.x1 = NAN,	.x2 = NAN},
    	(struct SquareExample){.a = 0.3333333,	.b = 2,		.c = 3,		.nRoots = ONE_ROOTS,	.x1 = -3,	.x2 = NAN},
    	(struct SquareExample){.a = 5,			.b = 3,		.c = 10,	.nRoots = TWO_ROOTS,	.x1 = -15,	.x2 = 82}, /*wrong, nRoots = 0 */
    	(struct SquareExample){.a = 0,			.b = 0,		.c = 15,	.nRoots = ZERO_ROOTS,	.x1 = NAN,	.x2 = NAN},
	};

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

    enum Roots nRoots = Solver(a, b, c, &x1, &x2); /* number of roots */

    switch(nRoots) {
        case INF_ROOTS:
            printf("infinity roots!\n");
            break;

        case ZERO_ROOTS:
            printf("no roots!\n");
            break;

        case ONE_ROOTS:
            printf("x = %lg\n", x1);
            break;

        case TWO_ROOTS:
            printf("x1 = %lg, x2 = %lg\n", x1, x2);
            break;

        default:
            printf("error! nRoots = %d\n", nRoots);
            break;
    }
    return 0;
}