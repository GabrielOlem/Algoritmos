#include <stdio.h>
#include <stdbool.h>
typedef struct agent{
    bool lido;
    bool calculado;
    int* certificado;
}agent;
int *pais;
int **permutacoes;
bool ***matriz_agentes;
bool ehCompativel2(int id, int *teste, int k){
    int i,j;
    for(i=k-1; i>=0; i--){
        for(j = i-1; j>=0; j--){
            if(matriz_agentes[id][teste[i]][teste[j]] == false){
                return 0;
            }
        }
    }
    return 1;
}
int* pegaCertificado(int id, int size, int k){
    int i;
    for(i=0; i<size; i++){
        if(ehCompativel2(id, permutacoes[i], k)){
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
    int a, n, k, q;
    scanf("%i %i %i %i", &a, &n, &k, &q);
    agent agentes[a];
    matriz_agentes = malloc(sizeof(bool**)*a);
    pais = malloc(sizeof(int)*a);
    int i, j;
    for(i=0; i<a; i++){
        matriz_agentes[i] = malloc(sizeof(bool*)*n);
        for(j=0; j<n; j++){
            matriz_agentes[i][j] = malloc(sizeof(bool)*n);
        }
        agentes[i].calculado = false;
        agentes[i].lido = false;
        pais[i] = i;
    }
    int base[k];
    for(i=0; i<k; i++){
        base[i] = i;
    }
    int size = (int)1e6;
    int index = 0;
    permutacoes = malloc(sizeof(int*)*(int)1e6);
    while(1){
        int l;
        permutacoes[index] = malloc(sizeof(int)*k);
        for(l=0; l<k; l++){
            permutacoes[index][l] = base[l];
        }
        printf("\n");
        index++;
        int aux = k - 1;
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
        int i;
        for(i=aux+1; i<k; i++){
            base[i] = base[i-1] + 1;
        }
    }
    int m;
    for(m=0; m<q; m++){
        int idA, idB;
        scanf("%i %i", &idA, &idB);
        if(!agentes[idA].lido){
            agentes[idA].lido = true;
            char linha[200];
            for(i=1; i<n; i++){
                scanf(" %s", linha);
                for(j=0; j<i; j++){
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
            char linha[200];
            for(i=1; i<n; i++){
                scanf(" %s", linha);
                for(j=0; j<i; j++){
                    if(linha[j] == '1'){
                        matriz_agentes[idB][i][j] = true;
                    }
                    else{
                        matriz_agentes[idB][i][j] = false;
                    }
                }
            }
        }
        printf("a");
        return 0;
        if(!agentes[idA].calculado && !agentes[idB].calculado){
            agentes[idA].certificado = pegaCertificado(idA, index, k);
            agentes[idA].calculado = true;
            if(ehCompativel2(idB, agentes[idA].certificado, k)){
                agentes[idB].calculado = true;
                pais[idB] = idA;
                printf("SUCC ");
                int i2;
                for(i2=0; i2 < k; i2++){
                    printf("%i", agentes[idA].certificado[i2]);
                    if(i2+1 != k){
                        printf(" ");
                    }
                }
                printf("\n");
            }
            else{
                printf("FAIL\n");
            }
        }
        else if(!agentes[idA].calculado && agentes[idB].calculado){
            int pai = find(idB);
            if(ehCompativel2(idA, agentes[pai].certificado, k)){
                agentes[idA].calculado = true;
                pais[idA] = pai;
                printf("SUCC ");
                int i2;
                for(i2=0; i2 < k; i2++){
                    printf("%i", agentes[pai].certificado[i2]);
                    if(i2+1 != k){
                        printf(" ");
                    }
                }
                printf("\n");
            }
            else{
                printf("FAIL\n");
            }
        }
        else if(agentes[idA].calculado && !agentes[idB].calculado){
            int pai = find(idA);
            if(ehCompativel2(idB, agentes[pai].certificado, k)){
                agentes[idB].calculado = true;
                pais[idB] = pai;
                printf("SUCC ");
                int i2;
                for(i2=0; i2 < k; i2++){
                    printf("%i", agentes[pai].certificado[i2]);
                    if(i2+1 != k){
                        printf(" ");
                    }
                }
                printf("\n");
            }
            else{
                printf("FAIL\n");
            }
        }
        else{//Ja calculei os dois
            int paiA = find(idA);
            int paiB = find(idB);
            if(paiA == paiB){
                printf("SUCC ");
                int i2;
                for(i2=0; i2 < k; i2++){
                    printf("%i", agentes[paiB].certificado[i2]);
                    if(i2+1 != k){
                        printf(" ");
                    }
                }
                printf("\n");
            }
            else{
                int igual = 1;
                int i2;
                for(i2=0; i2<k; i2++){
                    if(agentes[paiA].certificado[i2] != agentes[paiB].certificado[i2]){
                        igual = 0;
                        break;
                    }
                }
                if(igual){
                    pais[paiB] = paiA;
                    printf("SUCC ");
                    int i2;
                    for(i2=0; i2 < k; i2++){
                        printf("%i", agentes[paiB].certificado[i2]);
                        if(i2+1 != k){
                            printf(" ");
                        }
                    }
                    printf("\n");
                }
                else{
                    printf("FAIL\n");
                }
            }
        }
    }
    return 0;
}