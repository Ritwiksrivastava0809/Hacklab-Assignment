#include <stdio.h>
#include <stdlib.h>

// Define the structure of each node in the linked list
typedef struct node {
    int data;
    struct node* next;
} Node;

// Define the linked list structure with a head pointer
typedef struct linked_list {
    Node* head;
} LinkedList;

void add_node(LinkedList* list, int data) {
    // Allocate memory for a new node
    Node* new_node = (Node*) malloc(sizeof(Node));
    new_node->data = data;
    new_node->next = NULL;

    // If the linked list is empty, set the head to the new node
    if (list->head == NULL) {
        list->head = new_node;
    }
    // Otherwise, traverse to the end of the list and add the new node
    else {
        Node* current = list->head;
        while (current->next != NULL) {
            current = current->next;
        }
        current->next = new_node;
    }
}

void delete_node_by_location(LinkedList* list, int location) {
    // If the linked list is empty, return
    if (list->head == NULL) {
        return;
    }
    // If the head node needs to be deleted
    if (location == 0) {
        Node* temp = list->head;
        list->head = temp->next;
        free(temp);
        return;
    }
    // Traverse to the node before the one to be deleted
    Node* current = list->head;
    for (int i = 0; current != NULL && i < location - 1; i++) {
        current = current->next;
    }
    // If the given location is greater than the number of nodes in the list
    if (current == NULL || current->next == NULL) {
        return;
    }
    // Delete the node at the given location
    Node* temp = current->next;
    current->next = temp->next;
    free(temp);
}

void delete_nodes_by_data(LinkedList* list, int data) {
    // If the linked list is empty, return
    if (list->head == NULL) {
        return;
    }
    // Traverse through the linked list and delete nodes with the given data
    Node* current = list->head;
    Node* prev = NULL;
    while (current != NULL) {
        if (current->data == data) {
            // If the head node needs to be deleted
            if (prev == NULL) {
                list->head = current->next;
            }
            else {
                prev->next = current->next;
            }
            Node* temp = current;
            current = current->next;
            free(temp);
        }
        else {
            prev = current;
            current = current->next;
        }
    }
}

void delete_list(LinkedList* list) {
    // Traverse through the linked list and free all nodes
    Node* current = list->head;
    while (current != NULL) {
        Node* temp = current;
        current = current->next;
        free(temp);
    }
    // Set the head pointer to NULL to indicate an empty list
    list->head = NULL;
}


void display_list(LinkedList* list) {
    // If the linked list is empty, return
    if (list->head == NULL) {
        printf("Linked list is empty.\n");
        return;
    }
    // Traverse through the linked list and print each node's data
    Node* current = list->head;
    while (current != NULL) {
        printf("%d ", current->data);
        current = current->next;
    }
    printf("\n");
}

void display_inverted_list(Node* head) {
    // Base case: if the head is NULL, return
    if (head == NULL) {
        return;
    }
    // Recursive call to print the rest of the list in reverse order
    display_inverted_list(head->next);
    // Print the current node's data
    printf("%d ", head->data);
}


void display_memory_usage(LinkedList* list) {
    // If the linked list is empty, return
    if (list->head == NULL) {
        printf("Linked list is empty.\n");
        return;
    }
    // Calculate the size of each node in bytes
    int node_size = sizeof(Node);
    // Traverse through the linked list and count the number of nodes
    int node_count = 0;
    Node* current = list->head;
    while (current != NULL) {
        node_count++;
        current = current->next;
    }
    // Calculate the total memory usage and print it
    int total_memory = node_size * node_count;
    printf("Total memory usage: %d bytes\n", total_memory);
}


void delete_nodes_with_data_and_next(LinkedList* list, int data) {
    // If the linked list is empty, return
    if (list->head == NULL) {
        printf("Linked list is empty.\n");
        return;
    }
    // Traverse through the linked list and remove nodes with matching data
    Node* current = list->head;
    Node* prev = NULL;
    while (current != NULL) {
        // Check if the current node's data matches the given number
        if (current->data == data) {
            // If the current node is the head of the list, update the head
            if (prev == NULL) {
                list->head = current->next;
            }
            // Otherwise, update the previous node's next pointer
            else {
                prev->next = current->next;
            }
            // Free the memory used by the current node and its next node (if it exists)
            Node* next_node = current->next;
            free(current);
            if (next_node != NULL) {
                free(next_node);
            }
            // Move on to the next node
            current = (prev == NULL) ? list->head : prev->next;
        }
        else {
            // Move on to the next node
            prev = current;
            current = current->next;
        }
    }
}


int main() {
    // Create a new linked list
    LinkedList list;
    list.head = NULL;

    // Add some nodes to the linked list
    add_node(&list, 1);
    add_node(&list, 2);
    add_node(&list, 3);
    add_node(&list, 4);
    add_node(&list, 5);

    // Display the linked list
    printf("Linked list: ");
    display_list(&list);

    // Delete nodes with the given data
    delete_nodes_by_data(&list, 3);

    // Display the updated linked list
    printf("Linked list after deleting nodes with data = 3: ");
    display_list(&list);

    // Delete a node at the given location
    delete_node_by_location(&list, 1);

    // Display the updated linked list
    printf("Linked list after deleting node at location 1: ");
    display_list(&list);

    // Delete nodes with the given data and next node's data
    delete_nodes_with_data_and_next(&list, 2);

    // Display the updated linked list
    printf("Linked list after deleting nodes with data = 2 and next node's data: ");
    display_list(&list);

    // Display the memory usage of the linked list
    display_memory_usage(&list);

    // Display the inverted linked list
    printf("Inverted linked list: ");
    display_inverted_list(list.head);
    printf("\n");

    // Delete the linked list
    delete_list(&list);

    return 0;
}