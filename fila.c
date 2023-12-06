# include <stdio.h>
# include <stdlib.h>
# include "fila.h"

/* Criação da função da inicialização da fila*/
void f_inicializar(Fila_FIFO **f){
    /* Alocando um espaço na memória e verificando se a alocação foi bem-sucedida */
    *f = (Fila_FIFO*)malloc(sizeof(Fila_FIFO));

    if (*f == NULL){
        exit(EXIT_FAILURE);
    }

    /* Adição das variáveis da fila */
    (*f) -> inicio = NULL;
    (*f) -> fim = NULL;


}

/* Criação da função de inserção */
int f_inserir(Fila_FIFO **f, int chave, int valor){
    /* Alocando o novo nó e verificando se a alocação foi bem-sucedida */
    No *novoNo = (No*)malloc(sizeof(No));

    if (novoNo == NULL){
        return 0;
    }

    /* Preenchendo o no */
    novoNo -> chave = chave;
    novoNo -> valor = valor;
    novoNo -> proximo = NULL;

    /* Verificando se a fila está vazia */
    if ((*f) -> inicio == NULL){
        (*f) -> inicio = novoNo;
        (*f) -> fim = novoNo;
    } /* Caso esteja vazia, atribuimos ao inicio e fim o no */

    else{
        (*f) -> fim -> proximo = novoNo;
        (*f) -> fim = novoNo;
    } /* Caso não esteja, adicionamos o nó à fila e definimos como final */

    return 1;

}

/* Criação da função para obter a próxima chave */
int f_obter_proxima_chave(Fila_FIFO **f){

    /* Analisando se a fila está vazia */
    if ((*f) -> inicio == NULL){
        return -1;
    }

    /* Ponteiro para indicar o segundo elemento da fila */
    No *no_prox_primeiro = (*f) -> inicio -> proximo;
    /* Armazenamento da chave */
    int chave_saida = (*f) -> inicio -> chave;

    /* Liberação do primeiro elemento da fila e retorno do valor da chave */
    free((*f) -> inicio);
    (*f) -> inicio = no_prox_primeiro;

    /* Analisando se a fila ficou vazia após a remoção, e consertando, atualizando o ponteiro fim */
    if ((*f) -> inicio == NULL){
        (*f) -> fim = NULL;
    }

    return chave_saida;
    
}

/* Criação da função para consultar a próxima chave */
int f_consultar_proxima_chave(Fila_FIFO **f){

    /* Verificando se a fila está vazia */
    if ((*f) -> inicio == NULL){
        return -1;
    }

    return (*f) -> inicio -> chave;
}

/* Criação da função para consultar o próximo valor */
int f_consultar_proximo_valor(Fila_FIFO **f){

    /* Verificando se a fila está vazia */
    if ((*f) -> inicio == NULL){
        return -1;
    }

    return (*f) -> inicio -> valor;
}

/* Criação da função para retornar o número de elementos da fila */
int f_num_elementos(Fila_FIFO **f){
    /* Criar um ponteiro que apontara para o inicio e uma variável para contar o numero de nós na fila */
    No *no_temporario = (*f) -> inicio;
    int contador = 0;

    /* Percorrendo a fila e contando o numero de nos */
    while (no_temporario != NULL){
        contador += 1;
        no_temporario = no_temporario -> proximo;
    }

    /* Retornando o numero de termos da fila */
    return contador;
}

/* Criação da função para consultar a chave de determinada posição da fila */
int f_consultar_chave_por_posicao(Fila_FIFO **f, int posicao){
    /* Criação da do ponteiro para o no inicial e da variável para percorrer a fila até chegar na posição informada */
    No *no_atual = (*f) -> inicio;
    int posicao_atual = 1;

    /* Percorrendo a fila para encontrar determinada posição, determinada pelo usuário */
    while (posicao_atual < posicao && no_atual -> proximo != NULL){
        no_atual = no_atual -> proximo;
        posicao_atual += 1;
    }

    /* Analisando se a posição dada existe na fila */
    /* Caso não */
    if (posicao_atual < posicao){
        return -1;
    }

    /* Caso sim */
    else{
        return no_atual -> chave;
    }
}

/* Criação da função para a consulta do valor de determinada posição, dada pelo usuário */
int f_consulta_valor_por_posicao(Fila_FIFO **f, int posicao){
    /* Criação do ponteiro para o no inicial e da variável para percorrer a fila até chegar na posição informada */
    No *no_atual = (*f) -> inicio;
    int posicao_atual = 1;

    /* Percorrendo a fila para encontrar determinada posição, determinada pelo usuário */
    while (posicao_atual < posicao && no_atual -> proximo != NULL){
        no_atual = no_atual -> proximo;
        posicao_atual += 1;
    }

    /* Analisando se a posição dada existe na fila */
    /* Caso não */
    if (posicao_atual < posicao){
        return -1;
    }

    /* Caso sim */
    else{
        return no_atual -> valor;
    }

}
