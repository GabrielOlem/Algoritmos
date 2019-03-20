#include <bits/stdc++.h>
#define endl '\n'

using namespace std;
struct Book{
    string codigo;
    int C;
    int jmax;
    int total_livro;
};
struct Contador{
    int livros;
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
        void size(){
            return logic;
        }
        void resize(int tam){
            v = change(tam);
        }
        T& operator[](int index){
            return v[index];
        }
        
};
int somatorio(string nome){
    int temp = 0, ce = 0, index, aux;
    for(int i=0; i<9; i++){
        if(nome[i] != '?'){
            temp += (10-i)*(nome[i] - '0');
        }
        else{
            ce = 1;
            index = (10 - i);
        }
    }
    if(ce == 1){
        int j;
        aux = temp;
        if(nome[9] == 'X'){
            aux += 10;
        }
        else{
            aux += (nome[9] - '0');
        }
        aux %= 11;
        aux = 11 - aux;
        for(j=0; j<10; j++){
            if((index*j)% 11 == aux){
                cout << j << endl;
                break;
            }
        }
        temp += (index*j);
    }
    return temp;
}
int main(int argc, char *argv[]) {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int m, q, i, j, index_contagem = 0, pos_contagem;
    int qtd_contagem = 0, tam_contagem = 1;
    cin >> m >> q;
    Dvetor<Dvetor<Dvetor<Book>>> andar;
    Dvetor<Dvetor<Contador>> frequencia;
    andar.resize(m);
    frequencia.resize(m);
    for(int i=0; i<m; i++){
        andar[i].resize(11);
    }
    Book livro;
    string funcao;
    int qtd, nucleo, estante, level;
    while(funcao != "END"){
        cin >> funcao;
        if(funcao != "END"){
            cin >> livro.codigo;
            if(funcao == "ADD"){
                cin >> livro.C;
                nucleo = somatorio(livro.codigo);
                estante = nucleo % m;
                if(codigo[9] == 'x'){
                    level = 10;
                }
                else{
                    level = (codigo[9] - '0');
                }
                
                cout << estante << endl;
            }
        }
    }
    return 0;
}
