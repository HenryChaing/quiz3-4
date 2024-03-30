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

Node *init_node(Tree *tree,int value){
    Node *node = malloc(sizeof(Node));
    node->balance = 0;
    node->value = value;
    node->left = NULL;
    node->right = NULL;
    tree->tree_size++;
    return node;
}

Tree *init_tree(){
    Tree *tree = malloc(sizeof(Tree));
    tree->tree_size = 0;
    tree->root = NULL;
    return tree;
}

int count_height(Node *sub_root){
    if(!sub_root)return 0;
    int right_height = count_height(sub_root->right);
    int left_height = count_height(sub_root->left);
    int max_height = (right_height > left_height) ? right_height : left_height;
    return 1 + max_height;
}

void rotate (Tree *tree, Node *sub_root){
    enum rotate_case {LL,LR,RL,RR};
    int rotate_type = 4;

    if(sub_root->balance > 1){
        if(sub_root->right->balance > 0){
            rotate_type = RR;
        }else if(sub_root->right->balance < 0){
            rotate_type = RL;
        }
    }else if(sub_root->balance < -1){
        if(sub_root->left->balance > 0){
            rotate_type = LR;
        }else if(sub_root->left->balance < 0){
            rotate_type = LL;
        }
    }

    Node *grand = NULL, *parent = NULL, *node = NULL;

    switch (rotate_type)
    {
    case LL:
        grand = sub_root;
        parent = sub_root->left;
        node = sub_root->left->left;

        /*grand_parent with grand_grand_parent links*/
        if(grand->parent){    
            if (grand->parent->left == grand){
                grand->parent->left = parent;
            } else {
                grand->parent->right = parent;
            }
        }else{
            tree->root = parent;
        }
        parent->parent = grand->parent;
        if(parent->right)
            parent->right->parent = grand;
        grand->left = parent->right;
        parent->right = grand;
        grand->parent = parent;
        
        break;
    case LR:
        grand = sub_root;
        parent = sub_root->left;
        node = sub_root->left->right;

        /*grand_parent with grand_grand_parent links*/
        if(grand->parent){    
            if (grand->parent->left == grand){
                grand->parent->left = parent;
            } else {
                grand->parent->right = parent;
            }
        }else{
            tree->root = node;
        }
        node->parent = grand->parent;
        parent->right =  node->left;
        grand->left = node->right;
        node->left->parent = parent;
        node->right->parent = grand;
        node->left = parent;
        node->right = grand;
        parent->parent = node;
        grand->parent = node;

        break;
    case RL:
        grand = sub_root;
        parent = sub_root->right;
        node = sub_root->right->left;

        /*grand_parent with grand_grand_parent links*/
        if(grand->parent){    
            if (grand->parent->left == grand){
                grand->parent->left = parent;
            } else {
                grand->parent->right = parent;
            }
        }else{
            tree->root = node;
        }
        node->parent = grand->parent;
        parent->left =  node->right;
        grand->right = node->left;
        if(node->left)
            node->left->parent = grand;
        if(node->right)
            node->right->parent = parent;
        node->left = grand;
        node->right = parent;
        parent->parent = node;
        grand->parent = node;

        break;
    case RR:
        grand = sub_root;
        parent = sub_root->right;
        node = sub_root->right->right;

        /*grand_parent with grand_grand_parent links*/
        if(grand->parent){    
            if (grand->parent->left == grand){
                grand->parent->left = parent;
            } else {
                grand->parent->right = parent;
            }
        }else{
            tree->root = parent;
        }
        parent->parent = grand->parent;
        if(parent->left)
            parent->left->parent = grand;
        grand->right = parent->left;
        parent->left = grand;
        grand->parent = parent;
        break;
    default:
        break;
    }

    grand->balance = count_height(grand->right) - count_height(grand->left);
    parent->balance = count_height(parent->right) - count_height(parent->left);
    node->balance = count_height(node->right) - count_height(node->left);

}


