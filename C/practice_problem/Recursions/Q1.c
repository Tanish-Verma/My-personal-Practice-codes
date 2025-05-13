#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAX_LENGTH 10
#define MIN_LENGTH 1

void swap(char arr[],int i,int j){
    char temp=arr[i];
    arr[i]=arr[j];
    arr[j]=temp;
}
long int factorial(int n){
    int k=1;
    for(int i=2;i<=n;i++){
        k*=i;
    }
    return k;
}


int generatepermutations(int lenght,char arr[lenght],int start,int stop,char result[][lenght+1]){
    static int index=0;
    if(start==stop){
        strcpy(result[index],arr);
        index++;
    }
    else{
        for(int i=start;i<=stop;i++){
            int should_skip=0;
            for(int j=start;j<i;j++){
                if(arr[i]==arr[j]){
                    should_skip=1;
                    break;
                }
            }
            if(should_skip)continue;
            swap(arr,start,i);
            generatepermutations(lenght,arr,start+1,stop,result);
            swap(arr,start,i);
        }
    }
    return index;
}

int main(){
    char string[MAX_LENGTH+1];
    scanf("%10s",string);
    // int k=strlen(string);
    int k = strlen(string);
    // qsort(string, k, sizeof(char), (int (*)(const void *, const void *)) strcmp);
    char result[factorial(k)][k+1];
    int no_of_permutations=0;
    int l=generatepermutations(k,string,0,k-1,result);
    for(int i=0;i<l;i++){
        printf("%s\n",result[i]);
    }
    return 0;
}