#include <bits/stdc++.h>
#define endl '\n'

using namespace std;
struct arquivo{
    string nome;
    int id;
};

struct node{
    arquivo file;
    int qtd;
    node *next;
};

int somatorio(string nome){
    int par = 0;
    for(int i=0; nome[i]!='\0'; i++){
        par += (i+1)*nome[i];
    }
    return par;
}

int dispersa(int chave, int tam){
    return (chave % tam);
}

int busca_binaria(arquivo files[], int valor, int tamanho){
    int l = 0, r = tamanho - 1;
    while(l <= r){
        int h = (l + r)/2;
        if(files[h].id == valor){
            return h;
        }
        else if(valor < files[h].id){
            r = h - 1;
        }
        else{
            l = h + 1;
        }
    }
    return -1;
}
node *list_insert(node *tail, arquivo file){
    node *novo = new node;
    novo->file = file;
    novo->next = tail->next;
    tail->next = novo;
    return tail; 
}
node *enqueue(node *tail, arquivo file){
    node *t = list_insert(tail, file);
    return t->next;
}
int main(int argc, char *argv[]) {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int a;
    cin >> a;
    arquivo arquivos[a];
    for(int i=0; i<a; i++){
        cin >> arquivos[i].nome >> arquivos[i].id;
    }
    int m;
    cin >> m;
    node **head = new node*[m];
    node **tail = new node*[m];
    for(int i=0; i<m; i++){
        head[i] = new node;
        tail[i] = new node;
        head[i] -> next = NULL;
        tail[i] -> next = NULL;
        head[i] -> qtd = 0;
    }
    int x;
    cin >> x;
    int id, pos_id, chave, index;
    for(int i=0; i<x; i++){
        cin >> id;
        pos_id = busca_binaria(arquivos, id, a);
        if(pos_id != -1){
            chave = somatorio(arquivos[pos_id].nome);
            index = chave % m;
            head[index]->qtd++;
            tail[index] = enqueue(tail[index], arquivos[pos_id]);
            if(head[index]->next == NULL){
                head[index]->next = tail[index];
            }
        }
    }
    for(int i=0; i<m; i++){
        cout << i << ": " << head[i]->qtd << endl;
    }
    int y, count;
    cin >> y;
    string buscar;
    for(int i=0; i<y; i++){
        count = 0;
        cin >> buscar;
        chave = somatorio(buscar);
        index = chave % m;
        node *j = head[index];
        while(j->next != NULL){
            if(j->next->file.nome == buscar){
                cout << i << ": " << count+1 << endl;
            }
            j = j->next;
            count++;
        }
    }
    return 0;
}
