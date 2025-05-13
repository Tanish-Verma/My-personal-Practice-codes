#include <stdio.h>
#include <stdlib.h>

int isprime(int n){
    if (n <= 1) return 0;
    if(n<=3)return 1;
    if (n % 2 == 0) return 0;
    for(int i=3;i*i<=n;i+=2){
        if(n%i==0)return 0;
    }
    return 1;
}
int* findprime(int n){
    int* primes = (int*)calloc(n , sizeof(int));
    int count=0,i=2;
    while (count<n)
    {
        if(isprime(i)){
            primes[count]=i;
            count++;
        }
        i++;
    }
    return  primes;

}

int main(){
    int n;
    scanf("%d",&n);
    int * primes = findprime(n);
    for(int i=0;i<n;i++){
        printf("%d\n",*(primes+i));
    }
    free;
    return 0;
}
