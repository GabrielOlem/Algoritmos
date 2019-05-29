#include <bits/stdc++.h>
#define MAX 0x3f3f3f3f
using namespace std;

struct aresta{
    int u;
    int v;
    int custo;
    int distancia;
    int coeficiente;
};

struct pedido{
    int livro;
    int qtd;
};

struct disti{
    int d;
    int i;
};

vector<vector<aresta> > grafo;
int **estoque;
int **certificados;
bool verifica(pedido *pedidos, int npedidos, int local){
    for(int i=0; i<npedidos; i++){
        if(pedidos[i].qtd > estoque[local][pedidos[i].livro]){
            return 0;
        }
    }
    for(int j=0; j<npedidos; j++){
        estoque[local][pedidos[j].livro] -= pedidos[j].qtd;
    }
    return 1;
}

bool agoravai(aresta a, aresta b){
    if(a.custo != b.custo){
        return a.custo < b.custo;
    }
    return a.v < b.v;
}
vector<aresta> h;
void bubble_up(int i){
    int p = floor((i - 1)/2);
    while(i > 0 && agoravai(h[i], h[p])){
        aresta aux = h[i];
        h[i] = h[p];
        h[p] = aux;
        i = p;
        p = floor((i - 1)/2);
    }
}

void heap_insert(aresta valor){
    h.push_back(valor);
    bubble_up(h.size() - 1);
}

void heapify(int index){
    int r = 2*index + 2;
    int l = 2*index + 1;
    int m = index;

    if(l < h.size() && agoravai(h[l], h[m])){
        m = l;
    }

    if(r < h.size() && agoravai(h[r], h[m])){
        m = r;
    }

    if(m != index){
        aresta aux = h[m];
        h[m] = h[index];
        h[index] = aux;
        heapify(m);
    }
}

void heap_extract(){
    h.pop_back();
    aresta aux = h[0];
    h[0] = h[h.size()];
    h[h.size()] = aux;
    heapify(0);
}

void dijkstra(int s, pedido *pedidos, int npedidos){
    int vertices = grafo.size();
    vector<disti> dist(vertices);
    int precessor[vertices];
    bool visitado[vertices];
    for(int i=0; i<vertices; i++){
        dist[i].d = MAX;
        dist[i].i = i;
        precessor[i] = -1;
        visitado[i] == false;
    }
    h.clear();
    dist[s].d = 0;
    heap_insert({0,s,0,0,0});

    for(int ha=0; ha<vertices; ha++){
        if(h.size() == 0){
            break;
        }
        aresta removido = h[0];
        heap_extract();
        if(dist[removido.v].d < removido.custo){
            continue;
        }
        if(removido.v != s){
            if(verifica(pedidos, npedidos, removido.v)){
                int pre = removido.v;
                for(int j=0; j<vertices; j++){
                    if(pre != -1){
                        cout << pre << ' ';
                        pre = precessor[pre];
                    }
                    else{
                        break;
                    }
                }

                
                cout << removido.custo << endl;
                return;
            }
        }
        for(int e=0; e<grafo[removido.v].size(); e++){
            int para = grafo[removido.v][e].v;
            if(grafo[removido.v][e].coeficiente != certificados[removido.v][grafo[removido.v][e].v] && certificados[removido.v][grafo[removido.v][e].v] != -1){

                grafo[removido.v][e].coeficiente = certificados[removido.v][grafo[removido.v][e].v];
                grafo[removido.v][e].custo = grafo[removido.v][e].distancia*(100 + certificados[removido.v][grafo[removido.v][e].v])/100;
        
            }
            if(dist[para].d > removido.custo + grafo[removido.v][e].custo){

                dist[para].d = removido.custo + grafo[removido.v][e].custo;
                precessor[para] = removido.v;

                aresta a;
                a.v = para;
                a.custo = dist[para].d;

                heap_insert(a);
            }
        }
    }
    while(h.size() != 0){
        aresta removido = h[0];
        heap_extract();
        if(verifica(pedidos, npedidos, removido.v)){
            int pre = removido.v;
            for(int j=0; j<vertices; j++){
                if(pre != -1){
                    cout << pre  << ' ';
                    pre = precessor[pre];
                }
                else{
                    break;
                }
            }
            cout << removido.custo << endl;
            return;
        }
    }
    cout << "OOS" << endl;
}

int main(){
    int v, e, b;
    cin >> v >> e >> b;
    estoque = new int*[v];
    certificados = new int*[v];
    grafo.resize(v);
    for(int i=0; i<v; i++){
        certificados[i] = new int[v];
        for(int j=0; j<v; j++){
            certificados[i][j] = -1;
        }
    }
    for(int i=0; i<e; i++){
        int x, y;
        cin >> x >> y;
        aresta a;
        cin >> a.distancia >> a.coeficiente;
        a.custo = floor((a.distancia*(100 + a.coeficiente))/100);
        certificados[x][y] = a.coeficiente;
        certificados[y][x] = a.coeficiente;
        a.u = x;
        a.v = y;
        grafo[x].push_back(a);
        a.v = x;
        a.u = y;
        grafo[y].push_back(a);
    }
    for(int i=0; i<v; i++){
        estoque[i] = new int[b];
        for(int j=0; j<b; j++){
            cin >> estoque[i][j];
        }
    }

    string oper;

    while(oper != "END"){
        cin >> oper;
        if(oper != "END"){
            if(oper == "ORD"){
                int local, npedidos;
                cin >> local >> npedidos;
                pedido livros[npedidos];
                int foi = 1;
                for(int i=0; i<npedidos; i++){
                    cin >> livros[i].livro >> livros[i].qtd;
                    if(livros[i].qtd > estoque[local][livros[i].livro]){
                        foi = 0;
                    }
                }
                if(foi){
                    cout << local << " 0" << endl;
                    for(int i=0; i<npedidos; i++){
                        estoque[local][livros[i].livro] -= livros[i].qtd;
                    }
                }
                else{
                    dijkstra(local, livros, npedidos);
                }
            }
            else if(oper == "UPD"){
                int x, y, w;
                cin >> x >> y >> w;
                certificados[x][y] = w;
                certificados[y][x] = w;
            }
            else if(oper == "STK"){
                int x, i, q;
                cin >> x >> i >> q;
                estoque[x][i] += q;
            }
        }
    }
    return 0;
}
