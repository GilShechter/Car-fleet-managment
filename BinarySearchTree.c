
#include "BinarySearchTree.h"
#include "matam.h"


/* functions below are not available outside of this file */
Node* createNewNode();
int treeExists_rec(Node* root, Node* node, int(*cmp)(void*,void*));
int treeExists(Tree* tree,Node* node);
Node* insertNode(Node* root, Node* new, int(*cmp)(void*,void*));
Node* removeNode_REC(Node* root, void* data,int(*cmp)(void*,void*),int(*fre)(Node*),int* elements);
void printTree_rec(Node* root, void(*print)(void*));
void treeToArray_rec(Node* root,void** arr,int* i);
int insertListNode(LList** head,LList* new);
LList* createListNode();
void findNode_rec(LList** head,Node* root, void* find,int(*cmp)(void*,void*));
void freeTree_rec(Node* root,int(*fre)(Node*));
int freeLinkedList_rec(LList* head);
double averageKey_rec(Node* root,double(*add)(void*,double),int* numNodes);
/* functions above are not available outside of this file */

/* Returns a new empty generic binary search */
Tree* createTree(void*(*getData)(void*,FILE*),int(*cmp)(void*,void*),int(*fre)(Node*)){
    Tree* res = ALLOC(Tree,1);
    if(!res){
        printf("memory allocation error.\n");
        exit(1);
    }
    res->getData = getData;
    res->cmp = cmp;
    res->fre = fre;
    res->root = NULL;
    res->elementCount = 0;
    return res;
}

/* Returns a new empty node struct */
Node* createNewNode(){
    Node* res = ALLOC(Node,1);
    if(!res){
        printf("Error while allocating memory.\n");
        exit(1);
    }
    res->data = NULL;
    res->left = NULL;
    res->right = NULL;
    return res;
}

/* Checks if a node exist in a tree recursively */
int treeExists_rec(Node* root, Node* node, int(*cmp)(void*,void*)){
    int compare;
    if(!root)
        return -1;
    compare = cmp(root->data,node->data);
    if(compare > 0){
        return treeExists_rec(root->left,node,cmp);
    }
    if(compare < 0){
        return treeExists_rec(root->right,node,cmp);
    }
    return 0;
}

/* Checks if a node exist in a tree */
int treeExists(Tree* tree,Node* node){
    if(!tree){
        return -1;
    }
    if(tree->elementCount == 0){
        return -1;
    }
    return treeExists_rec(tree->root,node,tree->cmp);
}

/* Inserts node to tree */
Node* insertNode(Node* root, Node* new, int(*cmp)(void*,void*)){
    if(!root)
        return new;
    if(cmp(root->data,new->data) > 0){
        root->left = insertNode(root->left,new,cmp);
        return root;
    }
    root->right = insertNode(root->right,new,cmp);
    return root;
}

/* Creates new node, gets data, add it to tree */
Node* addNewNode(Tree* tree,int(*cmp)(void*,void*),FILE* f){
       Node* newNode = createNewNode();
       newNode->data = tree->getData(newNode->data,f);
       if(treeExists(tree,newNode) == 0){
           tree->fre(newNode);
           return NULL;
       }
       tree->root = insertNode(tree->root, newNode,cmp);
       tree->elementCount++;
       return newNode;
}

/* Search for a given node in a tree, if found - remove it from the tree */
Node* removeNode_REC(Node* root, void* data,int(*cmp)(void*,void*),int(*fre)(Node*),int* elements){
    Node* temp;
    Node** tempParent;
    void* rep;
    int compare;
    if(!root)
        return NULL;
    compare = cmp(root->data,data);
    if(compare > 0){
        root->left = removeNode_REC(root->left,data,cmp,fre,elements);
        return root;
    } else if(compare < 0){
        root->right = removeNode_REC(root->right,data,cmp,fre,elements);
        return root;
    }
    if(!root->left && !root->right){
        fre(root);
        (*elements)--;
        return NULL;
    } else if(!root->left){
        temp = root->right;
        fre(root);
        (*elements)--;
        return temp;
    } else if(!root->right){
        temp = root->left;
        fre(root);
        (*elements)--;
        return temp;
    } else{
        temp = root->right;
        tempParent = &(root->right);
        while(temp->left){
            tempParent = &(temp->left);
            temp = temp->left;
        }
        rep = root->data;
        root->data = temp->data;
        temp->data = rep;
        *tempParent = removeNode_REC(temp,data,cmp,fre,elements);
    }
    return root;
}

/* Gets a node and removes it from tree if exists */
int removeNode(Tree* tree,void* data,int(*cmp)(void*,void*)){
    tree->root = removeNode_REC(tree->root,data,cmp,tree->fre,&(tree->elementCount));
    return 0;
}

