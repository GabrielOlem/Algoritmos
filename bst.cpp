#include <bits/stdc++.h>
#define endl '\n'
struct node{
    int val;
    node *left, *right;
};
using namespace std;
void in_order(node *root){
    if(root == NULL){
        return;
    }
    in_order(root->left);
    cout << root -> val << ' ';
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
node *bst_search(node *root, int v){
    if(root == NULL){
        return NULL;
    }
    if(v == root -> val){
        return root;
    }
    else if(v > root->val){
        return bst_search(root->right, v);
    }
    else{
        return bst_search(root->left, v);
    }
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
        return root;
    }
    else{
        root -> right = bst_insert(root->right, v);
        return root;
    }
}
node *bst_delete_min(node *root, int valor){
    if(root -> left == NULL){
        valor = root -> val;
        node *n = root -> right;
        delete(root);
        return n;
    }
    else{
        root -> left = bst_delete_min(root -> left, valor);
        return root;
    }
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
            root->right = bst_delete_min(root->right, root->val);
            return root;
        }
    }
}
int main(int argc, char *argv[]) {
    cin.tie(nullptr);
    int valor;
    node *root = NULL;
    while(valor != -1){
        cin >> valor;
        if(valor != -1){
            root = bst_insert(root, valor);
            in_order(root);
            cout << endl;
        }
    }

    return 0;
}
