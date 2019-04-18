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
            for(int i=0; i<_size; i++){
                aux[i] = v[i];
            }
            _size = tam;
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
            if(soldado.id >= _size){
                resize(_size*soldado.id + 1);
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
            return a.id < b.id;
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
            return a.id < b.id;
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
            return a.id < b.id;
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
            return a.id < b.id;
        }
    }
}
void bubble_up(Dvetor<soldier> &h, int i, int criterio, Dvetor<info> &ind){
    int p = floor((i - 1)/2);
    while(i > 0 && compare(h[i], h[p], criterio)){
        soldier aux = h[i];
        h[i] = h[p];
        h[p] = aux;
        info outro = ind[h[i].id];
        ind[h[i].id] = ind[h[p].id];
        ind[h[p].id] = outro;
        i = p;
        p = floor((i - 1)/2);
    }
}
void heap_insert(Dvetor<soldier> &h, soldier &valor, int criterio, Dvetor<info> &ind){
    h.push_back(valor);
    bubble_up(h, h.size() - 1, criterio, ind);
}
void heapify(Dvetor<soldier> &h, int index, int criterio, Dvetor<info> &ind){
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
        info outro = ind[h[m].id];
        ind[h[m].id] = ind[h[index].id];
        ind[h[index].id] = outro;
        soldier aux = h[m];
        h[m] = h[index];
        h[index] = aux;
        heapify(h, m, criterio, ind);
    }
}
void heap_extracti(Dvetor<soldier> &h, int criterio, Dvetor<info> &ind, int index){
    h.pop_back();
    info outro = ind[h[index].id];
    ind[h[index].id] = ind[h[h.size()].id];
    ind[h[h.size()].id] = outro;
    soldier aux = h[index];
    h[index] = h[h.size()];
    h[h.size()] = aux;
    heapify(h, index, criterio, ind);
}
void build_heap(Dvetor<soldier> &h, int size, int criterio, Dvetor<info> &ind){
    for(int i = floor(size/2) - 1; i>=0; i--){
        heapify(h, i, criterio, ind);
    }
}
int main(int argc, char *argv[]) {
    ios::sync_with_stdio(false);
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
            indices.alocate(esquadroes[i].soldiers[j], j, i);
        }
        build_heap(esquadroes[i].soldiers, esquadroes[i].soldiers.size(), esquadroes[i].priority, indices);
    }
    string funcao;
    while(funcao != "END"){
        cin >> funcao;
        if(funcao != "END"){
            if(funcao == "ADD"){
                int esq;
                cin >> esq >> soldado.id >> soldado.service_time >> soldado.rank;
                indices.alocate(soldado, esquadroes[esq].soldiers.size(), esq);
                heap_insert(esquadroes[esq].soldiers, soldado, esquadroes[esq].priority, indices);
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
                int p = floor((index - 1)/2);
                if(compare(esquadroes[s].soldiers[index], esquadroes[s].soldiers[p], esquadroes[s].priority)){
                    bubble_up(esquadroes[s].soldiers, index, esquadroes[s].priority, indices);
                }
                else{
                    heapify(esquadroes[s].soldiers, index, esquadroes[s].priority, indices);
                }
                cout << esquadroes[s].soldiers[0].id << ' ' << esquadroes[s].soldiers[0].service_time << ' ' << esquadroes[s].soldiers[0].rank << endl;
            }
            else if(funcao == "MOV"){
                int squadi, squadj;
                cin >> squadi >> squadj;
                info antes, depois;
                int transferido = esquadroes[squadi].soldiers[0].id;
                antes = indices[transferido];
                indices[transferido].index = esquadroes[squadj].soldiers.size();
                indices[transferido].squad = squadj;
                heap_insert(esquadroes[squadj].soldiers, esquadroes[squadi].soldiers[0], esquadroes[squadj].priority, indices);
                depois = indices[transferido];
                indices[transferido] = antes;
                heap_extracti(esquadroes[squadi].soldiers, esquadroes[squadi].priority, indices, 0);
                indices[transferido] = depois;
                if(esquadroes[squadi].soldiers.size() != 0){
                    cout << esquadroes[squadi].soldiers[0].id << ' ' << esquadroes[squadi].soldiers[0].service_time << ' ' << esquadroes[squadi].soldiers[0].rank;
                }
                else{
                    cout << "-1 -1 -1";
                }
                if(esquadroes[squadj].soldiers.size() != 0){
                    cout << ' ' << esquadroes[squadj].soldiers[0].id << ' ' << esquadroes[squadj].soldiers[0].service_time << ' ' << esquadroes[squadj].soldiers[0].rank << endl;
                }
                else{
                    cout << "-1 -1 -1" << endl;
                }
            }
            else if(funcao == "CHG"){
                int squadi, squadj;
                int qtd;
                int novo_criterio;
                cin >> squadi >> squadj >> qtd >> novo_criterio;
                for(int i=0; i<qtd; i++){
                    info antes, depois;
                    int transferido = esquadroes[squadi].soldiers[0].id;
                    antes = indices[transferido];
                    indices[transferido].index = esquadroes[squadj].soldiers.size();
                    indices[transferido].squad = squadj;
                    heap_insert(esquadroes[squadj].soldiers, esquadroes[squadi].soldiers[0], esquadroes[squadj].priority, indices);
                    depois = indices[transferido];
                    indices[transferido] = antes;
                    heap_extracti(esquadroes[squadi].soldiers, esquadroes[squadi].priority, indices, 0);
                    indices[transferido] = depois;
                }
                esquadroes[squadi].priority = novo_criterio;
                build_heap(esquadroes[squadi].soldiers, esquadroes[squadi].soldiers.size(), novo_criterio, indices);
                if(esquadroes[squadi].soldiers.size() != 0){
                    cout << esquadroes[squadi].soldiers[0].id << ' ' << esquadroes[squadi].soldiers[0].service_time << ' ' << esquadroes[squadi].soldiers[0].rank;
                }
                else{
                    cout << "-1 -1 -1";
                }
                if(esquadroes[squadj].soldiers.size() != 0){
                    cout << ' ' << esquadroes[squadj].soldiers[0].id << ' ' << esquadroes[squadj].soldiers[0].service_time << ' ' << esquadroes[squadj].soldiers[0].rank << endl;
                }
                else{
                    cout << "-1 -1 -1" << endl;
                }
            }
            else if(funcao == "KIA"){
                int id;
                cin >> id;
                int s = indices[id].squad;
                int index = indices[id].index;
                heap_extracti(esquadroes[s].soldiers, esquadroes[s].priority, indices, index);
                bubble_up(esquadroes[s].soldiers, index, esquadroes[s].priority, indices);
                if(esquadroes[s].soldiers.size() != 0){
                    cout << esquadroes[s].soldiers[0].id << ' ' << esquadroes[s].soldiers[0].service_time << ' ' << esquadroes[s].soldiers[0].rank << endl;
                }
                else{
                    cout << "-1 -1 -1" << endl;
                }
            }
        }
    }
    return 0;
}
