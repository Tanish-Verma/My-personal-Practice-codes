#include <stdio.h>
#include <stdlib.h>

typedef struct node {
    int data;
    struct node* next;
    struct node* prev;
} node;

// Function to create and append a new node at the end of the list
void create_node(node **head) {
    node* new_node = (node*)malloc(sizeof(node));
    if (new_node == NULL) {
        printf("Memory Error\n");
        return;
    }
    printf("Enter number: ");
    scanf("%d", &(new_node->data));
    new_node->prev = NULL;
    new_node->next = NULL;

    if (*head == NULL) {
        *head = new_node;
    } else {
        node* last = *head;
        while (last->next != NULL) {
            last = last->next;
        }
        last->next = new_node;
        new_node->prev = last;
    }
}

// Function to reverse the order of alternate nodes
void reverse_alternate_nodes(node* head) {
    if (head == NULL || head->next == NULL) return;

    // Initialize pointers for managing alternate nodes
    node* current = head->next;  // Start from the second node
    node* prev = NULL;            // To keep track of previous alternate node
    node* next = NULL;

    // Detach and reverse every alternate node
    while (current != NULL) {
        next = current->next ? current->next->next : NULL; // Move to the next alternate node

        // Detach current node from the list
        if (current->prev != NULL) current->prev->next = current->next;
        if (current->next != NULL) current->next->prev = current->prev;

        // Insert detached node at the beginning of the reversed section
        current->next = prev;
        if (prev != NULL) prev->prev = current;

        prev = current;           // Update previous to the current node
        current = next;            // Move to the next alternate node
    }

    // Attach reversed nodes back to the main list after the first node
    current = head;
    node* reversed = prev;  // Start of the reversed alternate nodes section

    while (reversed != NULL) {
        node* next_main = current->next;
        node* next_reversed = reversed->next;

        // Insert reversed node between current and the next main node
        current->next = reversed;
        reversed->prev = current;

        if (next_main != NULL) next_main->prev = reversed;
        reversed->next = next_main;

        // Move to the next pair of nodes
        current = next_main;
        reversed = next_reversed;
    }
}

// Function to print the list from head to tail
void print_list(node* head) {
    node* current = head;
    while (current != NULL) {
        printf("%d ", current->data);
        current = current->next;
    }
    printf("\n");
}

// Free the list to avoid memory leaks
void free_list(node** head) {
    node* current = *head;
    while (current != NULL) {
        node* next = current->next;
        free(current);
        current = next;
    }
    *head = NULL;
}

int main() {
    int T;
    printf("Enter number of nodes: ");
    scanf("%d", &T);
    
    node* head = NULL;
    for (int i = 0; i < T; i++) {
        create_node(&head);
    }

    printf("Original list: ");
    print_list(head);

    reverse_alternate_nodes(head);

    printf("List after reversing alternate nodes: ");
    print_list(head);

    // Free memory
    free_list(&head);

    return 0;
}
