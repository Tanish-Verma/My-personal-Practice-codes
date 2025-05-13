#include <stdio.h>
#include <stdlib.h>
#include <string.h>

 void swap(char * str,int len){
    for (int i=0;i<len/2;i++){
        char temp=str[i];
        str[i]=str[len-i-1];
        str[len-i-1]=temp;
    }
 }
 void reverse_words(char **words, int count){
    for (int i = 0; i < count; i++){
        swap(*(words+i),strlen(*(words+i)));
    }
 }


int main(){
    int n;
    scanf("%d",&n);
    getchar();
    char  *ptr[n];
    for(int i=0;i<n;i++){
        char *str=(char*)calloc(1,sizeof(char));
        int k=0;
        while(1){
            char c=getchar();
            if(c=='\n' || c==' ' || c=='\0')break;
            str[k]=c;
            str=realloc(str,k+2);
            k++;
        }
        str[k]='\0';
        ptr[i]=str;
    }
    reverse_words(ptr,n);
    for(int i=0;i<n;i++){
        printf("%s\n",ptr[i]);
    }
    free;
    return 0;
}