#ifndef _BINTREE_H
#define _BINTREE_H

#include <stdio.h>
#include <stdlib.h>
#include <stddef.h>

// Node structure should have an int node_id, an int data, and pointers to left and right child nodes
typedef struct node {
    int node_id;
    int data;
    struct node *left;
    struct node *right;
} NODE;

///*** DO NOT CHANGE ANY FUNCTION DEFINITIONS ***///
// Declare the tree modification functions below...
void insert_node(int, int);
int find_node_data(int);
void print_preorder(NODE*);

#endif
