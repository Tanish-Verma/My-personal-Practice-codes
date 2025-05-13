#include <stdio.h>
#include <math.h>
#include <stdlib.h>

double bisection_method(double xl, double xr, double *f, int n, double epsilon)
{
    double fl = 0, fr = 0, xc, fc = 0;
    int count = 0;
    xc = (xl + xr) / 2;
    for (size_t i = 0; i < n; i++)
    {
        fl += pow(xl, i) * f[i];
        fc += pow(xc, i) * f[i];
        fr += pow(xr, i) * f[i];
    }
    if (fl * fr > 0)
    {
        printf("Invalid Inputs please provide proper guess\n");
        return 0;
    }

    while (fabs(fc) > epsilon)
    {
        if (fl * fc < 0)
        {
            xr = xc;
        }
        else
        {
            xl = xc;
        }
        xc = (xl + xr) / 2;
        fc = 0;
        for (size_t i = 0; i < n; i++)
        {
            fc += pow(xc, i) * f[i];
        }
        count += 1;
    }
    printf("Total number of iterations: %d\n", count);
    return xc;
}

int main()
{
    int n;
    double xl, xr, epsilon;

    printf("Enter the degree of the polynomial: ");
    scanf("%d", &n);
    n++; // Since we need n+1 coefficients for a polynomial of degree n

    double *f = (double *)malloc(n * sizeof(double));
    if (f == NULL)
    {
        fprintf(stderr, "Memory allocation failed\n");
        return 1;
    }

    printf("Enter the coefficients of the polynomial (from constant term to highest degree):\n");
    for (int i = 0; i < n; i++)
    {
        printf("Coefficient of x^%d: ", i);
        scanf("%lf", &f[i]);
    }

    printf("Enter the initial guess xl: ");
    scanf("%lf", &xl);
    printf("Enter the initial guess xr: ");
    scanf("%lf", &xr);
    printf("Enter the tolerance epsilon: ");
    scanf("%lf", &epsilon);

    double root = bisection_method(xl, xr, f, n, epsilon);
    if (root != 0)
    {
        printf("The root of the polynomial is: %lf\n", root);
    }

    free(f);
    return 0;
}