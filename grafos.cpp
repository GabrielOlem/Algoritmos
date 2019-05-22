#include <bits/stdc++.h>
#define MAX 100000
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
void BellmanFord(vector<vector<aresta> > &grafo, int s){//Funciona com pesos negativos
    int vertices = grafo.size();
    int dist[vertices];
    for(int i=0; i<vertices; i++){
        dist[i] = 10000;
    }
    dist[s] = 0;
    for(int k=1; k<vertices; k++){
        for(int u=0; u<vertices; u++){
            for(int j=0; j<grafo[u].size(); j++){
                int de = grafo[u][j].u;
                int para = grafo[u][j].v;
                int peso = grafo[u][j].peso;
                if(dist[de] + peso < dist[para]){
                    dist[para] = dist[de] + peso;
                }
            }
        }
    }
    for(int u=0; u<vertices; u++){
        for(int j=0; j<grafo[u].size(); j++){
            if(dist[u] + grafo[u][j].peso < dist[grafo[u][j].v]){
                cout << "Tem ciclo negativo" << endl;
                break;
            }
        }
    }
    for(int i=0; i<vertices; i++){
        cout << dist[i] << ' ';
    }
}
void FloydWarshall(vector<vector<aresta> > &grafo){
    int vertices = grafo.size();
    int dist[vertices][vertices];
    for(int i=0; i<vertices; i++){
        for(int j=0; j<vertices; j++){
             dist[i][j] = MAX;
        }
    }
    for(int s=0; s<vertices; s++){
        dist[s][s] = 0;
        for(int j=0; j<grafo[s].size(); j++){
            int para = grafo[s][j].v;
            int peso = grafo[s][j].peso;
            if(dist[s][para] > peso){
                dist[s][para] = peso;
            }
        }
    }
    for(int k=1; k<=vertices; k++){
        for(int s=0; s<vertices; s++){
            for(int t=0; t<vertices; t++){
                if(dist[s][t] > dist[s][k-1] + dist[k-1][t]){
                    dist[s][t] = dist[s][k-1] + dist[k-1][t];
                }
            }
        }
    }
    for(int i=0; i<vertices; i++){
        for(int j=0; j<vertices; j++){
            cout << dist[i][j] << ' ';
        }
        cout << endl;
    }
}
int main(){
    vector<vector<aresta> > grafo;
    int n;
    cin >> n;
    int E = 0;
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
            grafo[i].push_back(a);
        }
    }
    for(int i=0; i<grafo.size(); i++){
        BellmanFord(grafo, i);
        cout << endl;
    }
    cout << endl;
    FloydWarshall(grafo);
    return 0;
}