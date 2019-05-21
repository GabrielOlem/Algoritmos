#include <bits/stdc++.h>
#define MAX (int)1e7
using namespace std;
struct aresta{
    int u;
    int v;
    int peso;
};
int* pais;
int find_pc(int a){
    if(pais[a] == a){
        return a;
    }
    return pais[a] = find_pc(pais[a]);
}
void dfs_visit(vector<vector<int> > &grafo, vector<bool> &p, int s){
    p[s] = true;
    cout << s << ' ';
    for(int i=0; i<grafo[s].size(); i++){
        int v = grafo[s][i];
        if(!p[v]){
            dfs_visit(grafo, p, v);
        }
    }
}
void dfs(vector<vector<int> > &grafo){
    vector<bool> p(grafo.size());
    for(int i=0; i<p.size(); i++){
        p[i] = false;
    }
    for(int i=0; i<grafo.size(); i++){
        if(!p[i]){
            dfs_visit(grafo, p, i);
        }
    }
}
void bfs_visit(vector<vector<int> > &grafo, vector<bool> &p, int s){
    queue<int> fila;
    fila.push(s);
    p[s] = true;
    while(!fila.empty()){
        int u = fila.front();
        cout << u << ' ';
        fila.pop();
        for(int i=0; i<grafo[u].size(); i++){
            int v = grafo[u][i];
            if(!p[v]){
                fila.push(v);
                p[v] = true;
            }
        }
    }
}
void bfs(vector<vector<int> > &grafo){
    vector<bool> p(grafo.size());
    for(int i=0; i<p.size(); i++){
        p[i] = false;
    }
    for(int i=0; i<grafo.size(); i++){
        if(!p[i]){
            bfs_visit(grafo, p, i);
        }
    }
}
bool compare(aresta a, aresta b){
    return(a.peso < b.peso);
}
int kruskal(vector<aresta> &arestas){//Funciona com pesos negativos
    sort(arestas.begin(), arestas.end(), compare);
    int co = 0;
    for(int i=0; i<arestas.size(); i++){
        if(find_pc(arestas[i].u) != find_pc(arestas[i].v)){
            pais[find_pc(arestas[i].u)] = find_pc(arestas[i].v);
            co += arestas[i].peso;
        }
    }
    return co;
}
int main(){
    vector<vector<aresta> > grafo;
    vector<aresta> arestas;
    int n;
    cin >> n;
    pais = new int[n];
    grafo.resize(n);
    for(int i=0; i<n; i++){
        int vizinhos;
        cin >> vizinhos;
        pais[i] = i;
        for(int j=0; j<vizinhos; j++){
            aresta a;
            cin >> a.v >> a.peso;
            a.u = i;
            arestas.push_back(a);
        }
    }
    cout << kruskal(arestas);
    return 0;
}