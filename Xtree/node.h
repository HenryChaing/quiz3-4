#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>

typedef struct node 
{
    int balance;
    int value;
    struct node *left;
    struct node *right;
    struct node *parent;
}Node;

typedef struct tree
{
    int tree_size;
    Node *root;
}Tree;

Node *init_node(Tree *tree,int value);

Tree *init_tree();

int find(Tree *tree, int value);

int count_height(Node *sub_root);

void rotate (Tree *tree, Node *sub_root);

void update_balance(Tree *tree, Node *node);

void insert_node(Tree *tree,int value);

void inorder_free_and_insert(Tree *tree, Node *subtree);

void remove_node(Tree *tree,int value);

void delete_tree(Tree *tree,Node *node);

void inorder_search(Node *subtree);