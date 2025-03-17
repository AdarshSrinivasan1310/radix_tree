#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

#define ALPHABET_SIZE 26

struct Node {
    bool isEndOfWord;
    struct Node* children[ALPHABET_SIZE];
};

struct Node* createNode() {
    struct Node* newNode = (struct Node*)malloc(sizeof(struct Node));
    if (newNode) {
        newNode->isEndOfWord = false;
        for (int i = 0; i < ALPHABET_SIZE; ++i) {
            newNode->children[i] = NULL;
        }
    }
    return newNode;
}

void insert(struct Node* root, const char* key) {
    struct Node* current = root;
    for (int level = 0; key[level] != '\0'; ++level) {
        int index = key[level] - 'a';
        if (!current->children[index]) {
            current->children[index] = createNode();
        }
        current = current->children[index];
    }
    current->isEndOfWord = true;
}

bool search(struct Node* root, const char* key) {
    struct Node* current = root;
    for (int level = 0; key[level] != '\0'; ++level) {
        int index = key[level] - 'a';
        if (!current->children[index]) {
            return false;
        }
        current = current->children[index];
    }
    return current != NULL && current->isEndOfWord;
}

bool isEmpty(struct Node* root) {
    for (int i = 0; i < ALPHABET_SIZE; ++i) {
        if (root->children[i] != NULL) {
            return false;
        }
    }
    return true;
}

struct Node* deleteHelper(struct Node* root, const char* key, int depth) {
    if (!root) {
        return NULL;
    }

    if (depth == strlen(key)) {
        if (root->isEndOfWord) {
            root->isEndOfWord = false;
        }
        if (isEmpty(root)) {
            free(root);
            root = NULL;
        }

        return root;
    }

    int index = key[depth] - 'a';
    root->children[index] = deleteHelper(root->children[index], key, depth + 1);

    if (isEmpty(root) && !root->isEndOfWord) {
        free(root);
        root = NULL;
    }

    return root;
}

void deleteKey(struct Node* root, const char* key) {
    if (!root || !key) {
        return;
    }

    deleteHelper(root, key, 0);
}

void traverse(struct Node* root, char* buffer, int depth) {
    if (root->isEndOfWord) {
        buffer[depth] = '\0';
        printf("%s\n", buffer);
    }

    for (int i = 0; i < ALPHABET_SIZE; ++i) {
        if (root->children[i] != NULL) {
            buffer[depth] = i + 'a';
            traverse(root->children[i], buffer, depth + 1);
        }
    }
}

void display(struct Node* root) {
    if (!root) {
        printf("The radix tree is empty.\n");
        return;
    }

    char buffer[100];
    traverse(root, buffer, 0);
}

int main() {
    struct Node* root = createNode();

    int choice;
    char key[100];

    do {
        printf("\nMenu:\n");
        printf("1. Insert key\n");
        printf("2. Search key\n");
        printf("3. Delete key\n");
        printf("4. Display radix tree\n");
        printf("5. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                printf("Enter key to insert: ");
                scanf("%s", key);
                insert(root, key);
                printf("Key '%s' inserted successfully.\n", key);
                break;
            case 2:
                printf("Enter key to search: ");
                scanf("%s", key);
                if (search(root, key)) {
                    printf("Key '%s' found.\n", key);
                } else {
                    printf("Key '%s' not found.\n", key);
                }
                break;
            case 3:
                printf("Enter key to delete: ");
                scanf("%s", key);
                deleteKey(root, key);
                printf("Key '%s' deleted successfully.\n", key);
                break;
            case 4:
                printf("Displaying radix tree:\n");
                display(root);
                break;
            case 5:
                printf("Exiting program.\n");
                break;
            default:
                printf("Invalid choice. Please enter a valid option.\n");
        }
    } while (choice != 5);

    return 0;
}
