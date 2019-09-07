#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#define TAMANHO_VALORES_ALEATORIOS 10
#define MAX_VALOR_ALEATORIO 1000

typedef struct no {
    int valor;
    struct no* prox;
} No;

typedef struct {
    No* inicio;
} Lista;

void imprime(Lista* l) {

    printf("\nLISTA ->");

    No* n = (*l).inicio;

    while (n != NULL) {
        printf(" %i ->", (*n).valor);
        n = (*n).prox;
    }

    printf(" NULL\n");
}

bool insereFim(Lista* l, int valor) {

    No* n = malloc(sizeof(No));
    (*n).valor = valor;
    (*n).prox = NULL;

    if ((*l).inicio == NULL) { //se a lista estiver vazia
        (*l).inicio = n; //a lista deve apontar como inicio o elemento atual (n)
    }
    else {
        //senão, encontra o elemento anterior (n_ant)
        No* n_ant = (*l).inicio;
        while ((*n_ant).prox != NULL) {
            n_ant = (*n_ant).prox;
        }
        //atribui ao prox do elemento anterior o elemento atual (n)
        (*n_ant).prox = n;
    }
    int s = (*n).valor; //pega o valor de n
    printf("\nElemento %i inserido no fim da lista\n", s);
    return(true);
}

bool inserePos(Lista* l, int pos, int valor) {

    //verifica se a posição é negativa
    if (pos < 0) {
    printf("Nenhum elemento inserido pois a posição informada é negativa!\n");
        return(false);
    }

    //aloca o novo nó - OBS: se a posição informada > última posição + 1, o elemento é inserido na última posição
    No* n = malloc(sizeof(No));
    (*n).valor = valor; //passa o valor para o nó

    if (pos == 0) { //se for inserido na primeira posição
        (*n).prox = (*l).inicio; //o prox do elemento inserido é o antigo primeiro elemento
        (*l).inicio = n; //o inicio da lista é o elemento inserido
        int s = (*n).valor; //pega o valor de n
        printf("\nElemento %i inserido\n", s);
        return(true);
    }
    //se não for a primeira posição da lista

    No* n_ant = (*l).inicio; //pega o primeiro nó da lista

    int i = 0;
    int pos_ant = pos-1; //queremos achar anterior da posição 'pos', por isso subtraímos 1

    //loop para encontrar o elemento anterior à posição que queremos (n_ant)
    while ((i<pos_ant) && ((*n_ant).prox!=NULL)) {
        n_ant = (*n_ant).prox;
        ++i;
    }

    //acerta os ponteiros na lista
    (*n).prox = (*n_ant).prox; //popula o prox do novo elemento
    (*n_ant).prox = n; //atualiza o prox do elemento anterior

    int s = (*n).valor; //pega o valor de n
    printf("\nElemento %i inserido\n", s);
    return(true);
}

bool removeFim(Lista* l) {

    //pega o primeiro nó da lista
    No* n = (*l).inicio;

    //verifica se a lista está vazia
    if (n == NULL) {
        printf("Nenhum elemento removido pois a lista está vazia!\n");
        return(false);
    }
    //se a lista tiver elementos
    if ((*n).prox == NULL){ //tratamento caso seja o primeiro elemento da lista
        (*l).inicio = (*n).prox;
    }
    else { //se o elemento não for o primeiro da lista

        No* n_ant;

        //loop para encontrar o elemento a ser removido (n) e o seu anterior (n_ant)
        while ((*n).prox != NULL) {
            n_ant = n;
            n = (*n).prox;
        }
        //atualiza o prox do elemento anterior
        (*n_ant).prox = (*n).prox;
    }
    int r = (*n).valor; //pega o valor de n
    free(n); //libera a memória de n
    printf("\nElemento %i removido\n", r);
    return(true);
}

bool removePos(Lista* l, int pos) {

    //verifica se a posição é negativa
    if (pos < 0) {
    printf("Nenhum elemento removido pois a posição informada é negativa!\n");
        return(false);
    }

    //pega o primeiro nó da lista
    No* n = (*l).inicio;

    //verifica se a lista está vazia
    if (n == NULL) {
        printf("Nenhum elemento removido pois a lista está vazia!\n");
        return(false);
    }
    //se a lista tiver elementos
    if (pos == 0){ //tratamento caso seja o primeiro elemento da lista
        (*l).inicio = (*n).prox;
    }
    else { //se o elemento não for o primeiro da lista

        No* n_ant;

        int i = 0;
        //loop para encontrar o elemento a ser removido (n) e o seu anterior (n_ant)
        do {
            n_ant = n;
            n = (*n).prox;
            ++i;

        } while ((i<pos) && (n!=NULL));

        if (n==NULL) { //'pos' é maior que a posição do último elemento
            printf("Nenhum elemento removido. A posição informada é maior que a posição do último elemento\n");
            return(false); //não exclui nada e retorna
        }
        //atualiza o prox do elemento anterior
        (*n_ant).prox = (*n).prox;
    }
    int r = (*n).valor; //pega o valor de n
    free(n); //libera a memória de n
    printf("\nElemento %i removido\n", r);
    return(true);
}

