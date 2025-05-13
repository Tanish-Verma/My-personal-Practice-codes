#include <stdio.h>
#include <stdlib.h>
#include <math.h>

double newton_raphson(double xi, double *f, int n, double epsilon) {
    double *Df = (double *)calloc(n - 1, sizeof(double));
    double Dfxi, fxi;
    Dfxi = fxi = 0;
    int count = 0;

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

    // Newton-Raphson iteration
    while (fabs(fxi) > epsilon) {
        xi = xi - (fxi / Dfxi);
        fxi = Dfxi = 0;
        for (size_t i = 0; i < n; i++) {
            fxi += pow(xi, i) * f[i];
        }
        for (size_t i = 1; i < n; i++) {
            Dfxi += pow(xi, i - 1) * Df[i - 1];
        }
        count += 1;
    }

    printf("Total number of iterations: %d\n", count);
    free(Df);
    return xi;
}

int main() {
    int n;
    double xi, epsilon;

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

    printf("Enter the initial guess xi: ");
    scanf("%lf", &xi);
    printf("Enter the tolerance epsilon: ");
    scanf("%lf", &epsilon);

    double root = newton_raphson(xi, f, n, epsilon);
    printf("The root of the polynomial is: %lf\n", root);

    free(f);
    return 0;
}