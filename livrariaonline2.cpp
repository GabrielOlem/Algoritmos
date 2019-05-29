#include <bits/stdc++.h>
#define MAX 0x3f3f3f3f
using namespace std;

typedef long long int lli;
struct aresta{
    int u;
    int v;
    lli custo;
    lli distancia;
    lli coeficiente;
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

bool verifica(pedido pedidos[], int npedidos, int local){
    for(int i=0; i<npedidos; i++){
        if(pedidos[i].qtd > estoque[local][pedidos[i].livro]){
            return 0;
        }
    }
    return 1;
}
bool agoravai(aresta a, aresta b){
    if(a.custo != b.custo){
        return a.custo < b.custo;
    }
    return a.v < b.v;
}
void bubble_up(vector<aresta> &h, int i){
    int p = floor((i - 1)/2);
    while(i > 0 && agoravai(h[i], h[p])){
        aresta aux = h[i];
        h[i] = h[p];
        h[p] = aux;
        i = p;
        p = floor((i - 1)/2);
    }
}

void heap_insert(vector<aresta> &h, aresta valor){
    h.push_back(valor);
    bubble_up(h, h.size() - 1);
}

void heapify(vector<aresta> &h, int index){
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
        heapify(h, m);
    }
}

void heap_extract(vector<aresta> &h){
    h.pop_back();
    aresta aux = h[0];
    h[0] = h[h.size()];
    h[h.size()] = aux;
    heapify(h, 0);
}

bool compare(disti a, disti b){
    return a.d < b.d;
}

void dijkstra(int s, pedido pedidos[], int npedidos){
    int vertices = grafo.size();
    vector<disti> dist(vertices);
    int precessor[vertices];

    for(int i=0; i<vertices; i++){
        dist[i].d = MAX;
        dist[i].i = i;
        precessor[i] = -1;
    }

    dist[s].d = 0;
    vector<aresta> minHeap;
    heap_insert(minHeap, {0,s,0,0,0});

    for(int h=0; h<vertices; h++){
        if(minHeap.size() == 0){
            break;
        }
        aresta removido = minHeap[0];
        heap_extract(minHeap);
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

            for(int j=0; j<npedidos; j++){
                estoque[removido.v][pedidos[j].livro] -= pedidos[j].qtd;
            }
            cout << removido.custo << endl;
            return;
        }
        if(dist[removido.v].d < removido.custo){
            continue;
        }
        for(int e=0; e<grafo[removido.v].size(); e++){
            int para = grafo[removido.v][e].v;
            if(dist[para].d > removido.custo + grafo[removido.v][e].custo){

                dist[para].d = removido.custo + grafo[removido.v][e].custo;
                precessor[para] = removido.v;

                aresta a;
                a.v = para;
                a.custo = dist[para].d;

                heap_insert(minHeap, a);
            }
        }
    }
    cout << "OOS" << endl;
}

int main(){
    int v, e, b;
    cin >> v >> e >> b;
    estoque = new int*[v];
 
    grafo.resize(v);
    
    for(int i=0; i<e; i++){
        int x, y;
        cin >> x >> y;
        aresta a;
        cin >> a.distancia >> a.coeficiente;
        a.u = x;
        a.v = y;
        a.custo = floor((a.distancia*(100 + a.coeficiente))/100);
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
                for(int i=0; i<grafo[x].size(); i++){
                    if(grafo[x][i].v == y){
                        grafo[x][i].coeficiente = w;
                        grafo[x][i].custo = grafo[x][i].distancia*(100 + w)/100;
                        break;
                    }
                }
                for(int i=0; i<grafo[y].size(); i++){
                    if(grafo[y][i].v == x){
                        grafo[y][i].coeficiente = w;
                        grafo[y][i].custo = grafo[y][i].distancia*(100 + w)/100;
                        break;
                    }
                }
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
