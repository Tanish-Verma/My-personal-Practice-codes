#include <stdio.h>

int main() {
    FILE *ptr;
    ptr = fopen("hi.txt", "r");
    if (ptr == NULL) {
        printf("File could not be opened");
        return 1;
    }
    
    char c;
    // Use fgetc to read one character at a time
    while ((c = fgetc(ptr)) != EOF) {
        printf("%c", c);
    }
    
    fclose(ptr); // Close the file after reading
    return 0;
}