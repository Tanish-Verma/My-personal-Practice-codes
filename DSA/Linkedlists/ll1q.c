#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

typedef struct node{
    char* string;
    int lenght;
    struct node *ptr;
}node;

char * generate_random_string(int lenght){
    char *string = (char*)malloc((lenght+1) * sizeof(char));
    const char charset[] = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789";
    if (string == NULL) {
        printf("Memory error\n");
    }
    for(int i=0;i<lenght;i++){
        int  r = rand() % (sizeof(charset) - 1);
        string[i] = charset[r]; 
    }
    string[lenght]='\0';
    return string;
}
int generate_random_num(){
    int k=rand() % (16-1)+5;
    return k;
}

char* traversal(node* head){
    node *ptr = head;
    int lenght=0;
    while (ptr!=NULL)
    {
        lenght+=ptr->lenght;
        ptr=ptr->ptr;
    }
    ptr=head;
    char * finalstring=(char*)malloc((lenght+1)*sizeof(char));
    finalstring[0]='\0';
    while (ptr!=NULL)
    {
        strcat(finalstring,ptr->string);
        ptr=ptr->ptr;
    }
    
    return finalstring;

}
int main(){
    srand(time(NULL));
    struct node  *head = (node*)malloc(sizeof(node));
    head->lenght=generate_random_num();
    head->string =generate_random_string(head->lenght);
    node *second=(node*)malloc(sizeof(node));
    head->ptr=second;
    second->lenght=generate_random_num();
    second->string =generate_random_string(second->lenght);
    node *third=(node*)malloc(sizeof(node));
    third->lenght=generate_random_num();
    third->string=generate_random_string(third->lenght);
    second->ptr=third;
    node *fourth=(node*)malloc(sizeof(node));
    fourth->lenght=generate_random_num();
    fourth->string=generate_random_string(fourth->lenght);
    third->ptr=fourth;
    node *fifth=(node*)malloc(sizeof(node));
    fifth->lenght=generate_random_num();
    fifth->string=generate_random_string(fifth->lenght);
    fourth->ptr=fifth;
    fifth->ptr=NULL;
    char * finalstring=traversal(head);
    printf("%s\n",finalstring);
    // printf("%s",head->string);
    return 0;
}