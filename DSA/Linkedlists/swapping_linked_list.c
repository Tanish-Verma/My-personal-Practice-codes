#include <stdio.h>
#include <stdlib.h>

typedef struct node{
    int data;
    struct node* next;
    struct node* prev;
}node;


void create_node(node ** head){
    node * new_node = (node*)malloc(sizeof(node));
    if(new_node==NULL){
        printf("Memory Error");
        return;
    }
    printf("enter number: ");
    scanf("%d",&(new_node->data));
    new_node->prev=NULL;
    new_node->next=NULL;

    if(*head==NULL){
        *head=new_node;
        return;
    }
    else{
        node * last=*head;
        while (last->next!=NULL)
        {
            last=last->next;
        }
        last->next=new_node;
        new_node->prev=last;
    }
}

void swap(node * Node){
    node *current_node=Node;

    if (current_node == NULL || current_node->next == NULL) {
        return;
    }
    if(current_node->next->next==NULL){
        current_node->next->prev=current_node->prev;
        current_node->prev->next=current_node->next;
        current_node->next->next=current_node;
        current_node->prev=current_node->next;
        current_node->next=NULL;
    }
    else{
    current_node->next->prev=current_node->prev;
    current_node->prev->next=current_node->next;
    current_node->prev=current_node->next;
    current_node->next=current_node->next->next;
    current_node->prev->next=current_node;
    current_node->next->prev=current_node;

    }
}
 
void alternate_node_swap(node* head,int T){
    node* current = head->next;
    if((current->next)==NULL){
        printf("\nList has only one element\n");
        return;
    }
    for(int i=0;i<(T-1)/2;i++){
        // printf("%d\n",i);
        swap(current);
        current=current->next;
    }
}

void print_list(node* head){
    node* current = head;
    while(current!=NULL){
        printf("%d ",current->data);
        current=current->next;
    }
    printf("\n");
}

int main(){\
    int T;
    printf("Enter number of nodes: ");
    node * head=NULL;
    scanf("%d",&T);
    for(int i=0;i<T;i++){
        create_node(&head);
    }
    print_list(head);
    alternate_node_swap(head,T);
    print_list(head);

    return 0;
}