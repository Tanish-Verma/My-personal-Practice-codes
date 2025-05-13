#include <stdio.h>
#include <stdlib.h>

typedef struct node {
    char c;
    struct node* next;
    struct node* prev;
}node;

node* create_node(char data){
    node* new_node = (node*)malloc(sizeof(node));
    new_node->c=data;
    new_node->next=NULL;
    new_node->prev=NULL;
    return  new_node;
}

void append(node ** head,char data){
    node* new_node = create_node(data);
    node *last=*head;
    if(*head==NULL){
        *head=new_node;
        return;
    }
    while(last->next!=NULL){
        last=last->next;
    }
    new_node->prev=last;
    last->next=new_node;
}
void freeList(node* head) {
    node* current = head;
    node* nextNode;

    while (current != NULL) {
        nextNode = current->next;
        free(current);
        current = nextNode;
    }
}

void is_palindrome(node * head){
    if (head == NULL || head->next == NULL) return;

    node* back_checker = head;
    while (back_checker->next != NULL) {
        back_checker = back_checker->next;
    }

    node* front_checker = head;
    while (front_checker != back_checker && front_checker->prev != back_checker) {
        if (front_checker->c != back_checker->c) {
            printf("Not a palindrome\n");
            return;
        }
        front_checker = front_checker->next;
        back_checker = back_checker->prev;
    }
    printf("Is a palindrome\n");
}

int main(){
    char c;
    char str[100];
    node *head = NULL;
    int i=0;
    while ((c = getchar()) != '\n' && c != EOF)
    {
        // sprintf(&str[i],"%c",c);
        // i++;
        append(&head, c);
    }
    if (head == NULL)
    {
        printf("Input is empty\n");
    }
    else
    {
        is_palindrome(head);
    }
    freeList(head);
    return 0;
}