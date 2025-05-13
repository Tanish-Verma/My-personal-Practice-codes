#include <stdio.h>
#include <stdlib.h>

struct Record {
    int id;
    char name[20];
};

int main() {
    FILE *file;
    struct Record rec;
    
    // Open file in binary write mode
    file = fopen("data.bin", "w+");
    if (file == NULL) {
        perror("Error opening file");
        return 1;
    }
    
    // Write records to file
    for (int i = 0; i < 5; i++) {
        rec.id = i + 1;
        snprintf(rec.name, sizeof(rec.name), "Name%d", i + 1);
        fwrite(&rec, sizeof(struct Record), 1, file);
    }
    
    // Seek to the third record (offset of 2 records from the start)
    fseek(file, 2 * sizeof(struct Record), SEEK_SET);

    // Read the third record
    fread(&rec, sizeof(struct Record), 1, file);
    printf("ID: %d, Name: %s\n", rec.id, rec.name);

    // Update the third record
    rec.id = 99;
    snprintf(rec.name, sizeof(rec.name), "UpdatedName");

    // Move back to the position of the third record to overwrite it
    fseek(file, 2 * sizeof(struct Record), SEEK_SET);
    fwrite(&rec, sizeof(struct Record), 1, file);

    // Close the file
    fclose(file);
    return 0;
}
