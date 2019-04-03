#include <stdio.h>
#include <string.h>
int teste;
typedef struct node{
    int val;
    struct node *left;
    struct node *right;
}node;
node *bst_insert(node *root, int valor){
    if(root == NULL){
        node *N = (node*)malloc(sizeof(node));
        N -> val = valor;
        N -> left = NULL;
        N -> right = NULL;
        return N;
    }
    else if(valor < root -> val){
        root -> left = bst_insert(root -> left, valor);
        teste++;
        return root;
    }
    else{
        root -> right = bst_insert(root -> right, valor);
        teste++;
        return root;
    }
}
int height(node *root){
    if(root == NULL){
        return 0;
    }
    else{
        int l = height(root -> left);
        int r = height(root -> right);
        if(l > r){
            return (1 + l);
        }
        else{
            return (1 + r);
        }
    }
}
int busca(node *root, int valor){
    node *cur = root;
    int contador = 0;
    while(cur != NULL){
        if(valor == cur -> val){
            return contador;
        }
        else if(valor < cur -> val){
            cur = cur -> left;
        }
        else{
            cur = cur -> right;
        }
        contador++;
    }
    return -1;
}
node *minValueNode(node *root){
    node *cur = root;
    while(cur -> left != NULL){
        cur = cur -> left;
    }
    return cur;
}
node *bst_delete(node *root, int valor){
    if(root == NULL){
        return NULL;
    }
    else if(valor < root -> val){
        root -> left = bst_delete(root -> left, valor);
        return root;
    }
    else if(valor > root -> val){
        root -> right = bst_delete(root -> right, valor);
        return root;
    }
    else{
        if(root -> left == NULL){
            node *r = root -> right;
            free(root);
            return r;
        }
        else if(root -> right == NULL){
            node *l = root -> left;
            free(root);
            return l;
        }
        else{
            node *temp = minValueNode(root -> right);
            root -> val = temp -> val;
            root -> right = bst_delete(root -> right, root -> val);
            return root;
        }
    }
}
int main(int argc, char *argv[]) {
    int valor;
    node *root = NULL;
    int qtd, i;
    scanf("%i", &qtd);
    for(i=0; i<qtd; i++){
        scanf("%i", &valor);
        root = bst_insert(root, valor);
    }
    char funcao[5];
    printf("%i\n", height(root));
    while(strcmp(funcao, "END") != 0){
        scanf(" %s", funcao);
        if(strcmp(funcao, "END") != 0){
            if(strcmp(funcao, "SCH") == 0){
                scanf("%i", &valor);
                printf("%i\n", busca(root, valor));
            }
            else if(strcmp(funcao, "INS") == 0){
                scanf("%i", &valor);
                teste = 0;
                root = bst_insert(root, valor);
                printf("%i\n", teste);
            }
            else{
                scanf("%i", &valor);
                printf("%i\n", busca(root, valor));
                root = bst_delete(root, valor);
            }
        }
    }
    printf("%i\n", height(root));
    return 0;
}
