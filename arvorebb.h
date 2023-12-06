# include <stdio.h>
# include <stdlib.h>

/*Criação da estrutura da árvore */
typedef struct _Log {
    int conta;
    int classe;
    int timer;
    int caixa;
    struct _Log *esq;
    struct _Log *dir;
}Log;

/*Declaração das funções*/
void log_inicializar(Log **l);
Log* CriarNo(int conta, int classe, int timer, int caixa);
void log_registrar(Log** l, int conta, int classe, int timer, int caixa);
float log_media_por_classe(Log **l,int classe);
int log_obter_soma_por_classe(Log **l, int classe);
int log_obter_contagem_por_classe(Log **l, int classe);

