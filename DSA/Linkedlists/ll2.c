#include <stdio.h>
#include <stdlib.h>
struct node
{
    int data;
    struct node *ptr;
};

struct node *insertion_ll(struct node *head, int req_position, int data)
{

    struct node *new_node = (struct node *)malloc(sizeof(struct node));
    new_node->data = data;
    struct node *curr_node = (struct node *)malloc(sizeof(struct node));
    curr_node = head;
    if (req_position == 0)
    {
       new_node->ptr=head;
       head=new_node;
       return head;
    }
    for (int i = 1; i < req_position; i++)
    {
        curr_node = curr_node->ptr;
        if (curr_node == NULL)
        {
            printf("Index out of range\n");
            return head;
        }
    }

    new_node->ptr = curr_node->ptr;
    curr_node->ptr = new_node;
    return head;
}

int main()
{
    struct node *head = (struct node *)malloc(sizeof(struct node));
    struct node *sixth = (struct node *)malloc(sizeof(struct node));
    struct node *second = (struct node *)malloc(sizeof(struct node));
    struct node *third = (struct node *)malloc(sizeof(struct node));
    struct node *fourth = (struct node *)malloc(sizeof(struct node));
    struct node *fifth = (struct node *)malloc(sizeof(struct node));
    head->data = 68453;
    head->ptr = second;
    second->data = 123;
    second->ptr = third;
    third->data = 456;
    third->ptr = NULL;
    fourth->data = 789;
    fifth->data = 237946;

    fourth->ptr = head;
    head = fourth;
    // fifth->ptr=third;
    // second->ptr=fifth;
    head = insertion_ll(head, 0, 2346243);

    struct node *current = head;
    while (current != NULL)
    {
        printf("%d\n", current->data);
        current = current->ptr;
    }

    // printf("%d",head->data);

    return 0;
}