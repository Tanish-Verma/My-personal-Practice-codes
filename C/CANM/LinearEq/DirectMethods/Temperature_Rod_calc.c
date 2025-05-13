#include <stdio.h>
#include <stdlib.h>

int Tri_Diagonal_Algorithm(int n, double **a, double *b, double *x) {
    double *P = malloc((n-1) * sizeof(double));
    double *Q = malloc(n * sizeof(double));
    P[0] = -a[0][1] / a[0][0];
    Q[0] = b[0] / a[0][0];
    for (int i = 1; i < n - 1; i++) {
        double denominator = a[i][i] + a[i][i-1] * P[i-1];
        P[i] = -a[i][i+1] / denominator;
        Q[i] = (b[i] - a[i][i-1] * Q[i-1]) / denominator;
    }
    Q[n-1] = (b[n-1] - a[n-1][n-2] * Q[n-2]) / (a[n-1][n-1] + a[n-1][n-2] * P[n-2]);
    x[n-1] = Q[n-1];
    for (int i = n - 2; i >= 0; i--) {
        x[i] = P[i] * x[i+1] + Q[i];
    }
    
    free(P);
    free(Q);
    return 0;
}
void laplacian_tridiagonal_matrix(int n, double **a, double *b,double cold_temp, double hot_temp){
    for(int i=0;i<n;i++){
        a[i][i]=2;
        b[i]=0;
        if(i>0){
            a[i][i-1]=-1;
        }
        if(i<n-1){
            a[i][i+1]=-1;
        }
        }
    b[n-1]=cold_temp;
    b[0]=hot_temp;
    return;
}

void print_matrix_file(int n, double **a, FILE *f, double * b){
    for(int i=0;i<n;i++){
        for(int j=0;j<n;j++){
            fprintf(f,"%.4lf ",a[i][j]);
        }
        fprintf(f,"\n");
    }
    fprintf(f,"\n");
    for(int i=0;i<n;i++){
        fprintf(f,"%0.4lf\n ",b[i]);
    }
    return;
}

int main(){
    double length;
    double Hot_temp;
    long double dx;
    double Cold_temp;
    printf("Enter the length of the rod: ");
    scanf("%lf",&length);
    printf("Enter the section lenght: ");
    scanf("%Lf",&dx);
    printf("Enter the temperature of the hot end: ");
    scanf("%lf",&Hot_temp);
    printf("Enter the temperature of the cold end: ");
    scanf("%lf",&Cold_temp);
    int n=length/dx-1;
    double *x=malloc(n*sizeof(double));
    double *b=malloc(n*sizeof(double));
    double **a=malloc(n*sizeof(double*));
    for(int i=0;i<n;i++){
        a[i]=malloc(n*sizeof(double));
    }
    laplacian_tridiagonal_matrix(n,a,b,Cold_temp,Hot_temp);
    FILE *f=fopen("matrix.txt","w");
    print_matrix_file(n,a,f,b);
    fclose(f);
    Tri_Diagonal_Algorithm(n,a,b,x);
    printf("Temperature at point 1 is %lf\n",Hot_temp);
    for(int i=1;i<=n;i++){
        printf("Temperature at point %d is %lf\n",i+1 ,x[i-1]);
    }
    printf("Temperature at point %d is %lf\n",n+2,Cold_temp);
    free(x);
    free(b);
    for(int i=0;i<n;i++){
        free(a[i]);
    }
    free(a);

    return 0;
}