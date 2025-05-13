#include <stdio.h>
#include <string.h>

int main() {
    printf("Enter the file name: ");
    char filename[100];
    scanf("%s", filename);
    printf("Enter the word to be found: ");
    char word[100];
    scanf("%s", word);
    FILE *ptr;
    ptr = fopen(filename, "r");
    if (ptr == NULL) {
        printf("File could not be opened");
        return 1;
    }
    
    char c[100];
    int  count = 0,i=0;

    while (fscanf(ptr, "%s", c)==1) {
        if (strcmp(c, word) == 0) {
            count++;
        }
    }
    printf("The frequency of the word %s is %d\n",word,count);

    fclose(ptr); 
    return 0;
}