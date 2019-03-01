#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Node{
    int val;
    struct Node* next;
}Node;
Node* list_insert(Node*cur, int valor){
    Node* n = (Node*)malloc(sizeof(Node));
    n -> val = valor;
    n -> next = cur -> next;
    cur -> next = n;
    return cur;
}
Node* list_delete(Node*cur, int variante){
    Node* p = malloc(sizeof(Node));
    p = cur -> next;
    cur -> next = p -> next;
    if(variante == 0){
        printf("%i OK\n", p -> val);
    }
    else if(variante == 1){
        printf("%i BAD\n", p -> val);
    }
    free(p);
    return cur;

}
Node* enqueue(Node* head, Node* tail, int val){
    Node* t = list_insert(tail, val);
    return t -> next;
}
Node* dequeue(Node* head, Node* tail, int variante, int* mudar){
    *mudar = head->next->val;
    head = list_delete(head, variante);
    if(head -> next != NULL){
        return tail;
    }
    else{
        return head;
    }
}
void print(Node* comeco){
    Node* i;
    for(i=comeco; i->next!=NULL; i = i->next){
        printf("%i ", i->next->val);
    }
    puts("");
}
int main()
{
    int m, i, numero, valor_mudar;
    scanf("%i", &m);
    Node** head_fila = (Node**)malloc(m*sizeof(Node*));
    Node** top_stack = (Node**)malloc(m*sizeof(Node*));
    Node** tail_fila = (Node**)malloc(m*sizeof(Node*));
    for(i=0; i<m; i++){
        head_fila[i] = (Node*)malloc(sizeof(Node));
        tail_fila[i] = (Node*)malloc(sizeof(Node));
        top_stack[i] = (Node*)malloc(sizeof(Node));
        head_fila[i] -> next = NULL;
        tail_fila[i] -> next = NULL;
        top_stack[i] -> next = NULL;
    }
    char linha[6];
    while(strcmp(linha, "END") != 0){
        scanf(" %s", linha);
        if(strcmp(linha, "END") != 0){
            scanf("%i", &numero);
            if(linha[0] == 'N'){
                tail_fila[0] = enqueue(head_fila[0], tail_fila[0], numero);
                if(head_fila[0]->next == NULL){
                    head_fila[0]-> next = tail_fila[0];
                }
            }
            else if(linha[0] == 'M'){
                tail_fila[0] = dequeue(head_fila[0], tail_fila[0], 2, &valor_mudar);
                tail_fila[numero] = enqueue(head_fila[numero], tail_fila[numero], valor_mudar);
                if(head_fila[numero]->next == NULL){
                    head_fila[numero]-> next = tail_fila[numero];
                }
            }
            else if(linha[0] == 'D'){
                tail_fila[numero] = dequeue(head_fila[numero], tail_fila[numero], 2, &valor_mudar);
                top_stack[numero] = list_insert(top_stack[numero], valor_mudar);
            }
            else if(linha[0] == 'F'){
                tail_fila[numero] = enqueue(head_fila[numero], tail_fila[numero], top_stack[numero]->next->val);
                top_stack[numero] = list_delete(top_stack[numero], 2);

                if(head_fila[numero]->next == NULL){
                    head_fila[numero]-> next = tail_fila[numero];
                }
            }
            else if(linha[0] == 'T'){
                top_stack[numero] = list_delete(top_stack[numero], 1);
            }
            else if(linha[0] == 'R'){
                tail_fila[numero] = dequeue(head_fila[numero], tail_fila[numero], 0, &valor_mudar);
            }
        }
    }
    return 0;
}
