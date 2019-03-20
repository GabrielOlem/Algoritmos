#include <bits/stdc++.h>
#define endl '\n'

using namespace std;

struct node{
    string codigo;
    int qtd_andar, qtd_livro;
    node *next;
};
struct contador{
    int prateleiras, quantidade;
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
void print(node* comeco){
    node* i;
    for(i=comeco; i->next!=NULL; i = i->next){
        cout << i->next->codigo << " ";
    }
    puts("");
}
node* list_insert(node *cur, string val, int qtd){
    node *h = new node;
    h->codigo = val;
    h->qtd_livro = qtd;
    h->next = cur->next;
    cur->next = h;
    return cur;
}
node* list_ordenado(node *head, string numero, int qtd){
    node *i = head;
    while(1){
        if(i -> next == NULL){
            i = list_insert(i, numero, qtd);
            return head;
        }
        if(i->next->codigo == numero){
            i->next->qtd_livro += qtd;
            return head;
        }
        if(numero > i -> codigo && numero < i -> next -> codigo){
            i = list_insert(i, numero, qtd);
            return head;
        }
        
        i = i->next;
    }
}

int main(int argc, char *argv[]) {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int m, q, i, j, index_contagem = 0, pos_contagem;
    double qtd_contagem = 0, tam_contagem = 1;
    cin >> m >> q;
    contador *contagem = new contador[1];
    contagem.prateleiras = -1;
    contagem.quantidade = -1;
    node ***andar = new node**[m];
    for(i=0; i<m; i++){
        andar[i] = new node*[11];
        for(j=0; j<11; j++){
            andar[i][j] = new node;
            andar[i][j] -> next = NULL;
            andar[i][j] -> qtd_andar = 0;
        }
    }
    string funcao, codigo;
    int qtd, nucleo, estante, level;
    while(funcao != "END"){
        cin >> funcao;
        if(funcao != "END"){
            cin >> codigo;
            if(funcao == "ADD"){
                cin >> qtd;
                int cheio = 0, atual;
                nucleo = somatorio(codigo);
                estante = nucleo % m;
                if(codigo[9] == 'x'){
                    level = 10;
                }
                else{
                    level = (codigo[9] - '0');
                }
                pos_contagem = nucleo % tam_contagem;
                if(qtd_contagem/tam_contagem >= 0.5){
                    contagem = rehashing(contagem, &tam_contagem);
                }
                if(qtd + andar[estante][level] -> qtd_andar <= q){
                    andar[estante][level] = list_ordenado(andar[estante][level], codigo, qtd);
                    andar[estante][level] -> qtd_andar += qtd;
                }
                else{
                    andar[estante][level] = list_ordenado(andar[estante][level], codigo, q - andar[estante][level]->qtd_andar);
                    qtd -= (q - andar[estante][level]->qtd_andar);
                    andar[estante][level] -> qtd_andar += (q - andar[estante][level]->qtd_andar);
                    for(int j=1; j<11; j++){
                        atual = (level + j) % 11;
                        if(qtd + andar[estante][atual] -> qtd_andar <= q){
                            andar[estante][atual] = list_ordenado(andar[estante][atual], codigo, qtd);
                            andar[estante][atual] -> qtd_andar += qtd;
                            qtd = 0;
                        }
                        else{
                            andar[estante][atual] = list_ordenado(andar[estante][atual], codigo, q - andar[estante][atual]->qtd_andar);
                            qtd -= (q - andar[estante][atual]->qtd_andar);
                            andar[estante][atual] -> qtd_andar += (q - andar[estante][atual]->qtd_andar);
                        }
                        if(qtd == 0){
                            break;
                        }
                    }
                }
                cout << estante << endl;
            }
        }
    }
    return 0;
}
