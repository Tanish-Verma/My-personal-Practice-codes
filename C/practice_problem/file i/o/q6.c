#include <stdio.h>
#include <string.h>
#include <ctype.h>

enum vowels{
    a=1,e,i,o,u
};

int main()
{
    printf("Enter the file name: ");
    char filename[100];
    scanf("%s", filename);
    FILE *ptr;
    FILE *ptr2;
    ptr2 = fopen("no_vowel.txt", "w");
    ptr = fopen(filename, "r");
    if (ptr == NULL)
    {
        printf("File could not be opened");
        return 1;
    }
    char c;
    while(((c=fgetc(ptr))!=EOF)){
        switch (c)
        {
        case 'a': case 'A':
        case 'e': case 'E':
        case 'i': case 'I':
        case 'o': case 'O':
        case 'u': case 'U':
            fputc('*', ptr2); // Replace vowel with '*'
            break;
        default:
            fputc(c,ptr2);  
            break;
        }
    }

    fclose(ptr); 
    fclose(ptr2); 
    return 0;
}