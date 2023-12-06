# include <stdio.h>
# include <stdlib.h>
# include "arvorebb.h"

Log* CriarNo(int conta, int classe, int timer, int caixa) {
    Log *novoNo = (Log*) malloc(sizeof(Log));
    if(novoNo == NULL){
        return NULL;
    }

    novoNo->conta = conta;
    novoNo->classe = classe;
    novoNo->timer = timer;
    novoNo->caixa = caixa;
    novoNo->esq = NULL;
    novoNo->dir = NULL;

    return novoNo;
}
void log_inicializar(Log **l) {
    *l = NULL;
}

void log_registrar(Log** l, int conta, int classe, int timer, int caixa){
    Log *atual = *l;
    Log *ant; /*anterior*/
    Log *novoNo = CriarNo(conta, classe, timer, caixa);
    if (novoNo == NULL) {
        return;
    }

    if (*l == NULL) {
        *l = novoNo;
        
    } 
    else {
        while (atual != NULL) {
            ant = atual; /* Precisamos do anterior para fazer a atribuição do novoNo à árvore*/
            if (conta < atual->conta) 
                atual = atual->esq;
            
            else 
                if (conta > atual->conta) 
                atual = atual->dir;
            
            else 
                return;
            
        }
        if (conta < ant->conta) 
            ant->esq = novoNo;
        else 
            ant->dir = novoNo;
        
    }
}


float log_media_por_classe(Log **l,int classe){
	float tempo,clientes;
	tempo = log_obter_soma_por_classe(l,classe);
	clientes =  log_obter_contagem_por_classe(l,classe);
	return tempo/clientes;
}


int log_obter_soma_por_classe(Log **l,int classe){
	if(*l == NULL)
		return 0;
	if((*l)->classe == classe){
		return (*l)->timer + log_obter_soma_por_classe(&(*l)->esq, classe) + log_obter_soma_por_classe(&(*l)->dir,classe);
	}
	else{
		return	log_obter_soma_por_classe(&(*l)->esq, classe) + log_obter_soma_por_classe(&(*l)->dir,classe);
	
	}	
}



int log_obter_contagem_por_classe(Log **l, int classe) {
    if(*l == NULL){
        return 0;
    }    

    if((*l)->classe == classe){
        return  log_obter_contagem_por_classe(&(*l)->esq, classe) + log_obter_contagem_por_classe(&(*l)->dir, classe) + 1;
    } 
    else{
        return log_obter_contagem_por_classe(&(*l)->esq, classe) + log_obter_contagem_por_classe(&(*l)->dir, classe);
    } 
} 



