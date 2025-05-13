#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_LENGTH 100

typedef struct node{
    char * string;
    struct node *next;
}node;

void append(node **head, char *string) {
    node *newnode = (node *)malloc(sizeof(node));
    newnode->string = strdup(string);
    newnode->next = *head; 

    if (*head == NULL) {
        *head = newnode;
        newnode->next = *head;
    } else {
        node *last = *head;
        while (last->next != *head) {
            last = last->next;
        }
        last->next = newnode; 
    }
}

char *string_concat(node *head) {
    char *final_str = (char *)malloc((MAX_LENGTH + 1) * sizeof(char));
    if (final_str == NULL) {
        printf("Memory allocation failed.\n");
        return NULL;
    }
    final_str[0] = '\0';
    int length = 0;
    node *temp = head;

    
    while (length < MAX_LENGTH) {
        int remaining_space = MAX_LENGTH - length;
        int str_len = strlen(temp->string);
        if (str_len <= remaining_space) {
            sprintf(&final_str[length], "%s", temp->string);
            length += str_len;
        } else {
            snprintf(&final_str[length], remaining_space + 1, "%s", temp->string);
            length = MAX_LENGTH;
        }

        temp = temp->next;
    }

    return final_str;
}
int main(){
    node * head=NULL;
    int T;
    printf("Enter the number of  strings: ");
    scanf("%d",&T);
    getchar();
    for(int i=0;i<T;i++){
        char c;
        char *str=(char* )malloc(sizeof(char));
        int k=0;
        while((c=getchar())!='\n' && c!=EOF &&c!=' '){
            str[k]=c;
            str=realloc(str,k+2);
            k++;
        }
        str[k]='\0';
        append(&head,str);
    }
    char *final_str=string_concat(head);
    printf("%s",final_str);

    return 0;
}