/* Prints all nodes of the tree recursively */
void printTree_rec(Node* root, void(*print)(void*)){
    if(!root)
        return;
    printTree_rec(root->left,print);
    print(root->data);
    printTree_rec(root->right,print);
}

/* Gets ptr to tree and prints its data */
void printTree(Tree* tree,void(*print)(void*)){
    if(!tree){
        printf("Error: NULL tree pointer\n");
        return;
    }
    if(tree->elementCount == 0){
        printf("No elements in tree\n");
        return;
    }
    printf("\n");
    printTree_rec(tree->root,print);

}

/* Recursively builds an array from a tree */
void treeToArray_rec(Node* root,void** arr,int* i){
    if(!root)
        return;
    treeToArray_rec(root->left,arr,i);
    arr[*i] = root->data;
    (*i)++;
    treeToArray_rec(root->right,arr,i);
}

/* Gets tree and return it as an array */
void** treeToArray(Tree* tree){
    void** arr;
    int index = 0;
    if(!tree){
        printf("Error, NULL tree pointer\n");
        return NULL;
    }
    if(tree->elementCount == 0){
        printf("Tree is empty\n");
        return NULL;
    }
    arr = ALLOC(void*,tree->elementCount);
    treeToArray_rec(tree->root,arr,&index);
    return arr;
}

/* Inserts a node to linked list */
int insertListNode(LList** head,LList* new){
    LList* temp = * head;
    if(!(*head)){
        *head = new;
        return 0;
    }
    while(temp->next){
        temp = temp->next;
    }
    temp->next = new;
    return 0;
}

/* Creates a new linked list node */
LList* createListNode(){
    LList* new = ALLOC(LList,1);
    new->data = NULL;
    new->next = NULL;
    return new;
}

/* Recursively search for a nodes in a tree and inserts them to linked list if found */
void findNode_rec(LList** head,Node* root, void* find,int(*cmp)(void*,void*)){
    int compare;
    LList* newNode;
    if(!root)
        return;
    findNode_rec(head,root->left,find,cmp);
    compare = cmp(root->data,find);
    if(compare == 0){
        newNode = createListNode();
        newNode->data = root->data;
        insertListNode(head,newNode);
    }
    findNode_rec(head,root->right,find,cmp);
}

/* Search for nodes in a tree. Returns a linked list of them if found */
LList* findNode(Tree* tree,void* findMe, int(*cmp)(void*, void*)){
    LList* head = NULL;
    if(!tree){
        printf("Error: NULL tre pointer\n");
        return NULL;
    }
    if(tree->elementCount == 0){
        printf("Empty tree\n");
        return NULL;
    }
    findNode_rec(&head,tree->root,findMe,cmp);
    return head;
}

/* Free allocated memory from tree struct recursively */
void freeTree_rec(Node* root,int(*fre)(Node*)){
    if(!root)
        return;
    freeTree_rec(root->left,fre);
    freeTree_rec(root->right,fre);
    fre(root);
}

/* Free allocated memory from tree struct */
int freeTree(Tree* tree){
    if(!tree){
        printf("Error: NULL tree pointer\n");
        return -1;
    }
    if(tree->elementCount == 0){
        tree->root = NULL;
        return 0;
    }
    freeTree_rec(tree->root,tree->fre);
    tree->elementCount = 0;
    return 0;
}

/* Recursively free linked list allocated memory */
int freeLinkedList_rec(LList* head){
    if(!head)
        return 0;
    freeLinkedList_rec(head->next);
    FREE(head);
    return 0;
}

/* Free allocated memory from linked list */
int freeLinkedList(LList** head){
    if(!(*head))
        return -1;
    freeLinkedList_rec(*head);
    *head = NULL;
    return 0;
}

/* Recursively computes the average of all data in a tree */
double averageKey_rec(Node* root,double(*add)(void*,double),int* numNodes){
    double avg_r = 0,avg_l = 0;
    int num_l = 0,num_r = 0;
    if(!root){
        return 0;
    }
    avg_l = averageKey_rec(root->left,add,&num_l);
    avg_r = averageKey_rec(root->right,add,&num_r);
    *numNodes = num_l+num_r+1;
    return (double)(add(root->data,((avg_l*num_l)+(avg_r*num_r)))/(double)(*numNodes));
}

/* Computes the average of data from given tree */
double averageKey(Tree* tree,double(*add)(void*,double)){
    int numNodes = 0;
    if(!tree){
        printf("Error: NULL tree pointer\n");
        return -1;
    }
    if(tree->elementCount == 0){
        printf("Empty tree\n");
        return 0;
    }
    return averageKey_rec(tree->root,add,&numNodes);
}
