#include <stdio.h>
#include <stdlib.h>
#include <math.h>

double newton_raphson_iteration(double xi, double *f, int n) {
    double *Df = (double *)calloc(n - 1, sizeof(double));
    double Dfxi = 0, fxi = 0;

    // Calculate the derivative coefficients
    for (size_t i = 1; i < n; i++) {
        Df[i - 1] = i * f[i];
    }

    // Calculate the initial function value and its derivative at xi
    for (size_t i = 0; i < n; i++) {
        fxi += pow(xi, i) * f[i];
    }
    for (size_t i = 1; i < n; i++) {
        Dfxi += pow(xi, i - 1) * Df[i - 1];
    }

    // Perform one iteration of Newton-Raphson
    xi = xi - (fxi / Dfxi);

    free(Df);
    return xi;
}

double secant_method(double x0, double x1, double *f, int n, double epsilon) {
    double fx0 = 0, fx1 = 0, x2, fx2;
    int count = 1;

    // Calculate the initial function values at x0 and x1
    for (size_t i = 0; i < n; i++) {
        fx0 += pow(x0, i) * f[i];
        fx1 += pow(x1, i) * f[i];
    }

    // Secant method iteration
    while (fabs(fx1) > epsilon) {
        x2 = x1 - fx1 * (x1 - x0) / (fx1 - fx0);
        fx2 = 0;
        for (size_t i = 0; i < n; i++) {
            fx2 += pow(x2, i) * f[i];
        }

        x0 = x1;
        fx0 = fx1;
        x1 = x2;
        fx1 = fx2;

        count += 1;
    }

    printf("Total number of iterations: %d\n", count);
    return x1;
}

int main() {
    int n;
    double x_guess, epsilon;

    printf("Enter the degree of the polynomial: ");
    scanf("%d", &n);
    n++; // Since we need n+1 coefficients for a polynomial of degree n

    double *f = (double *)malloc(n * sizeof(double));
    if (f == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        return 1;
    }

    printf("Enter the coefficients of the polynomial (from highest degree to constant term):\n");
    for (int i = 0; i < n; i++) {
        printf("Coefficient of x^%d: ", n - i - 1);
        scanf("%lf", &f[n-i-1]);
    }

    printf("Enter the initial guess x_guess: ");
    scanf("%lf", &x_guess);
    printf("Enter the tolerance epsilon: ");
    scanf("%lf", &epsilon);

    // Use Newton-Raphson method for one iteration to get x0 and x1
    double x0 = x_guess;
    double x1 = newton_raphson_iteration(x0, f, n);

    double root = secant_method(x0, x1, f, n, epsilon);
    printf("The root of the polynomial is: %lf\n", root);

    free(f);
    return 0;
}