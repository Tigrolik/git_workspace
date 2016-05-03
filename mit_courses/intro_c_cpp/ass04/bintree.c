#include "bintree.h"

///*** DO NOT CHANGE ANY FUNCTION DEFINITIONS ***///

// Recall node is defined in the header file

NODE *root = NULL;

// Insert a new node into the binary tree with node_id and data
void insert_node(int node_id, int data) {

    NODE *curr = root;

    if (root == NULL) {
        NODE *new_node = malloc(sizeof(*new_node));
        new_node->node_id = node_id;
        new_node->data = data;
        root = new_node;
        root->left = root->right = NULL;

        return;
    }

    while (curr != NULL) {
        if (node_id > curr->node_id) {
            curr = curr->right;
        } else if (node_id < curr->node_id) {
            curr = curr->left;
        } else {
            printf("There is an element in the tree with id %d\n",
                    node_id);
            return;
        }
    }

    NODE *new_node = malloc(sizeof(*new_node));
    new_node->node_id = node_id;
    new_node->data = data;
    curr = new_node;
    curr->left = curr->right = NULL;
    print_preorder(root);
}

// Find the node with node_id, and return its data
int find_node_data(int node_id) {

    NODE *curr = root;

    while (curr != NULL) {
        if (node_id > curr->node_id)
            curr = curr->right;
        else if (node_id < curr->node_id)
            curr = curr->left;
        else
            return curr->data;
    }

    printf("No node with id %d, returning -1\n", node_id);

    return -1;
}

void print_preorder(NODE *tree)
{
    printf("Size of struct %lu\n", sizeof(NODE));
    if (tree) {
        printf("id %d and data %d\n", tree->node_id, tree->data);
        print_preorder(tree->left);
        print_preorder(tree->right);
    }
}
///***** OPTIONAL: Challenge yourself w/ deletion if you want ***///
/*//Find and remove a node in the binary tree with node_id.
//Children nodes are fixed appropriately.
void remove_node(int node_id) {

}
*/
