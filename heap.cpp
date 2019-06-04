#include <bits/stdc++.h>
#define endl '\n'

using namespace std;
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
        void print(){
            for(int i=0; i<size(); i++){
                cout << v[i] << ' ';
            }
            cout << endl;
        }
        
};
void bubble_up(Dvetor<int> &h, int i){
    int p = floor((i - 1)/2);
    while(i > 0 && h[i] <= h[p]){
        int aux = h[i];
        h[i] = h[p];
        h[p] = aux;
        i = p;
        p = floor((i - 1)/2);
    }
}
void heap_insert(Dvetor<int> &h, int valor){
    h.push_back(valor);
    bubble_up(h, h.size() - 1);
}
void heapify(Dvetor<int> &h, int index){
    int r = 2*index + 2;
    int l = 2*index + 1;
    int m = index;
    if(l < h.size() && h[l] >= h[m]){
        m = l;
    }
    if(r < h.size() && h[r] >= h[m]){
        m = r;
    }
    if(m != index){
        int aux = h[m];
        h[m] = h[index];
        h[index] = aux;
        heapify(h, m);
    }
}
void heap_extract(Dvetor<int> &h){
    h.pop_back();
    int aux = h[0];
    h[0] = h[h.size()];
    h[h.size()] = aux;
    heapify(h, 0);
}
void build_heap(Dvetor<int> &h, int size){
    for(int i = floor(size/2) - 1; i>=0; i--){
        heapify(h, i);
    }
}
void heap_sort(Dvetor<int> &h){
    cout << h.size() << endl;
    build_heap(h, h.size());
    int size = h.size();
    for(int i=0; i<size; i++){
        heap_extract(h);
    }
}
int main(int argc, char *argv[]) {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    Dvetor<int> vetor;
    int ah = 0;
    int valor;
    while(valor != -1){
        cin >> valor;
        if(valor != -1){
            ah++;
            vetor.push_back(valor);
        }
    }
    vetor.print();
    heap_sort(vetor);
    for(int i=0; i<ah; i++){
        cout << vetor[i] << ' ';
    }
    cout << endl;
    return 0;
}
