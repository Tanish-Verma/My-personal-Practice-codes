#include <stdio.h>
#include <stdlib.h>
#include <string.h>

union data{
    int intValue;
    float floatValue;
    char charValue;
    char *StrValue;
};

typedef enum dtype{
    Int=1,Float,Char,String
}datatype;

typedef struct node{
    union data data;
    enum dtype type;
    struct node *ptr;
}node;

void get_node_values(node* node){
    switch (node->type) {
        case Int:
            printf("Enter the integer value: ");
            scanf("%d", &node->data.intValue);
            break;
        case Float:
            printf("Enter the float value: ");
            scanf("%f", &node->data.floatValue);
            break;
        case Char:
            printf("Enter the character: ");
            getchar(); // Consume leftover newline
            scanf("%c", &node->data.charValue);
            break;
        case String:
            printf("Enter the string: ");
            char *str=(char*)calloc(1,sizeof(char));
            int k=0;
            getchar();
            while(1){
                char c=getchar();
                if(c=='\n' || c==' ' || c=='\0')break;
                str[k]=c;
                str=realloc(str,k+2);
                k++;
            }
            str[k]='\0';
            node->data.StrValue=str;
            break;
        default:
            printf("Invalid data type!\n");
            break;
    }
}

void insertion(node **head){
    int dtype;
    printf("Enter the type of data:\n1. Int\n2. Float\n3.Char\n4.String\n");
    scanf("%d",&dtype);
    if (dtype<1  || dtype>4){
        printf("Wrong input!");
        return;
    }
    node* newnode=(node*)malloc(sizeof(node));
    if (newnode==NULL){
        printf("Memory error!");
        return;
    }
    newnode->type=(datatype)(dtype);
    get_node_values(newnode);
    newnode->ptr= (*head);

    *head=newnode;
}

void printList(node *head) {
    if(head==NULL){
        printf("List is empty!\n");
    }
    node *current = head;
    while (current) {
        switch (current->type) {
            case Int:
                printf("Integer: %d\n", current->data.intValue);
                break;
            case Float:
                printf("Float: %.2f\n", current->data.floatValue);
                break;
            case Char:
                printf("Character: %c\n", current->data.charValue);
                break;
            case String:
                printf("String: %s\n",current->data.StrValue);
                break;
            default:
                printf("Unknown type\n");
        }
        current =current->ptr;
    }
}

void search(node*head){
    printf("Enter the type of data to search for:\n1. Int\n2. Float\n3.Char\n4.Str\n");
    int choice;
    scanf("%d",&choice);
    if(choice<1 && choice>4){
        printf("Wrong data type !");
        return;
    }
    node* current=head;
    while(current!=NULL){
        if (current->type==choice)
        {
            break;
        }
        current=current->ptr;        
    }
    if(current==NULL){
        printf("No such datatype found in the list");
        return;
    }
    printf("Search results: \n");
    switch (current->type) {
            case Int:
                printf("Integer: %d\n", current->data.intValue);
                break;
            case Float:
                printf("Float: %.2f\n", current->data.floatValue);
                break;
            case Char:
                printf("Character: %c\n", current->data.charValue);
                break;
            case String:
                printf("String: %s\n",current->data.StrValue);
        }
}

void delete(node**head){
    node* current = *head;
    while (current!=NULL)
    {
        node* temp=current;
        current=current->ptr;
        free(temp);
    }
    *head=NULL;
}
int main(){
    node *head;
    head=NULL;

    while(1){
        printf("1. Insert\n2. Delete\n3. print\n4. Search\n5. Exit\n");
        int choice;
        scanf("%d",&choice);
        switch(choice){
            case 1:
                insertion(&head);
                break;
            case 2:
                delete(&head);
                break;
            case 3:
                printList(head);
                break;
            case 4:
                search(head);
                break;
            case 5:
                return 0;
            default:
                printf("Wrong input \n");
                continue;
        }

    }
    return 0;
}