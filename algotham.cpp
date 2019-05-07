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
vector<int> backtrack;
vector<vector<int> > permutacoes;
bool ***matriz_agentes;
bool ehCompativel(int id, vector<int> &teste){
    for(int i=0; i<teste.size(); i++){
        for(int j = i + 1; j<teste.size(); j++){
            if(matriz_agentes[id][teste[i]][teste[j]] == false){
                return 0;
            }
        }
    }
    return 1;
}
vector<int> pegaCertificado(int id){
    for(int i=0; i<permutacoes.size(); i++){
        if(ehCompativel(id, permutacoes[i])){
            return permutacoes[i];
        }
    }
}
void backtracking(int limite, int tam, int tenho){
    if(tam == tenho){
        permutacoes.push_back(backtrack);
        return;
    }
    else{
        for(int i=limite; i>=0; i--){
            backtrack.push_back(i);
            backtracking(i - 1, tam, tenho + 1);
            backtrack.pop_back();
        }
    }
}

int main(){
    int a, n, k, q;
    cin >> a >> n >> k >> q;
    agent agentes[a];
    matriz_agentes = new bool**[a];
    for(int i=0; i<a; i++){
        matriz_agentes[i] = new bool*[n];
        for(int j=0; j<n; j++){
            matriz_agentes[i][j] = new bool[n];
        }
    }
    backtracking(n - 1, k, 0);
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
            if(ehCompativel(idB, agentes[idA].certificado)){
                agentes[idB].certificado = agentes[idA].certificado;
                agentes[idB].calculado = true;
                cout << "SUCC ";
                for(int i=agentes[idA].certificado.size() - 1; i >= 0; i--){
                    cout << agentes[idA].certificado[i];
                    if(i != 0){
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
            if(ehCompativel(idA, agentes[idB].certificado)){
                agentes[idA].certificado = agentes[idB].certificado;
                agentes[idA].calculado = true;
                cout << "SUCC ";
                for(int i=agentes[idB].certificado.size() - 1; i >= 0; i--){
                    cout << agentes[idB].certificado[i];
                    if(i != 0){
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
            if(ehCompativel(idB, agentes[idA].certificado)){
                agentes[idB].certificado = agentes[idA].certificado;
                agentes[idB].calculado = true;
                cout << "SUCC ";
                for(int i=agentes[idA].certificado.size() - 1; i >= 0; i--){
                    cout << agentes[idA].certificado[i];
                    if(i != 0){
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
            int igual = 1;
            for(int i=0; i<agentes[idA].certificado.size(); i++){
                if(agentes[idA].certificado[i] != agentes[idB].certificado[i]){
                    igual = 0;
                    break;
                }
            }
            if(igual){
                cout << "SUCC ";
                for(int i=agentes[idB].certificado.size() - 1; i >= 0; i--){
                    cout << agentes[idB].certificado[i];
                    if(i != 0){
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
    return 0;
}