#include <stdio.h>
#include <string.h>
#include <stdlib.h>

typedef struct node{
    unsigned value;
    struct node *left;
    struct node *right;
}Node;

typedef struct{
    Node *root;
}Tree;

void insert_right(unsigned value, Node *node){

    if(node->right == NULL){ 
        Node *new = (Node *)malloc(sizeof(Node));
        if(new == NULL){
         printf("insert right");
         exit(1);  
        }
        new->left = NULL;
        printf("oi2\n");
        new->right = NULL;
        printf("oi3\n");
        new->value = value;
        printf("oi4\n");
        node->right = new;
        printf("oi5\n");
        printf("passou no ins right\n");

    }else if(node->right->value > value){
        insert_left(value, node->right);
    }else if(node->right->value < value){
        insert_right(value, node->right);
    }
}

void insert_left(unsigned value, Node *node){

    if(node->left == NULL){
        Node *new = (Node *)malloc(sizeof(Node));
        if(new == NULL){
            printf("insert left");
            exit(2);  
        }
        new->left = NULL;
        printf("oi2\n");
        new->right = NULL;
        printf("oi2\n");
        new->value = value;
        printf("oi2\n");
        node->left = new;
        printf("oi2\n");
        printf("i left\n");
    }else if(node->left->value > value){
        insert_left(value, node->left);
    }else if(node->left->value < value){
        insert_right(value, node->left);
    }
}

void insert(Node *tree, unsigned value){

    if(tree == NULL){
        Node *new = (Node *)malloc(sizeof(Node));
        if(new == NULL){
            printf("insert");
            exit(3);
        }
        new->left = NULL;
        printf("oi1\n");
        new->right = NULL;
        printf("oi2\n");
        new->value = value;
        printf("oi3\n");
        tree = new;
        printf("oi4\n");
    }else{
        printf("aaaaaaaaaaa");
        if(value > tree->value){
            insert_right(value, tree);
        }else if(value < tree->value){
            insert_left(value, tree);
        }
    }
}

void print_tree(Node *node){
    printf("%u\n", node->value);
    print_tree(node->left);
    print_tree(node->right);
}

int main(){

    char command[4];
    unsigned value;
    int c_ins = 0;
    Tree tree;
    tree.root = NULL;
    
    do{
        scanf(" %s", command);
        if(strcmp(command, "INS") == 0){
            scanf("%u", &value);
            insert(tree.root, value);
            printf("%d\n", c_ins);
            c_ins++;
           // printf("%u", tree.root->value);
        }else if(strcmp(command, "FND") == 0){
            printf("cu");
        }else if(strcmp(command, "DEL") == 0){
            printf("vi");
        }

    }while(strcmp(command, "END") != 0);

    

    return 0;
}