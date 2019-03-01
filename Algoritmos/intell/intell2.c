#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct node{
    int val;
    struct node* next;0
}node;
node* list_insert(node* cur, int valor){
    node* novo = malloc(sizeof(node));
    novo->val = valor;
    novo->next = cur->next;
    cur->next = novo;
    return cur;
}
node* list_delete(node *cur){
    node* p = malloc(sizeof(node));
    p = cur -> next;
    cur -> next = p -> next;
    free(p);
    return cur;
}
node* enqueue(node *head, node *tail, int valor){
    node *t = malloc(sizeof(node));
    t = list_insert(tail, valor);
    return t->next;
}
node* dequeue(node *head, node *tail){
    node *h = list_delete(head);
    if(head -> next != NULL){
        return tail;
    }
    else{
        return head;
    }
}
int main(){
    node **head_fila, tail_fila, top_stack;
    int m, i, numero;
    scanf("%i", &m);
    head_fila = (node**)malloc(m*sizeof(node*));
    tail_fila = (node**)malloc(m*sizeof(node*));
    top_stack = (node**)malloc(m*sizeof(node*));
    for(i=0; i<m; i++){
        head_fila[i] = (node*)malloc(sizeof(node));
        tail_fila[i] = (node*)malloc(sizeof(node));
        top_stack[i] = (node*)malloc(sizeof(node));
        head_fila[i]->next = NULL;
        tail_fila[i]->next = NULL;
        top_stack[i]->next = NULL;
    }
    char linha[5];
    while(strcmp(linha, "END") != 0){
        if(strcmp(linha, "END") != 0){
            scanf("%i", &numero);
            if(linha[0] == 'N'){
                tail_fila[0] = enqueue(head_fila[0], tail_fila[0], numero);
                if(head_fila[0]->next == NULL){
                    head_fila[0]->next = tail_fila[0];
                }
            }
            else if(linha[0] == 'M'){
                tail_fila[numero] = enqueue(head_fila[numero], tail_fila[numero], head_fila[0]->next->val);
                if(head_fila[numero]->next == NULL){
                    head_fila[numero]->next = tail_fila[numero];
                }
                tail_fila[0] = dequeue(head_fila[0], tail_fila[0]);
            }
            else if(linha[0] == 'D'){
                top_stack[numero] = list_insert(top_stack[numero], head_fila[numero]->next->val);
                tail_fila[numero] = dequeue(head_fila[numero], tail_fila[numero]);
            }
            else if(linha[0] == 'F'){
                tail_fila[numero] = enqueue(head_fila[numero], tail_fila[numero], top_stack[numero]->next->val);
                top_stack[numero] = list_delete(top_stack[numero]);
            }
            else if(linha[0] == 'T'){
                printf("%i BAD\n", top_stack[numero]->next->val);
                top_stack[numero] = list_delete(top_stack[numero]);
            }
            else if(linha[0] == 'R'){
                printf("%i OK\n", head_fila[numero]->next->val);
                tail_fila[numero] = dequeue(head_fila[numero], tail_fila[numero]);
            }
        }
    }
}