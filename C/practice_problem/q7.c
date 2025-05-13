// Write a recursive function char *longest_common_substring(char *s1, char *s2) that finds the longest common substring between two dynamically allocated strings. The function should return a dynamically allocated string containing the longest substring. Use dynamic memory management efficiently to handle large input strings and avoid memory leaks.

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char *longest_common_substring(char *s1, char *s2){
    if(strlen(s1)==0 || strlen(s2)==0){
        return NULL;
    }
}

int main(){
    char *s1=(char*)calloc(1,sizeof(char));
    char *s2=(char*)calloc(1,sizeof(char));
    char c;
    int k=0;
    while(1){
        c=getchar();
        if(c=='\n' || c=='\0'  || c==' '){
            break;
        }
        else {
            s1[k]=c;
            s1=realloc(s1,k+2);
            k++;
        }
    }
    s1[k]='\0';
    int j=0;
    while(1){
        c=getchar();
        if(c=='\n' || c=='\0'  || c==' '){
            break;
        }
        else {
            s2[j]=c;
            s2=realloc(s2,j+2);
            j++;
        }
    }
    s2[j]='\0';
    printf("%s %s",s1,s2);


    return 0;
}
