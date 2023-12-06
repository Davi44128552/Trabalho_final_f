# include <stdio.h>
# include <stdlib.h>

/* Criação da estrutura do nó para a fila */
typedef struct _No{

    int chave;
    int valor;
    struct _No* proximo;

} No;

typedef struct _Fila{

    struct _No* inicio;
    struct _No* fim;

} Fila_FIFO;

/* Declaração das funções */
void f_inicializar(Fila_FIFO **f);
int f_inserir(Fila_FIFO **f, int chave, int valor);
int f_obter_proxima_chave(Fila_FIFO **f);
int f_consultar_proxima_chave(Fila_FIFO **f);
int f_consultar_proximo_valor(Fila_FIFO **f);
int f_num_elementos(Fila_FIFO **f);
int f_consultar_chave_por_posicao(Fila_FIFO **f, int posicao);
int f_consulta_valor_por_posicao(Fila_FIFO **f, int posicao);


