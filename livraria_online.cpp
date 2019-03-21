#include <bits/stdc++.h>
#define endl '\n'

using namespace std;
struct Book{
    string codigo;
    int jmax;
    int total_livro;
    Book(){
        jmax = 0;
        total_livro = 0; 
    }
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
                break;
            }
        }
        temp += (index*j);
    }
    return temp;
}
int busca_binaria(Dvetor<Book> &andar, string codigo, int qtd){
    int l = 0;
    int r = qtd - 1;
    while(l <= r){
        int h = (l + r)/2;
        if(andar[h].codigo == codigo){
            return h;
        }
        else if(codigo < andar[h].codigo){
            r = h - 1;
        }
        else{
            l = h + 1;
        }
    }
    return -1;
}
void busca_modif(Dvetor<Book> &andar, Book livro, int qtd){
    int pos = busca_binaria(andar, livro.codigo, andar.size());
    if(pos == -1){
        livro.total_livro = qtd;
        for(int i=0; i<andar.size(); i++){
            if(andar[i].codigo > livro.codigo){
                Book aux = livro;
                livro = andar[i];
                andar[i] = aux;
            }
        }
        andar.push_back(livro);
    }
    else{
        andar[pos].total_livro += qtd;
    }
}
void deletar(Dvetor<Book> &andar, Book livro){
    for(int i=1; i<andar.size(); i++){
        if(andar[i - 1].codigo == livro.codigo){
            Book aux = andar[i - 1];
            andar[i - 1] = andar[i];
            andar[i] = aux;
        }
    }
}
int main(int argc, char *argv[]) {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int m, q;
    cin >> m >> q;
    Dvetor<Dvetor<Dvetor<Book>>> andar;
    andar.resize(m);
    int frequencia[m][11];
    for(int i=0; i<m; i++){
        andar[i].resize(11);
        for(int j=0; j<11; j++){
            frequencia[i][j] = 0;
        }
    }
    Book livro;
    string funcao;
    int qtd, nucleo, estante, level;
    while(funcao != "END"){
        cin >> funcao;
        if(funcao != "END"){
            cin >> livro.codigo;
            if(funcao == "ADD"){
                cin >> qtd;
                int noh = 0;
                int total = qtd;
                nucleo = somatorio(livro.codigo);
                estante = nucleo % m;
                if(livro.codigo[9] == 'x'){
                    level = 10;
                }
                else if(livro.codigo[9] == '?'){
                    level = 11 - estante;
                }
                else{
                    level = (livro.codigo[9] - '0');
                }
                if(qtd + frequencia[estante][level] <= q){//Foi no primeiro
                    busca_modif(andar[estante][level], livro, qtd);
                    frequencia[estante][level] += qtd;
                    int pos = busca_binaria(andar[estante][level], livro.codigo, andar[estante][level].size());
                    if(pos != -1){
                        andar[estante][level][pos].jmax = 0;
                    }
                }
                else{//Não coube no primeiro
                    if(q != frequencia[estante][level]){
                        busca_modif(andar[estante][level], livro, q - frequencia[estante][level]);//Coloca o que der no primeiro
                        qtd -= (q - frequencia[estante][level]);
                    }
                    frequencia[estante][level] = q;
                    for(int j=1; j<11; j++){
                        int atual = (level + j) % 11;
                        if(qtd + frequencia[estante][atual] <= q){//Coube o que faltava na atual
                            busca_modif(andar[estante][atual], livro, qtd);
                            frequencia[estante][atual] += qtd;
                            qtd = 0;
                        }
                        else{
                            busca_modif(andar[estante][atual], livro, q - frequencia[estante][atual]);
                            qtd -= (q - frequencia[estante][atual]);
                            frequencia[estante][atual] = q;
                        }
                        if(qtd == 0){
                            int pos = busca_binaria(andar[estante][level], livro.codigo, andar[estante][level].size());
                            if(pos != -1){
                                andar[estante][level][pos].jmax = j;
                            }
                            else{
                                for(int i=1;i<11;i++){
                                    if(busca_binaria(andar[estante][(level+i)%11],livro.codigo, andar[estante][level].size()) != -1) {
                                        andar[estante][level][pos].jmax = j - noh; 
                                        break;
                                    }
                                    else{
                                        noh++;
                                    }
                                }
                            } 
                            break;
                        }
                    }  
                }
                int auxi = 0;
                int pos2 = busca_binaria(andar[estante][level], livro.codigo, andar[estante][level].size());
                while(pos2 == -1){
                    auxi++;
                    pos2 = busca_binaria(andar[estante][(level + auxi) % 11], livro.codigo, andar[estante][(level + auxi) % 11].size());
                }
                int prateleiras = andar[estante][(level + auxi) % 11][pos2].jmax;
                total = 0;
                for(int i = 0; i<=prateleiras; i++){
                    pos2 = busca_binaria(andar[estante][(level + i + auxi) % 11], livro.codigo, andar[estante][(level + i + auxi) % 11].size());
                    total += andar[estante][(level + i + auxi) % 11][pos2].total_livro;
                }
                cout << estante << " " << total << " " << prateleiras + 1 << endl;        
            }
            else if(funcao == "QRY"){
                nucleo = somatorio(livro.codigo);
                estante = nucleo % m;
                if(livro.codigo[9] == 'x'){
                    level = 10;
                }
                else if(livro.codigo[9] == '?'){
                    level = 11 - estante;
                }
                else{
                    level = (livro.codigo[9] - '0');
                }
                int auxi = 0;
                int pos2 = busca_binaria(andar[estante][level], livro.codigo, andar[estante][level].size());
                if(pos2 == -1){
                    for(auxi = 1; auxi < 11; auxi++){
                        pos2 = busca_binaria(andar[estante][(level + auxi) % 11], livro.codigo, andar[estante][(level + auxi) % 11].size());
                        if(pos2 != -1){
                            break;
                        }
                    }
                }
                if(pos2 == -1){
                    cout << estante << " 0 0" << endl;
                }
                else{
                    int prateleiras = andar[estante][(level + auxi) % 11][pos2].jmax;
                    int total = 0;
                    for(int i = 0; i<=prateleiras; i++){
                        pos2 = busca_binaria(andar[estante][(level + i + auxi) % 11], livro.codigo, andar[estante][(level + i + auxi) % 11].size());
                        total += andar[estante][(level + i + auxi) % 11][pos2].total_livro;
                    }
                    cout << estante << ' ' << total << ' ' << prateleiras + 1 << endl;
                }
            }
            else if(funcao == "REM"){
                cin >> qtd;
                nucleo = somatorio(livro.codigo);
                estante = nucleo % m;
                if(livro.codigo[9] == 'x'){
                    level = 10;
                }
                else if(livro.codigo[9] == '?'){
                    level = 11 - estante;
                }
                else{
                    level = livro.codigo[9] - '0';
                }
                int pos2 = busca_binaria(andar[estante][level], livro.codigo, andar[estante][level].size());
                int auxi = 0;
                while(pos2 == -1){
                    auxi++;
                    pos2 = busca_binaria(andar[estante][(level + auxi) % 11], livro.codigo, andar[estante][(level + auxi) % 11].size());
                }
                int prateleiras = andar[estante][(level + auxi) % 11][pos2].jmax;
                int pos3 = busca_binaria(andar[estante][(level + auxi + prateleiras) % 11], livro.codigo, andar[estante][(level + auxi + prateleiras) % 11].size());
                if(andar[estante][(level + auxi + prateleiras)%11][pos3].total_livro - qtd >= 0){
                    frequencia[estante][(level + auxi + prateleiras)%11] -= qtd;
                    andar[estante][(level + auxi + prateleiras)%11][pos3].total_livro -= qtd;
                    if(andar[estante][(level + auxi + prateleiras)%11][pos3].total_livro == 0){
                        andar[estante][(level + auxi) % 11][pos2].jmax--;
                        deletar(andar[estante][(level + auxi + prateleiras)%11], livro);
                        andar[estante][(level + auxi + prateleiras) % 11].pop_back();
                    }
                }
                else{//Nao deu para tirar tudo do (level + auxi + prateleiras)
                    qtd -= andar[estante][(level + auxi + prateleiras) % 11][pos3].total_livro;
                    frequencia[estante][(level + auxi + prateleiras)%11] -= andar[estante][(level + auxi + prateleiras)%11][pos3].total_livro;
                    andar[estante][(level + auxi + prateleiras)%11][pos3].total_livro = 0;
                    deletar(andar[estante][(level + auxi + prateleiras)%11], livro);
                    andar[estante][(level + auxi) % 11][pos2].jmax--;
                    prateleiras = andar[estante][(level + auxi) % 11][pos2].jmax;
                    for(int j=prateleiras; j>=0; j--){
                        
                    }
                }
                prateleiras = andar[estante][(level + auxi) % 11][pos2].jmax;
                int total = 0;
                for(int i=prateleiras; i >= 0; i--){
                    pos2 = busca_binaria(andar[estante][(level + auxi + i)%11], livro.codigo, andar[estante][(level + auxi + i) % 11].size());
                    total += andar[estante][(level + auxi + i)%11][pos2].total_livro;
                }
                cout << estante << ' ' << total << ' ' << prateleiras+1 << endl;
            }
        }
    }
    return 0;
}