void update_balance(Tree *tree, Node *node){
    Node *update_node = node;
    while(update_node){
        update_node->balance = count_height(update_node->right) - count_height(update_node->left);
        // printf("%d, ",update_node->balance);
        if(update_node->balance >1 || update_node->balance < -1){
            rotate(tree, update_node);
        }
        update_node = update_node->parent;
    }
}



void insert_node(Tree *tree,int value){
    Node *node = tree->root;

    if(node == NULL){
        Node *new_node = init_node(tree,value);
        tree->root = new_node;
        new_node->parent = NULL;
        return;
    }

    while (1)
    {
        if(value > node->value){
            if(!node->right){
                Node *new_node = init_node(tree,value);
                node->right = new_node;
                new_node->parent = node;
                new_node->balance = 0;
                update_balance(tree,new_node);
                return;
            }
            node = node->right;
        }else{
            if(!node->left){
                Node *new_node = init_node(tree,value);
                node->left = new_node;
                new_node->parent = node;
                new_node->balance = 0;
                update_balance(tree,new_node);
                return;
            }
            node = node->left;
        }
    }
    
}


void inorder_free_and_insert(Tree *tree, Node *subtree){
    if(!subtree)return;
    inorder_free_and_insert(tree, subtree->left);
    inorder_free_and_insert(tree, subtree->right);
    int value = subtree->value;
    tree->tree_size--;
    free(subtree);
    insert_node(tree,value);
}

void remove_node(Tree *tree,int value){
    Node *node = tree->root;
    if(!node)return;

    while(1){
        if(value == node->value){
            uint8_t remove_case = 0;
            if(node->left){
                remove_case |= 1;
            }
            if(node->right){
                remove_case |=2;
            }

            switch (remove_case)
            {
            case 0:
                if(--tree->tree_size == 0){
                    free(tree);
                }
                if(node->parent){    
                    if (node->parent->left == node){
                        node->parent->left = NULL;
                    } else {
                        node->parent->right = NULL;
                    }
                }
                update_balance(tree,node->parent);
                free(node);
                break;
            case 1:
                node->left->parent = node->parent;
                if(node->parent){    
                    if (node->parent->left == node){
                        node->parent->left = node->left;
                    } else {
                        node->parent->right = node->left;
                    }
                }else{
                    tree->root = node->left;
                }
                tree->tree_size--;
                update_balance(tree,node->parent);
                free(node);
                break;
            case 2:
                node->right->parent = node->parent;
                if(node->parent){    
                    if (node->parent->left == node){
                        node->parent->left = node->right;
                    } else {
                        node->parent->right = node->right;
                    }
                }else{
                    tree->root = node->right;
                }
                tree->tree_size--;
                update_balance(tree,node->parent);
                free(node);
                break;
            case 3:
                node->left->parent = node->parent;
                if(node->parent){    
                    if (node->parent->left == node){
                        node->parent->left = node->left;
                    } else {
                        node->parent->right = node->left;
                    }
                }else{
                    tree->root = node->left;
                }
                Node *replace_root = node->right;
                tree->tree_size--;
                update_balance(tree,node->parent);
                free(node);
                inorder_free_and_insert(tree,replace_root);
                break;
            default:
                break;
            }
            return;
        }else if(value > node->value){
            if(!node->right){
                return;
            }
            node = node->right;
        }else{
            if(!node->left){
                return;
            }
            node = node->left;
        }
    }
    
}

void inorder_search(Node *subtree){
    if(!subtree)return;
    inorder_search(subtree->left);
    printf("(%d, %d), ",subtree->value,subtree->balance);
    inorder_search(subtree->right);
}

int main(){
    Tree *tree = init_tree();
    insert_node(tree,1);
    insert_node(tree,2);
    insert_node(tree,3);
    insert_node(tree,4);
    insert_node(tree,5);
    inorder_search(tree->root);
    printf("\n");
    remove_node(tree,2);
    inorder_search(tree->root);
    printf("\n");
    remove_node(tree,3);
    inorder_search(tree->root);
    printf("\n");
    remove_node(tree,4);
    inorder_search(tree->root);
    printf("\n");
    remove_node(tree,5);
    inorder_search(tree->root);
    printf("\n");
    remove_node(tree,1);
}