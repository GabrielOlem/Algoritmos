#include <bits/stdc++.h>
struct node{
    int val;
    node*next;
};
using namespace std;
void dfs_visit(int S){
    p[S] = 1;
    node e = g[S];
    while(e != NULL){
        int val = e->val;
        if(p[V] == 0){
            dfs_visit(val);
        }
        e = e->next;
    }
}
int main(){
    
    return 0;
}