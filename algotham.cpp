#include <bits/stdc++.h>

using namespace std;
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
int main(){
    int total_agents, agent_size, clique, qtd;
    cin >> total_agents >> agent_size >> clique >> qtd;
    
    return 0;
}