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
int main(int argc, char *argv[]) {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    Dvetor<int> vetor;
    int valor;
    cout << vetor.size();
    while(valor != -1){
        cin >> valor;
        if(valor != -1){
            heap_insert(vetor, valor);
        }
    }
    for(int j=0; j<vetor.size(); j++){
        cout << vetor[j] << ' ';
    }
    return 0;
}
