#include <bits/stdc++.h>
#define endl '\n'
using namespace std;
class soldier{
    public:
    int rank;
    int id;
    int service_time;
};
template <class T>
class Dvetor{
    private:
        T * v;
        int logic;
        int _size;
    public:
        Dvetor(void){
            v = nullptr;
            logic = 0;
            _size = 0;
        }
        ~Dvetor(void){
            delete[] v;
        }
        bool full(void){
            if(_size == logic){
                return true;
            }
            else{
                return false;
            }
        }
        T *change(void){
            T *aux = new T[2*(_size) + 1];
            for(int i=0; i<logic; i++){
                aux[i] = v[i];
            }
            _size = _size * 2 + 1;
            return aux;
        }
        T *change(int tam){
            T *aux = new T[tam];
            for(int i=0; i<logic; i++){
                aux[i] = v[i];
            }
            return aux;
        }
        void push_back(T aux){
            if(full()){
                v = change();
            }
            v[logic] = aux;
            logic++;
        }
        void pop_back(void){
            logic--;
        }
        int size(){
            return logic;
        }
        int ba(){
            return _size;
        }
        void resize(int tam){
            v = change(tam);
        }
        T& operator[](int index){
            return v[index];
        }
        void alocate(soldier &soldado, int index, int squad){
            if(soldado.id > _size){
                resize(soldado.id+1);
            }
            v[soldado.id].index = index;
            v[soldado.id].squad = squad;    
        }
};
class info{
    public:
    int index;
    int squad;
};
class squad{
    public:
    int priority;
    Dvetor<soldier> soldiers;
};
bool compare(soldier &a, soldier &b, int criterio){
    if(criterio == 0){
        if(a.service_time < b.service_time){
            return true;
        }
        else if(a.service_time > b.service_time){
            return false;
        }
        else{
            if(a.rank > b.rank){
                return true;
            }
            else if(a.rank < b.rank){
                return false;
            }
        }
    }
    else if(criterio == 1){
        if(a.service_time > b.service_time){
            return true;
        }
        else if(a.service_time < b.service_time){
            return false;
        }
        else{
            if(a.rank < b.rank){
                return true;
            }
            else if(a.rank > b.rank){
                return false;
            }
        }
    }
    else if(criterio == 2){
        if(a.rank < b.rank){
            return true;
        }
        else if(a.rank > b.rank){
            return false;
        }
        else{
            if(a.service_time > b.service_time){
                return true;
            }
            else if(a.service_time < b.service_time){
                return false;
            }
        }
    }
    else{
        if(a.rank > b.rank){
            return true;
        }
        else if(a.rank < b.rank){
            return false;
        }
        else{
            if(a.service_time < b.service_time){
                return true;
            }
            else if(a.service_time > b.service_time){
                return false;
            }
        }
    }
    return a.id < b.id;
}
void bubble_up(Dvetor<soldier> &h, int i, int criterio){
    int p = floor((i - 1)/2);
    while(i > 0 && compare(h[i], h[p], criterio)){
        soldier aux = h[i];
        h[i] = h[p];
        h[p] = aux;
        i = p;
        p = floor((i - 1)/2);
    }
}
void heap_insert(Dvetor<soldier> &h, soldier valor, int criterio){
    h.push_back(valor);
    bubble_up(h, h.size() - 1, criterio);
}
void heapify(Dvetor<soldier> &h, int index, int criterio){
    int r = 2*index + 2;
    int l = 2*index + 1;
    int m = index;
    if(l < h.size() && compare(h[l], h[m], criterio)){
        m = l;
    }
    if(r < h.size() && compare(h[r], h[m], criterio)){
        m = r;
    }
    if(m != index){
        soldier aux = h[m];
        h[m] = h[index];
        h[index] = aux;
        heapify(h, m, criterio);
    }
}
void heap_extract(Dvetor<soldier> &h, int criterio){
    h.pop_back();
    soldier aux = h[0];
    h[0] = h[h.size()];
    h[h.size()] = aux;
    heapify(h, 0, criterio);
}
void build_heap(Dvetor<soldier> &h, int size, int criterio){
    for(int i = floor(size/2) - 1; i>=0; i--){
        heapify(h, i, criterio);
    }
}
int main(int argc, char *argv[]) {
    //ios::sync_with_stdio(false);
    cin.tie(nullptr);
    Dvetor<info> indices;
    int squads;
    soldier soldado;
    cin >> squads;
    int qtd_squads;
    squad esquadroes[squads];
    for(int i=0; i<squads; i++){
        cin >> qtd_squads;
        cin >> esquadroes[i].priority;
        for(int j=0; j<qtd_squads; j++){
            cin >> soldado.id;
            cin >> soldado.service_time;
            cin >> soldado.rank;
            esquadroes[i].soldiers.push_back(soldado);
        }
    }
    for(int i=0; i<squads; i++){
        build_heap(esquadroes[i].soldiers, esquadroes[i].soldiers.size(), esquadroes[i].priority);
        for(int j=0; j<esquadroes[i].soldiers.size(); j++){
            indices.alocate(esquadroes[i].soldiers[j], j, i);
        }
    }
    string funcao;
    while(funcao != "END"){
        cin >> funcao;
        if(funcao != "END"){
            if(funcao == "ADD"){
                int esq;
                cin >> esq;
                cin >> soldado.id;
                cin >> soldado.service_time;
                cin >> soldado.rank;
                heap_insert(esquadroes[esq].soldiers, soldado, esquadroes[esq].priority);
                cout << esquadroes[esq].soldiers[0].id << ' ' << esquadroes[esq].soldiers[0].service_time << ' ' << esquadroes[esq].soldiers[0].rank << endl;
            }
            else if(funcao == "UPD"){
                int id;
                int ts;
                int r;
                cin >> id >> ts >> r;
                int index = indices[id].index;
                int s = indices[id].squad;
                esquadroes[s].soldiers[index].service_time = ts;
                esquadroes[s].soldiers[index].rank = r;
                updateHeap(esquadroes[s].soldiers, indices, index);
            }
        }
    }
    return 0;
}
