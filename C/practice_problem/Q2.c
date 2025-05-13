#include <stdio.h>
#include <stdlib.h>

char * concat_string(char **str,int count){
    char *result=(char*)calloc(1,sizeof(char));
    int k=0;
    for(int i=0;i<count;i++){
        for(int j=0;*(*(str+i)+j)!='\0';j++){
            result[k]=*(*(str+i)+j);
            result=realloc(result,k+2);
            k++;
        }
    }
    result[k]='\0';
    return result;
}

int main(){
    char  *str[4]={"hello","my","name","f"};
    char *result=concat_string(str,4);
    printf("%s",result);
    free;
    return 0;
}