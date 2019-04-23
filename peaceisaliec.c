#include <stdio.h>
#include <string.h>

typedef struct soldier{
    int rank;
    int id;
    int service_time;
}soldier;
typedef struct info{
    int index;
    int squad;
}info;
typedef struct squad{
    int priority;
    soldier soldiers[1000000];
}squad;
int compare(soldier a, soldier b, int criterio){
    if(criterio == 0){
        if(a.service_time < b.service_time){
            return 1;
        }
        else if(a.service_time > b.service_time){
            return 0;
        }
        else{
            if(a.rank > b.rank){
                return 1;
            }
            else if(a.rank < b.rank){
                return 0;
            }
            return a.id < b.id;
        }
    }
    else if(criterio == 1){
        if(a.service_time > b.service_time){
            return 1;
        }
        else if(a.service_time < b.service_time){
            return 0;
        }
        else{
            if(a.rank < b.rank){
                return 1;
            }
            else if(a.rank > b.rank){
                return 0;
            }
            return a.id < b.id;
        }
    }
    else if(criterio == 2){
        if(a.rank < b.rank){
            return 1;
        }
        else if(a.rank > b.rank){
            return 0;
        }
        else{
            if(a.service_time > b.service_time){
                return 1;
            }
            else if(a.service_time < b.service_time){
                return 0;
            }
            return a.id < b.id;
        }
    }
    else{
        if(a.rank > b.rank){
            return 1;
        }
        else if(a.rank < b.rank){
            return 0;
        }
        else{
            if(a.service_time < b.service_time){
                return 1;
            }
            else if(a.service_time > b.service_time){
                return 0;
            }
            return a.id < b.id;
        }
    }
}
void bubble_up(soldier h[], int i, int criterio, info ind[]){
    int p = ((i - 1)/2);
    while(i > 0 && compare(h[i], h[p], criterio)){
        soldier aux = h[i];
        h[i] = h[p];
        h[p] = aux;
        info outro = ind[h[i].id];
        ind[h[i].id] = ind[h[p].id];
        ind[h[p].id] = outro;
        i = p;
        p = ((i - 1)/2);
    }
}
void heapify(soldier h[], int index, int criterio, info ind[], int final){
    int r = 2*index + 2;
    int l = 2*index + 1;
    int m = index;
    if(l < final && compare(h[l], h[m], criterio)){
        m = l;
    }
    if(r < final && compare(h[r], h[m], criterio)){
        m = r;
    }
    if(m != index){
        info outro = ind[h[m].id];
        ind[h[m].id] = ind[h[index].id];
        ind[h[index].id] = outro;
        soldier aux = h[m];
        h[m] = h[index];
        h[index] = aux;
        heapify(h, m, criterio, ind, final);
    }
}
void heap_extracti(soldier h[], int criterio, info ind[], int index, int final){
    info outro = ind[h[index].id];
    ind[h[index].id] = ind[h[final].id];
    ind[h[final].id] = outro;
    soldier aux = h[index];
    h[index] = h[final];
    h[final] = aux;
    heapify(h, index, criterio, ind, final);
}
void build_heap(soldier h[], int size, int criterio, info ind[]){
    int i;
    for(i = (size/2) - 1; i>=0; i--){
        heapify(h, i, criterio, ind, size);
    }
}
int main(int argc, char *argv[]) {
    info indices[1000000];
    int squads;
    soldier soldado;
    scanf("%i", &squads);
    int qtd_squads;
    squad esquadroes[squads];
    int b;
    int logic[squads], i, j;
    for(i=0; i<squads; i++){
        logic[i] = 0;
        scanf("%i %i", &qtd_squads, &b);
        esquadroes[i].priority = b;
        for(j=0; j<qtd_squads; j++){
            scanf("%i %i %i", &soldado.id, &soldado.service_time, &soldado.rank);
            printf("%i %i %i\n", soldado.id, soldado.service_time, soldado.rank);
            return 0;
            esquadroes[i].soldiers[logic[i]] = soldado;
            logic[i]++;
            indices[esquadroes[i].soldiers[j].id].index = j;
            indices[esquadroes[i].soldiers[j].id].squad = i;
        }
        build_heap(esquadroes[i].soldiers, logic[i], esquadroes[i].priority, indices);
    }
    printf("a");
    return 0;
    char funcao[10];
    while(strcmp(funcao, "END") != 0){
        scanf(" %s", funcao);
        if(strcmp(funcao, "END") != 0){
            if(strcmp(funcao, "ADD") == 0){
                int esq;
                scanf("%i %i %i %i", &esq, &soldado.id, &soldado.service_time, &soldado.rank);
                indices[soldado.id].index = logic[esq];
                indices[soldado.id].squad = esq;
                esquadroes[esq].soldiers[logic[esq]] = soldado;
                logic[esq]++;
                bubble_up(esquadroes[esq].soldiers, logic[esq] - 1, esquadroes[esq].priority, indices);
                printf("%i %i %i\n", esquadroes[esq].soldiers[0].id, esquadroes[esq].soldiers[0].service_time, esquadroes[esq].soldiers[0].rank);
            }
            else if(strcmp(funcao, "UPD") == 0){
                int id;
                int ts;
                int r;
                scanf("%i %i %i", &id, &ts, &r);
                int index = indices[id].index;
                int s = indices[id].squad;
                esquadroes[s].soldiers[index].service_time = ts;
                esquadroes[s].soldiers[index].rank = r;
                int p = ((index - 1)/2);
                if(compare(esquadroes[s].soldiers[index], esquadroes[s].soldiers[p], esquadroes[s].priority)){
                    bubble_up(esquadroes[s].soldiers, index, esquadroes[s].priority, indices);
                }
                else{
                    heapify(esquadroes[s].soldiers, index, esquadroes[s].priority, indices, logic[s]);
                }
                printf("%i %i %i\n", esquadroes[s].soldiers[0].id, esquadroes[s].soldiers[0].service_time, esquadroes[s].soldiers[0].rank);
            }
            else if(strcmp(funcao, "MOV") == 0){
                int squadi, squadj;
                scanf("%i %i", &squadi, &squadj);
                info antes, depois;
                int transferido = esquadroes[squadi].soldiers[0].id;
                antes = indices[transferido];
                indices[transferido].index = logic[squadj];
                indices[transferido].squad = squadj;
                esquadroes[squadj].soldiers[logic[squadj]] = esquadroes[squadi].soldiers[0];
                logic[squadj]++;
                bubble_up(esquadroes[squadj].soldiers, logic[squadj] - 1, esquadroes[squadj].priority, indices);
                depois = indices[transferido];
                indices[transferido] = antes;
                logic[squadi]--;
                heap_extracti(esquadroes[squadi].soldiers, esquadroes[squadi].priority, indices, 0, logic[squadi]);
                indices[transferido] = depois;
                if(logic[squadi] != 0){
                    printf("%i %i %i", esquadroes[squadi].soldiers[0].id, esquadroes[squadi].soldiers[0].service_time, esquadroes[squadi].soldiers[0].rank);
                }
                else{
                    printf("-1 -1 -1");
                }
                if(logic[squadj] != 0){
                    printf(" %i %i %i\n", esquadroes[squadj].soldiers[0].id, esquadroes[squadj].soldiers[0].service_time, esquadroes[squadj].soldiers[0].rank);
                }
                else{
                    printf(" -1 -1 -1\n");
                }
            }
            else if(strcmp(funcao, "CHG") == 0){
                int squadi, squadj;
                int qtd;
                int novo_criterio, i;
                scanf("%i %i %i %i", &squadi, &squadj, &qtd, &novo_criterio);
                for(i=0; i<qtd; i++){
                    info antes, depois;
                    int transferido = esquadroes[squadi].soldiers[0].id;
                    antes = indices[transferido];
                    indices[transferido].index = logic[squadj];
                    indices[transferido].squad = squadj;
                    esquadroes[squadj].soldiers[logic[squadj]] = esquadroes[squadi].soldiers[0];
                    logic[squadj]++;
                    bubble_up(esquadroes[squadj].soldiers, logic[squadj] - 1, esquadroes[squadj].priority, indices);
                    depois = indices[transferido];
                    indices[transferido] = antes;
                    logic[squadi]--;
                    heap_extracti(esquadroes[squadi].soldiers, esquadroes[squadi].priority, indices, 0, logic[squadi]);
                    indices[transferido] = depois;
                }
                esquadroes[squadi].priority = novo_criterio;
                build_heap(esquadroes[squadi].soldiers, logic[squadi], novo_criterio, indices);
                if(logic[squadi] != 0){
                    printf("%i %i %i", esquadroes[squadi].soldiers[0].id, esquadroes[squadi].soldiers[0].service_time, esquadroes[squadi].soldiers[0].rank);
                }
                else{
                    printf("-1 -1 -1");
                }
                if(logic[squadj] != 0){
                    printf(" %i %i %i\n", esquadroes[squadj].soldiers[0].id, esquadroes[squadj].soldiers[0].service_time, esquadroes[squadj].soldiers[0].rank);
                }
                else{
                    printf(" -1 -1 -1\n");
                }
            }
            else if(funcao == "KIA"){
                int id;
                scanf("%i", &id);
                int s = indices[id].squad;
                int index = indices[id].index;
                logic[s]--;
                heap_extracti(esquadroes[s].soldiers, esquadroes[s].priority, indices, index, logic[s]);
                bubble_up(esquadroes[s].soldiers, index, esquadroes[s].priority, indices);
                if(logic[s] != 0){
                    printf("%i %i %i\n", esquadroes[s].soldiers[0].id, esquadroes[s].soldiers[0].service_time, esquadroes[s].soldiers[0].rank);
                }
                else{
                    printf("-1 -1 -1\n");
                }
            }
        }
    }
    return 0;
}
