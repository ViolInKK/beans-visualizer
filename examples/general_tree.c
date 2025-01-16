// List of children general tree ADT implementation.
// REFERENCE: https://opendsa-server.cs.vt.edu/ODSA/Books/Everything/html/GenTreeImplement.html#list-of-children
/*                
 *                 
 *                    _________________________
 *              INDEX | VALUE | PARNT | CLDRN |
 *                0   |   R   |   /   |   -> 1 -> 3 -> NULL
 *                1   |   A   |   0   |   -> 2 -> 4 -> 6 -> NULL
 *                2   |   C   |   1   |   /   |
 *                3   |   B   |   0   |   -> 5 -> NULL 
 *                4   |   D   |   1   |   /   |
 *                5   |   F   |   3   |   /   |
 *                6   |   E   |   1   |   /   |
 *                7   -------------------------
 *
 *
 */

#include<stdlib.h>
#include<stdio.h>

#define NODES_AMNT 10

typedef struct {
    void *p_treeNode;
    void *p_nextListNode;
} ListNode;

typedef struct {
    char *data;
    void *p_parentTreeNode;
    ListNode *p_childrenList;
} TreeNode;

typedef struct{
    int size;
    int capacity;

    TreeNode *p_rootNode;
} Tree;

Tree *InitTree(){
    Tree *tree = malloc(sizeof(*tree));
    if(tree == NULL){
        fprintf(stderr, "ERROR: Couldn't init tree.\n");
        exit(1);
    }
    
    tree->size = 0;
    tree->capacity = NODES_AMNT;

    tree->p_rootNode = malloc(tree->capacity * sizeof(*tree->p_rootNode));
    if(tree->p_rootNode == NULL){
        fprintf(stderr, "ERROR: Couldn't init root node.\n");
        exit(2);
    }
    tree->p_rootNode[0] = (TreeNode){
        "R",
        NULL,
        NULL,
    };
    tree->size++;

    return tree;
}

void DeallocTree(Tree **tree){
    if(*tree == NULL){
        printf("Tree isn't initialized.\n");
        return;
    }

    //Iterate over children linked list to free each node.
    for(int i = 0; i < (*tree)->size; i++){
        if((*tree)->p_rootNode[i].p_childrenList == NULL){
            continue;
        }
        else{
            ListNode *currentNode = (*tree)->p_rootNode[i].p_childrenList;
            ListNode *nextNode;
            while(currentNode != NULL){
                nextNode = currentNode->p_nextListNode;
                free(currentNode);
                currentNode = nextNode;
            }
        }
    }
    free((*tree)->p_rootNode);
    free((*tree));
    *tree = NULL;
    return;
}

void AddChildrenNode(ListNode **rootChildrenNode, TreeNode *childrenNode){
    ListNode *listNode = malloc(sizeof(*listNode));
    if(listNode == NULL){
        fprintf(stderr, "ERROR: Couldn't allocate list node.\n");
        exit(3);
    }

    if(*rootChildrenNode == NULL){
        listNode->p_nextListNode = NULL;
        listNode->p_treeNode = (void *)(childrenNode);
        *rootChildrenNode = listNode;
    }
    else{
        listNode->p_nextListNode = *rootChildrenNode;
        listNode->p_treeNode = (void *)(childrenNode);
        *rootChildrenNode = listNode;
    }
}

void AddTreeNode(Tree *tree, char *value, char *dest){
    if(tree->size == tree->capacity){
        //NOTE(ViolinKK):
        //      Here we can allocate more space and update tree capacity if we need to.
        printf("Can't add any more nodes, array is full.\n");
        return;
    }
    
    //NOTE(ViolinKK): 
    //      Iterate through nodes array, when we find destination node, 
    //      save its address and keep iterating to see if we have duplicates. 
    //      If it has duplicates do nothing, otherwise go to found destination address and add new node.
    int treeSize = tree->size;
    TreeNode *p_destNode = NULL;
    for(int i = 0; i < tree->capacity; i++){
        if(tree->p_rootNode[i].data == dest && p_destNode == NULL){
            p_destNode = &tree->p_rootNode[i];
        }
        else if(tree->p_rootNode[i].data == dest && p_destNode != NULL){
            printf("Node with such data already exists.\n");
            return;
        }
    }

    //If we didnt find destination node return.
    if(p_destNode == NULL){
        printf("Couldn't find destination node.\n");
        return;
    }
    //Else add new node and update children list.
    else{
        tree->p_rootNode[treeSize].data = value;
        tree->p_rootNode[treeSize].p_parentTreeNode = (void *)p_destNode;
        tree->p_rootNode[treeSize].p_childrenList = NULL;
        AddChildrenNode(&p_destNode->p_childrenList, &tree->p_rootNode[treeSize]);
        tree->size++;
        return;
    }
}

Tree *tree = NULL;

int main(void){
    tree = InitTree();

    AddTreeNode(tree, "A", "R");
    AddTreeNode(tree, "B", "R");
    AddTreeNode(tree, "C", "A");
    AddTreeNode(tree, "D", "A");
    AddTreeNode(tree, "E", "A");
    AddTreeNode(tree, "F", "B");

    DeallocTree(&tree);
    return 0;
}
