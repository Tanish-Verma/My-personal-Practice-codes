#include <stdio.h>
#include <stdlib.h>

struct ListNode{
    int val;
    struct ListNode *next;
};

void insertNode(struct ListNode **head, int val){
    struct ListNode *newNode = (struct ListNode *)malloc(sizeof(struct ListNode));
    newNode->val = val;
    if(*head==NULL){
        *head=newNode;
        return;
    }
    struct ListNode * last=*head;
    while(last->next!=NULL){
        last=last->next;
    }
    last->next=newNode;
}


void printList(struct ListNode *head){
    struct ListNode *temp = head;
    while(temp!=NULL){
        printf("%d ",temp->val);
        temp=temp->next;
        }
        printf("\n");

}

struct ListNode* reverseList(struct ListNode **head){
    struct ListNode *reversehead=NULL;
    struct ListNode *current=*head;
    struct ListNode *nextNode=NULL;
    while(current!=NULL){
        nextNode=current->next;
        current->next=reversehead;
        reversehead=current;
        current=nextNode;
        }
    return reversehead;
}

int main(){
    int n;
    scanf("%d",&n);
    struct ListNode *head = NULL;
    for(int i=0;i<n;i++){
        int val;
        scanf("%d",&val);
        insertNode(&head,val);
    }
    printList(head);
    head=reverseList(&head);
    printList(head);
    return 0;
}