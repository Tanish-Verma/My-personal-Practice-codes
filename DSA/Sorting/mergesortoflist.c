#include <stdio.h>
#include <stdlib.h>

typedef struct Node
{
    int data;
    struct Node *next;
} Node;

Node *createNode(int data)
{
    Node *newnode = (Node *)malloc(sizeof(Node));
    if (newnode == NULL)
    {
        printf("Memory allocation failed\n");
        exit(1);
    }
    newnode->data = data;
    newnode->next = NULL;
    return newnode;
}

void insert(Node **head, int data)
{
    Node *newnode = createNode(data);
    if (*head == NULL)
    {
        *head = newnode;
        return;
    }
    Node *last = *head;
    while (last->next != NULL)
    {
        last = last->next;
    }
    last->next = newnode;
}

void freeList(Node *head)
{
    Node *temp = head;
    while (temp != NULL)
    {
        Node *next = temp->next;
        free(temp);
        temp = next;
    }
}

Node *mergeSortedLists(Node *list1, Node *list2)
{
    Node dummy;
    Node *current = &dummy;
    dummy.next = NULL;

    while (list1 != NULL && list2 != NULL)
    {
        if (list1->data <= list2->data)
        {
            current->next = list1;
            list1 = list1->next;
        }
        else
        {
            current->next = list2;
            list2 = list2->next;
        }
        current = current->next;
    }
    current->next = (list1 != NULL) ? list1 : list2;

    return dummy.next;
}

Node *splitList(Node *head)
{
    if (head == NULL || head->next == NULL)
    {
        return NULL;
    }
    Node *slow = head;
    Node *fast = head->next;

    while (fast != NULL && fast->next != NULL)
    {
        slow = slow->next;
        fast = fast->next->next;
    }

    Node *secondHalf = slow->next;
    slow->next = NULL;
    return secondHalf;
}

Node *mergeSort(Node *head)
{
    if (head == NULL || head->next == NULL)
    {
        return head;
    }

    Node *secondHalf = splitList(head);
    head = mergeSort(head);
    secondHalf = mergeSort(secondHalf);
    return mergeSortedLists(head, secondHalf);
}

void printList(Node *head)
{
    Node *temp = head;
    while (temp != NULL)
    {
        fprintf(stdout, "%d ", temp->data);
        temp = temp->next;
    }
    fprintf(stdout, "\n");
}

int main()
{
    int N;
    fscanf(stdin, "%d", &N);

    Node *head = NULL;
    for (int i = 0; i < N; i++)
    {
        int data;
        fscanf(stdin, "%d", &data);
        insert(&head, data);
    }

    head = mergeSort(head);

    printList(head);

    freeList(head);
    return 0;
}
