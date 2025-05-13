#include <stdio.h>

int main(){
    char source_file_name[100];
    char dest_file_name[100];
    printf("Enter the source file name: ");
    scanf("%s", source_file_name);
    FILE *ptr;
    ptr = fopen(source_file_name, "r");
    if (ptr == NULL) {
        printf("File could not be opened");
        return 1;
    }
    printf("Enter the destination  file name: ");
    scanf("%s", dest_file_name);
    FILE *ptr2;
    ptr2=fopen(dest_file_name,"a");
    if (ptr2 == NULL) {
        printf("File could not be opened");
        return 1;
    }
    
    char c='\n';
    fputc(c,ptr2);
    // Use fgetc to read one character at a time
    while ((c = fgetc(ptr)) != EOF) {
        fputc(c,ptr2);
    }
    
    fclose(ptr);
    return 0;
}