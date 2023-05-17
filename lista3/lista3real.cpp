#include <iostream>
#include <string>

using namespace std;

typedef struct node{
    unsigned value;
    node *right;
    node *left;
}Node;

Node *rotate_left(Node *root){
    Node *R = new Node;
    Node *RL = new Node;
    R = root->right;
    RL = R->left;
    R->left = root;
    root->right = RL;

    return R;
}

Node *rotate_right(Node *root){
    Node *L = new Node;
    Node *LR = new Node;
    L = root->left;
    LR = L->right;
    L->right = root;
    root->left = LR;

    return L;
}

Node *find(Node *root, unsigned value, int *depht, int *aux){
    if(root != NULL){
        if(value == root->value){
            return root;
        }else if(value < root->value){
            (*depht)++;
            root->left = find(root->left, value, &(*depht), &(*aux));
            if(*aux == 1){
                root = rotate_right(root);
            }
            return root;
        }else if(value > root->value){
            (*depht)++;
            root->right = find(root->right, value, &(*depht), &(*aux));
            if(*aux == 1){
                root = rotate_left(root);
            }
            return root;
        }
    }else{
        (*aux) = 0;
        return NULL;
    }
}

Node *insert(Node *root, unsigned value, int *depht, int *aux){
    if(root == NULL){
        Node *new_node = new Node; // equivalente ao malloc
        if(new_node == NULL){
            cout << "insert";
        }
        new_node->value = value;
        new_node->left = NULL;
        new_node->right = NULL;
       
        return new_node;

    }else{
        if(root->value > value){
            (*depht)++;
            root->left = insert(root->left, value, &(*depht), &(*aux));
            root = rotate_right(root);
        }else if(root->value < value){
            (*depht)++;
           root->right = insert(root->right, value, &(*depht), &(*aux));
           root = rotate_left(root);
        }else{ //find
            root = find(root, value, &(*depht), &(*aux));
        }
        return root;
    }
}

Node *bst_delete_min(Node *root, unsigned *value){
    Node *R = new Node;
    Node *L = new Node;
    //Node *L = new Node;
    unsigned v;
    cout << "entrou no min \n";
    if(root->left == NULL){
        v = root->value;
        R = root->right;
        free(root);
        (*value) = v;
        cout << "MIN 1 \n";
        return R;
    }else{
        L = bst_delete_min(root->left, value);
        root->left = L;
        cout << "MIN 2 \n";
        return root;
    }
}

Node *bst_delete(Node *root, unsigned value, int *depht, int *aux, int *parent, int *son){
    Node *R = new Node;
    Node *L = new Node;

    if(root == NULL){
        (*aux) = 0;
        cout << "passou aqui 1 \n";
        return NULL;
    }else{
        if(value < root->value){
            (*depht)++;
            root->left = bst_delete(root->left, value, &(*depht), &(*aux), &(*parent), &(*son));
            cout << "passou aqui 2 \n";

            if(root->left == NULL || root->left->value == (*son)){
                (*parent) = root->value;
                cout << "passou aqui 9 \n";

            }else if((*aux) == 1){
                root = rotate_right(root);
                cout << "passou aqui 3 \n";
            }
            return root;

        }else if(value > root->value){
            (*depht)++;
            root->right = bst_delete(root->right, value, &(*depht), &(*aux), &(*parent), &(*son));
            cout << "passou aqui 4 \n";

            if(root->right == NULL || root->right->value == (*son)){
                (*parent) = root->value;
                cout << "passou aqui 10 \n";
            }else if((*aux) == 1){
                root = rotate_left(root);
                cout << "passou aqui 5 \n";
            }
            return root;

        }else if(value == root->value){
            if(root->left == NULL){
                R = root->right;
                //free(root);
                if(R){
                    (*son) = R->value;
                    cout << "passou aqui 11 \n";
                }
                cout << "passou aqui 6 \n";
                return R;
            }
            if(root->right == NULL){
                if(L){
                    (*son) = L->value;
                    cout << "passou aqui 12 \n";
                }//free(root);
                cout << "passou aqui 7 \n";
                return L;
            }
            if(root->left || root->right){
                root->right = bst_delete_min(root->right, &root->value);
                (*son) = root->value;
                cout << "passou aqui 8 \n";
                return root;
            }
        }
    }
}

/* void Print_Tree(Node *root){
    if(root){
        cout << root->value << endl;
        Print_Tree(root->left);
        Print_Tree(root->right);
    }
}
 */
int main(){

    string command;
    unsigned value;
    Node *root = NULL;
    int parent, son;
    int depht;
    int aux;

    do{
        depht = 0;
        aux = 1;
        cin >> command;

        if(command == "INS"){
            cin >> value;
            root = insert(root, value, &depht, &aux);
            cout << depht << "\n";
            
        }else if(command == "FND"){
            cin >> value;
            root = find(root, value, &depht, &aux);
            cout << depht << "\n";
            
        }else if(command == "DEL"){
            cin >> value;
            root = bst_delete(root, value, &depht, &aux, &parent, &son);
            cout << depht << "\n";
        }

    }while(command != "END");
    //Print_Tree(root);

    return 0;
}