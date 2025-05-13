#include <stdio.h>
#include <stdlib.h>
#include <string.h>


int is_palindrome(char* str){
    int k=strlen(str);
    int i=0;
    while(i<(strlen(str)/2)){
        if(str[i]!=str[k-1]){
            return 0;
        }
        i++;
        k--;
    }
    return 1;
}

void longest_substring(char * str){
    int k=strlen(str);
    while(k){
        char * temp;
        
    }
}

int main(){
    printf("Enter the string: ");
    char c;
    char * str = (char*)malloc(sizeof(char));
    int k = 0;
    while ((c = getchar()) != '\n' && c != ' ' && c != EOF) {
        str[k] = c;
        str = (char*)realloc(str, k + 2);
        k++;
    }
    str[k] = '\0';
    if(is_palindrome(str)){
        printf("Its a palindrome\n");
    }
    else{
        printf("It is not a palindrome\n");
    }
    // printf("%s\n",str); 
    return 0;
}