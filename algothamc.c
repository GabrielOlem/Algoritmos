#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
typedef struct agent{
    bool lido;
    bool calculado;
    int certificado;
}agent;
int **permutacoes;
char ***matriz_agentes;
bool ehCompativel2(int id, int *teste, int k){
    int i,j;
    for(i=k-1; i>=0; i--){
        for(j = i-1; j>=0; j--){
            if(matriz_agentes[id][teste[i]][teste[j]] == 48){
                return 0;
            }
        }
    }
    return 1;
}
int pegaCertificado(int id, int size, int k){
    int i;
    for(i=0; i<size; i++){
        if(ehCompativel2(id, permutacoes[i], k)){
            return i;
        }
    }
}
int main(){
    int a, n, k, q;
    scanf("%i %i %i %i", &a, &n, &k, &q);
    agent agentes[a];
    matriz_agentes = (char***)malloc(sizeof(char**)*a);
    int i, j;
    int base[k];
    for(i=0; i<a; i++){
        matriz_agentes[i] = (char**)malloc(sizeof(char*)*n);
        for(j=0; j<n; j++){
            matriz_agentes[i][j] = (char*)malloc(sizeof(char)*n);
            if(j < k){
                base[j] = j;
            }
        }
        agentes[i].calculado = false;
        agentes[i].lido = false;
        pais[i] = i;
    }
    int index = 0;
    permutacoes = (int**)malloc(sizeof(int*)*(int)1e6);
    while(1){
        int l;
        permutacoes[index] = (int*)malloc(sizeof(int)*k);
        for(l=0; l<k; l++){
            permutacoes[index][l] = base[l];
        }
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
            for(i=1; i<n; i++){
                scanf(" %s", matriz_agentes[idA][i]);
            }
        }
        if(!agentes[idB].lido){
            agentes[idB].lido = true;
            for(i=1; i<n; i++){
                scanf(" %s", matriz_agentes[idB][i]);
            }
        }
        if(!agentes[idA].calculado && !agentes[idB].calculado){
            agentes[idA].certificado = pegaCertificado(idA, index, k);
            agentes[idA].calculado = true;
            if(ehCompativel2(idB, permutacoes[agentes[idA].certificado], k)){
                agentes[idB].calculado = true;
                agentes[idB].certificado = agentes[idA].certificado;
                printf("SUCC ");
                int i2;
                for(i2=0; i2 < k; i2++){
                    printf("%i", permutacoes[agentes[idA].certificado][i2]);
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
        else if(agentes[idA].calculado && agentes[idB].calculado){
            if(agentes[idA].certificado == agentes[idB].certificado){
                printf("SUCC ");
                int i2;
                for(i2=0; i2 < k; i2++){
                    printf("%i", permutacoes[agentes[idA].certificado][i2]);
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
        else if(agentes[idB].calculado){
            if(ehCompativel2(idA, permutacoes[agentes[idB].certificado], k)){
                agentes[idA].calculado = true;
                agentes[idA].certificado = agentes[idB].certificado;
                printf("SUCC ");
                int i2;
                for(i2=0; i2 < k; i2++){
                    printf("%i", permutacoes[agentes[idB].certificado][i2]);
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
        else{
            if(ehCompativel2(idB, permutacoes[agentes[idA].certificado], k)){
                agentes[idB].calculado = true;
                agentes[idB].certificado = agentes[idA].certificado;
                printf("SUCC ");
                int i2;
                for(i2=0; i2 < k; i2++){
                    printf("%i", permutacoes[agentes[idA].certificado][i2]);
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
    return 0;
}