#include<stdlib.h>
#include<stdio.h>

typedef struct {
    int data;
    void *p_nextNode;
} Node;

void AddNode(Node **p_headNode, int value){
    Node *newNode = NULL;
    newNode = malloc(sizeof(*newNode));
    if(newNode == NULL){
        fprintf(stderr, "ERROR: Couldn't create new node.\n");
        exit(1);
    }
    newNode->data = value;

    if(*p_headNode == NULL){
        newNode->p_nextNode = NULL;
        *p_headNode = newNode;
    }
    else{
        newNode->p_nextNode = *p_headNode;
        *p_headNode = newNode;
    }
}
void InsertNode(Node **p_headNode, int value, int position){
    Node *newNode = NULL;
    newNode = malloc(sizeof(*newNode));
    if(newNode == NULL){
        fprintf(stderr, "ERROR: Couldn't create new node.\n");
        exit(1);
    }
    newNode->data = value;

    if(*p_headNode == NULL){
        newNode->p_nextNode = NULL;
        *p_headNode = newNode;
        return;
    }

    //Edge case if insert at the beginning.
    if(position == 0){
        newNode->p_nextNode = *p_headNode;
        *p_headNode = newNode;
        return;
    }

    int counter = 0;
    Node *currentNode = *p_headNode;

    while(currentNode != NULL){
        if(counter + 1 == position){
            newNode->p_nextNode = currentNode->p_nextNode;
            currentNode->p_nextNode = newNode;
            break;
        }
            counter++;
            currentNode = currentNode->p_nextNode;
    }
}
void RemoveNode(Node **p_headNode, int value){
    if(*p_headNode == NULL){
        printf("Empty linked list.\n");
        return;
    }

    //If node to be deleted is headnode
    if((*p_headNode)->data == value){
        Node *nodeToFree = *p_headNode;
        *p_headNode = (*p_headNode)->p_nextNode;
        free(nodeToFree);
        return;
    }

    Node *currentNode = *p_headNode;
    Node *prevNode;
    while(currentNode != NULL){
        if(currentNode->data == value){
            prevNode->p_nextNode = currentNode->p_nextNode;
            free(currentNode);
            break;
        }
        prevNode = currentNode;
        currentNode = currentNode->p_nextNode;
    }
}

void *GetNode(Node *headNode, int value){
    if(headNode == NULL){
        printf("Empty linked list.\n");
        return headNode;
    }

    Node *currentNode = headNode;
    while(currentNode != NULL){
        if(currentNode->data == value){
            return currentNode;
        }
        currentNode = currentNode->p_nextNode;
    }

    return NULL;
}
void PrintLinkedList(Node *headNode){
    if(headNode == NULL){
        printf("Empty linked list.\n");
        return;
    }
    
    Node *currentNode = headNode;
    while(currentNode != NULL){
        printf("%d->", currentNode->data);
        currentNode = currentNode->p_nextNode;
    }

    printf("\n");
    return;
}

void DeallocList(Node *headNode){
    if(headNode == NULL){
        printf("Empty linked list.\n");
        return;
    }

    Node *currentNode = headNode;
    Node *nextNode;
    while(currentNode != NULL){
        nextNode = currentNode->p_nextNode;
        free(currentNode);
        currentNode = nextNode;
    }
}

int main(){
    Node *headNode = NULL;
    //Empty linked list.

    AddNode(&headNode, 10);
    //10->
    AddNode(&headNode, 14);
    //14->10->
    AddNode(&headNode, 18);
    //18->14->10->

    InsertNode(&headNode, 12, 1);
    //18->12->14->10->
    InsertNode(&headNode, 11, 0);
    //11->18->12->14->10->
    InsertNode(&headNode, 19, 5);
    //11->18->12->14->10->19->

    RemoveNode(&headNode, 18);
    //11->12->14->10->19->
    RemoveNode(&headNode, 11);
    //12->14->10->19->
    RemoveNode(&headNode, 19);
    //12->14->10->

    DeallocList(headNode);
    return 0;
}
