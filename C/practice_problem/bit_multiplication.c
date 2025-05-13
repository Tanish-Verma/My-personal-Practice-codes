#include <stdio.h>


int multiplybit(int a, int b) {
    int result = 0;
    int sign = (a < 0) ^ (b < 0) ? -1 : 1;
    for(int i=0;i<32;i++){
        if((a&1<<i)>>i){
            result+=b<<i;
        }
    }
    if((sign<0)^(result<0)?1:0){
        printf("Overflow Occured\n");
    }
    return result;
}


int main(){
    printf("%d\n",multiplybit(-13545,216532));
    return 0;
}