void insereValAleatorios(Lista* l){

    int i;
    for (i=0; i<TAMANHO_VALORES_ALEATORIOS; i++) {
        insereFim(l, rand()%MAX_VALOR_ALEATORIO);
    }
}

void imprimeComandos() {
    printf(
        "LISTA LIGADA DE EXEMPLO EM C\n"
        "\n--------------------\n"
        "COMANDOS:\n"
        "i\t-\tInserir valor no fim da lista\n"
        "r\t-\tRemover valor no fim da lista\n"
        "p\t-\tInserir %i valores aleatórios de 0 a %i\n"
        "l\t-\tImprimir lista\n"
        "lista\t-\tImprimir lista em tela limpa\n"
        "\nipos\t-\tInserir valor em uma posição específica\n"
        "rpos\t-\tRemover valor em uma posição específica\n"
        "\nq\t-\tSair\n"
        "\nclear\t-\tLimpar a tela\n"
        "help\t-\tEste menu de ajuda\n\n",
        TAMANHO_VALORES_ALEATORIOS, MAX_VALOR_ALEATORIO-1);
}

void lacoComandos(Lista* l) { //método do laço de comandos principal

    char comando[10];
    //Laço dos comandos
    while ((strcmp (comando, "sair") != 0) && (strcmp (comando, "exit") != 0) && (strcmp (comando, "q") != 0)){

        printf("\ncomando: ");
        scanf("%s", comando);

        if (strcmp (comando, "help") == 0) {
            system("clear");
            imprimeComandos();
        }
        if (strcmp (comando, "i") == 0) {
            printf("Digite um número inteiro: ");
            int valor;
            scanf("%i", &valor);
            bool i = insereFim(l, valor);
        }
        if (strcmp (comando, "r") == 0) {
            printf("Confirma exclusão do último elemento? [1 confirma] [-1 cancela]: ");
            int pos;
            scanf("%i", &pos);
            if (pos != -1) {
                removeFim(l);
            }
            else {
                printf("\nRemoção cancelada...\n");
            }
        }
        if (strcmp (comando, "p") == 0) {
           insereValAleatorios(l);
        }
        if (strcmp (comando, "l") == 0) {
            imprime(l);
        }
        if (strcmp (comando, "lista") == 0) {
            system("clear");
            imprime(l);
            printf("\n\nDigite v para voltar: ");
            scanf("%s", comando);
            system("clear");
            imprimeComandos();
        }
        if (strcmp (comando, "ipos") == 0) {
            printf("Digite a posição para inserir (inicia no 0) [-1 cancela]: ");
            int pos;
            scanf("%i", &pos);
            if (pos != -1) {
                printf("\nDigite um número inteiro: ");
                int valor;
                scanf("%i", &valor);
                inserePos(l, pos, valor);
            }
            else {
                printf("\nInserção cancelada...\n");
            }
        }
        if (strcmp (comando, "rpos") == 0) {
            printf("Digite a posição do elemento (inicia no 0) [-1 cancela]: ");
            int pos;
            scanf("%i", &pos);
            if (pos != -1) {
                removePos(l, pos);
            }
            else {
                printf("\nRemoção cancelada...\n");
            }
        }
        if (strcmp (comando, "clear") == 0) {
            system("clear");
        }
    }
}

void main() {

    Lista* l;
    l = malloc(sizeof(Lista));
    (*l).inicio = NULL;

    imprimeComandos();
    
    char confirmaSaida[10] = "N"; //comando para confirmar saída do programa
    while ((strcmp (confirmaSaida, "S") != 0) && (strcmp (confirmaSaida, "s") != 0)) { //laço para confirmar saída do programa (enquanto confirmaSaida != "S" e "s", continua no programa)
    
        lacoComandos(l); //laço de comandos principal
            
        printf("Confirma saída do programa? [S para SIM] [N para NÃO]: \n");
        scanf("%s", confirmaSaida);
    }
    printf("Saindo do programa...\n");
}
