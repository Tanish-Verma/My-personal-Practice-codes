#include <stdio.h>

int main() {
    FILE *ptr;
    ptr = fopen("hi.txt", "r");
    if (ptr == NULL) {
        printf("File could not be opened");
        return 1;
    }
    int countword=0,countcharacter=0,countline=1;
    char c;
    // Use fgetc to read one character at a time
    while ((c = fgetc(ptr)) != EOF) {
        if(c==' '){
            countword++;
        }
        else if(c=='\n'){
            countline++;
        }
        printf("%c", c);
        countcharacter++;
    }
    printf("\n the number of character is :  %d\n",countcharacter);
    printf(" the number of word is :  %d\n",countword);
    printf(" the number of lines is :  %d\n",countline);
    
    
    fclose(ptr); // Close the file after reading
    return 0;
}