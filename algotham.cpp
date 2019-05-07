#include <bits/stdc++.h>

using namespace std;
int pais[(int)1e6];
int pesos[(int)1e6];
bool lido[(int)1e6];
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
Dvetor<int> teste;
Dvetor<int> certo;
bool **matriz;
bool ehCompativel(){
    for(int i=0; i<teste.size(); i++){
        for(int j = i + 1; j<teste.size(); j++){
            if(matriz[teste[i]][teste[j]] == false){
                return 0;
            }
        }
    }
    return 1;
}
int find(int a){
    if(pais[a] == a){
        return a;
    }
    return pais[a] = find(pais[a]);
}
void join(int a, int b){
    a = find(a);
    b = find(b);
    if(pesos[a] < pesos[b]){
        pais[b] = a;
    }
    if(pesos[b] < pesos[a]){
        pais[a] = b;
    }
    if(pesos[b] == pesos[a]){
        pais[a] = b;
        pesos[b]++;
    }
}
int backtracking(int limite, int tam, int tenho){
    if(tam == tenho){
        if(ehCompativel()){
            for(int i=teste.size() - 1; i>=0; i--){
                certo.push_back(teste[i]);
            }
            return 1;
        }
        return 0;
    }
    else{
        for(int i=limite; i>=0; i--){
            teste.push_back(i);
            int ret = backtracking(i - 1, tam, tenho + 1);
            if(ret == 1){
                return ret;
            }
            teste.pop_back();
        }
    }
}
int main(){
    int total_agents, agent_size, clique, qtd;
    cin >> total_agents >> agent_size >> clique >> qtd;
    matriz = new bool*[agent_size + 1];
    for(int i=0; i<agent_size + 1; i++){
        matriz[i] = new bool[agent_size];
    }
    for(int i=0; i<total_agents; i++){
        lido[i] = false;
        pais[i] = i;
        pesos[i] = 0;
    }
    for(int i=0; i<qtd; i++){
        int idA, idB;
        cin >> idA >> idB;
    }
    string linha;
    cin.ignore();
    for(int i=1; i<agent_size; i++){
        getline(cin, linha);
        for(int j=0; j<i; j++){
            if(linha[j] == '1'){
                matriz[i][j] = true;
            }
            else{
                matriz[i][j] = false;
            }
        }
    }
    backtracking(agent_size, clique, 0);
    cout << endl;
    for(int i=0; i<certo.size(); i++){
        cout << certo[i] << ' ';
    }
    return 0;
}