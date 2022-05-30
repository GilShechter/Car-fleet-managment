

#ifndef BINARYSEARCHTREE_H
#define BINARYSEARCHTREE_H
#include <stdio.h>

/* Define generic Node struct for binary search tree */
typedef struct Node{
    void* data;
    struct Node* left;
    struct Node* right;
}Node;


/* Define struct for generic linked list node */
typedef struct linkedList{
   void* data;
   struct linkedList* next;
}LList;


/* Define struct for generic binary search tree */
typedef struct BinarySearchTree{
    Node* root;
    void* (*getData)(void*,FILE*);
    int (*fre)(Node*);
    int(*cmp)(void*,void*);
    int elementCount;
} Tree;

/* Returns a new empty generic binary search */
Tree* createTree(void*(*getData)(void*,FILE*),int(*cmp)(void*,void*),int(*fre)(Node*));

/* Creates new node, gets data, add it to tree */
Node* addNewNode(Tree* tree,int(*cmp)(void*,void*),FILE* f);

/* Gets a node and removes it from tree if exists */
int removeNode(Tree* tree,void* data,int(*cmp)(void*,void*));

/* Gets ptr to tree and prints its data */
void printTree(Tree* tree,void(*print)(void*));

/* Gets tree and return it as an array */
void** treeToArray(Tree* tree);

/* Search for nodes in a tree. Returns a linked list of them if found */
LList* findNode(Tree* tree,void* findMe, int(*cmp)(void*, void*));

/* Free allocated memory from linked list */
int freeLinkedList(LList** head);

/* Computes the average of data from given tree */
double averageKey(Tree* tree,double(*add)(void*,double));

/* Free allocated memory from tree struct */
int freeTree(Tree* tree);
#endif
