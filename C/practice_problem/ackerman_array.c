#include <stdio.h>
#include <math.h>

int main(){
    long long int N,K,T=0;
    scanf("%lld %lld",&N,&K);
    long long int input=N;
    int terms=0;
    while(input!=0){
        input/=10;
        terms++;
    }
    for (int i=1;i<=terms;i++){
        int sub_array=0;
        input=N;
        int array_sum=0;
        while(input!=0){
            sub_array=input%((long int)pow(10,i));
            // printf("%d\n",sub_array);
            for(int k=0;k<i;k++){
                array_sum+=(sub_array%10);
            }
            printf("%d\n",array_sum);
            if (array_sum==K){
                T+=1;
            }
            input/=10;
        }

    }
    printf("%lld",T);
    return 0;
}