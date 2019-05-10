#include <bits/stdc++.h>

using namespace std;
struct agent{
    bool lido;
    bool calculado;
    vector<int> certificado;
    agent(){
        lido = false;
        calculado = false;
    }
};
int *pais;
vector<vector<int> > permutacoes;
bool ***matriz_agentes;
bool ehCompativel2(int id, vector<int> &teste){
    for(int i=teste.size()-1; i>=0; i--){
        for(int j = i-1; j>=0; j--){
            if(matriz_agentes[id][teste[i]][teste[j]] == false){
                return 0;
            }
        }
    }
    return 1;
}
vector<int> pegaCertificado(int id){
    for(int i=0; i<permutacoes.size(); i++){
        if(ehCompativel2(id, permutacoes[i])){
            return permutacoes[i];
        }
    }
}
int find(int a){
    if(pais[a] == a){
        return a;
    }
    return pais[a] = find(pais[a]);
}
int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int a, n, k, q;
    cin >> a >> n >> k >> q;
    agent agentes[a];
    matriz_agentes = new bool**[a];
    pais = new int[a];
    for(int i=0; i<a; i++){
        matriz_agentes[i] = new bool*[n];
        for(int j=0; j<n; j++){
            matriz_agentes[i][j] = new bool[n];
        }
        pais[i] = i;
    }
    vector<int> base;
    for(int i=0; i<k; i++){
        base.push_back(i);
    }
    while(1){
        permutacoes.push_back(base);
        int aux = base.size() - 1;
        base[aux]++;
        int p = n;
        while(base[aux] == p){
            aux--;
            if(aux == -1){
                break;
            }
            base[aux]++;
            p--;
        }
        if(aux == -1){
            break;
        }
        for(int i=aux+1; i<base.size(); i++){
            base[i] = base[i-1] + 1;
        }
    }
    for(int i=0; i<q; i++){
        int idA, idB;
        cin >> idA >> idB;
        cin.ignore();
        if(!agentes[idA].lido){
            agentes[idA].lido = true;
            string linha;
            for(int i=1; i<n; i++){
                getline(cin, linha);
                for(int j=0; j<i; j++){
                    if(linha[j] == '1'){
                        matriz_agentes[idA][i][j] = true;
                    }
                    else{
                        matriz_agentes[idA][i][j] = false;
                    }
                }
            }
        }
        if(!agentes[idB].lido){
            agentes[idB].lido = true;
            string linha;
            for(int i=1; i<n; i++){
                getline(cin, linha);
                for(int j=0; j<i; j++){
                    if(linha[j] == '1'){
                        matriz_agentes[idB][i][j] = true;
                    }
                    else{
                        matriz_agentes[idB][i][j] = false;
                    }
                }
            }
        }
        if(!agentes[idA].calculado && !agentes[idB].calculado){
            agentes[idA].certificado = pegaCertificado(idA);
            agentes[idA].calculado = true;
            if(ehCompativel2(idB, agentes[idA].certificado)){
                agentes[idB].calculado = true;
                pais[idB] = idA;
                cout << "SUCC ";
                for(int i=0; i < agentes[idA].certificado.size(); i++){
                    cout << agentes[idA].certificado[i];
                    if(i+1 != agentes[idA].certificado.size()){
                        cout << ' ';
                    }
                }
                cout << endl;
            }
            else{
                cout << "FAIL" << endl;
            }
        }
        else if(!agentes[idA].calculado && agentes[idB].calculado){
            int pai = find(idB);
            if(ehCompativel2(idA, agentes[pai].certificado)){
                agentes[idA].calculado = true;
                pais[idA] = pai;
                cout << "SUCC ";
                for(int i=0; i < agentes[pai].certificado.size(); i++){
                    cout << agentes[pai].certificado[i];
                    if(i+1 != agentes[pai].certificado.size()){
                        cout << ' ';
                    }
                }
                cout << endl;
            }
            else{
                cout << "FAIL" << endl;
            }
        }
        else if(agentes[idA].calculado && !agentes[idB].calculado){
            int pai = find(idA);
            if(ehCompativel2(idB, agentes[pai].certificado)){
                agentes[idB].calculado = true;
                pais[idB] = pai;
                cout << "SUCC ";
                for(int i=0; i < agentes[pai].certificado.size(); i++){
                    cout << agentes[pai].certificado[i];
                    if(i+1 != agentes[pai].certificado.size()){
                        cout << ' ';
                    }
                }
                cout << endl;
            }
            else{
                cout << "FAIL" << endl;
            }
        }
        else{//Ja calculei os dois
            int paiA = find(idA);
            int paiB = find(idB);
            if(paiA == paiB){
                cout << "SUCC ";
                for(int i=0; i < agentes[paiB].certificado.size(); i++){
                    cout << agentes[paiB].certificado[i];
                    if(i+1 != agentes[paiB].certificado.size()){
                        cout << ' ';
                    }
                }
                cout << endl;
            }
            else{
                int igual = 1;
                for(int i=0; i<agentes[paiA].certificado.size(); i++){
                    if(agentes[paiA].certificado[i] != agentes[paiB].certificado[i]){
                        igual = 0;
                        break;
                    }
                }
                if(igual){
                    pais[paiB] = paiA;
                    cout << "SUCC ";
                    for(int i=0; i < agentes[paiB].certificado.size(); i++){
                        cout << agentes[paiB].certificado[i];
                        if(i+1 != agentes[paiB].certificado.size()){
                            cout << ' ';
                        }
                    }
                    cout << endl;
                }
                else{
                    cout << "FAIL" << endl;
                }
            }
        }
    }
    return 0;
}