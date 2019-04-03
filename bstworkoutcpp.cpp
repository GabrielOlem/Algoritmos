#include <bits/stdc++.h>
#define endl '\n'
int teste;
struct node{
    int val;
    node *left, *right;
};
using namespace std;
void in_order(node *root){
    if(root == NULL){
        return;
    }
    cout << root -> val << ' ';
    in_order(root->left);
    in_order(root->right);
}
int height(node *root){
    if(root == NULL){
        return 0;
    }
    else{
        int l = height(root->left);
        int r = height(root->right);
        return (1 + max(l,r));
    }
}
int busca(node *root, int buscado){
    node *cur = root;
    int contador = 0;
    while(cur != NULL){
        if(cur -> val == buscado){
            return contador;
        }
        else if(buscado > cur -> val){
            cur = cur -> right;
        }
        else if(buscado < cur -> val){
            cur = cur -> left;
        }
        contador++;
    }
    return -1;
}
node *bst_insert(node *root, int v){
    if(root == NULL){
        node *N = new node;
        N -> val = v;
        N -> left = NULL;
        N -> right = NULL;
        return N;
    }
    else if(v < root->val){
        root -> left = bst_insert(root->left, v);
        teste++;
        return root;
    }
    else{
        root -> right = bst_insert(root->right, v);
        teste++;
        return root;
    }
}
node *minValueNode(node *root){
    node *current = root;
    while(current -> left != NULL){
        current = current -> left;
    }
    return current;
}
node *bst_delete(node *root, int v){
    if(root == NULL){
        return NULL;
    }
    else if(v < root -> val){
        root -> left = bst_delete(root->left, v);
        return root;
    }
    else if(v > root -> val){
        root -> right = bst_delete(root -> right, v);
        return root;
    }
    else{
        if(root -> left == NULL){
            node *r = root -> right;
            delete(root);
            return r;
        }
        else if(root -> right == NULL){
            node *r = root -> left;
            delete(root);
            return r;
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
    cin.tie(nullptr);
    node *root = NULL;
    int qtd;
    cin >> qtd;
    int valor;
    for(int i=0; i<qtd; i++){
        cin >> valor;
        root = bst_insert(root, valor);
    }
    string funcao;
    cout << height(root) << endl;
    while(funcao != "END"){
        cin >> funcao;
        if(funcao != "END"){
            if(funcao == "SCH"){
                cin >> valor;
                cout << busca(root, valor) << endl;
            }
            else if(funcao == "INS"){
                cin >> valor;
                teste = 0;
                root = bst_insert(root, valor);
                cout << teste << endl;
            }
            else if(funcao == "DEL"){
                cin >> valor;
                cout << busca(root, valor) << endl;
                root = bst_delete(root, valor);
            }
        }
    }
    cout << height(root) << endl;
    return 0;
}