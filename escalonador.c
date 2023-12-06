#include "escalonador.h"


void e_inicializar (Escalonador *e, int caixas, int delta_t, int n_1, int n_2, int n_3, int n_4, int n_5) {
    int i;
	/* Inicializando as filas*/
    f_inicializar(&e->Premium);
    f_inicializar(&e->Ouro);
    f_inicializar(&e->Prata);
	f_inicializar(&e->Bronze);
	f_inicializar(&e->Leezu);
	
    e->caixas = caixas;
    e->tempo_Ope = delta_t;

    /*disciplina de atendimento*/
    e->disciplina[0] = n_1;
    e->disciplina[1] = n_2;
    e->disciplina[2] = n_3;
    e->disciplina[3] = n_4;
    e->disciplina[4] = n_5;
    
    e->cliente_classe = 1;/*Classe atual é Premium*/
    
    for(i= 0; i<5;i++)
    	e->disciplina_cont[i] = 0;
}

int e_inserir_por_fila (Escalonador *e, int classe, int num_conta, int qtde_operacoes){
    Fila_FIFO* filas[] = {e->Premium, e->Ouro, e->Prata, e->Bronze, e->Leezu};
    f_inserir(&(filas[classe-1]), num_conta, qtde_operacoes);
}

int e_obter_prox_num_conta(Escalonador *e){
    int conta;
    int classe;
    
    classe = e->cliente_classe;
    
    if(classe == 1) 
        conta = f_obter_proxima_chave(&e->Premium);
    else 
		if(classe == 2) 
        	conta = f_obter_proxima_chave(&e->Ouro);
    else 
		if(classe == 3) 
        	conta = f_obter_proxima_chave(&e->Prata);
    else 
		if(classe == 4) 
        	conta = f_obter_proxima_chave(&e->Bronze);
    else 
		if(classe == 5) 
        conta = f_obter_proxima_chave(&e->Leezu);
    
    
    /* Incrementa o contador que esta dentro de um vetor por meio do ponteiro*/
    e->disciplina_cont[classe - 1]++;
    
    /* Se o número de atendimentos da classe atual for igual ao valor na disciplina correspondente, avança para a próxima classe*/
    if(e->disciplina_cont[classe - 1] == e->disciplina[classe - 1]) {
        classe = e_consultar_prox_fila(e); 
        e->cliente_classe = classe;
        
        /* Reseta o contador da classe atendida*/
        e->disciplina_cont[classe - 1] = 0;
    }
    
    return conta;
}

int e_consultar_prox_num_conta (Escalonador *e){
    int classe, conta;
    Fila_FIFO* filas[] = {e->Premium, e->Ouro, e->Prata, e->Bronze, e->Leezu};
    classe = e->cliente_classe;
    while(classe != 0){
        conta = f_consultar_proxima_chave(&(filas[classe - 1]));
        if(conta == -1)
            classe = e_consultar_prox_fila(e);
        
		else 
            return conta;
        
    }
    return 0;
}
int e_consultar_prox_qtde_oper (Escalonador *e){
    int classe,operacoes;
    Fila_FIFO* filas[] = {e->Premium, e->Ouro, e->Prata, e->Bronze, e->Leezu};
    classe = e->cliente_classe;
    
    while (classe != 0){
        operacoes = f_consultar_proximo_valor(&(filas[classe - 1]));
        if (operacoes == -1){
            classe = e_consultar_prox_fila(e);
        } else {
            return operacoes;
        }
    }
    return 0;
}

int e_consultar_prox_fila (Escalonador *e){
    if(e->Premium != NULL)
        return 1;
    else if(e->Ouro != NULL)
        return 2;
    else if(e->Prata != NULL)
        return 3;
    else if(e->Bronze != NULL)
        return 4;
    else if(e->Leezu != NULL)
        return 5;
    else 
        return 0;
}


int e_consultar_qtde_clientes (Escalonador *e){
    int contador = 0;
    int i;
    Fila_FIFO* filas[] = {e->Premium, e->Ouro, e->Prata, e->Bronze, e->Leezu};

    for(i = 0; i < 5; i++) 
        contador = f_num_elementos(&(filas[i])) + contador;
    
    return contador;
}

int e_consultar_tempo_prox_cliente (Escalonador *e){
    int consultar,operacoes;
    Fila_FIFO* filas[] = {e->Premium, e->Ouro, e->Prata, e->Bronze, e->Leezu};

    consultar = e_consultar_prox_num_conta(e);
    if(consultar == 0) 
        return -1;
    

    operacoes = e_consultar_prox_qtde_oper(e);
    
    return e->tempo_Ope * operacoes;
}

int e_conf_por_arquivo (Escalonador *e, char *nome_arq_conf){
    FILE* arquivo_entrada;
    int QtdeCaixas, DTempo, N_1, N_2, N_3, N_4, N_5;
    char classe[10];
    int conta, operacao;
    Fila_FIFO* filas[] = {e->Premium, e->Ouro, e->Prata, e->Bronze, e->Leezu};
    int classe_cont;
    arquivo_entrada = fopen(nome_arq_conf, "r");
	char* classes[] = {"Premium", "Ouro", "Prata", "Bronze", "Leezu"};
	
    //Se estiver vazio.
    if(arquivo_entrada == NULL){
        return 0;
    }
    //Recolhe as informações iniciais.
    fscanf(arquivo_entrada,"qtde de caixas = %d\n", &QtdeCaixas);
    fscanf(arquivo_entrada,"delta t = %d\n", &DTempo);
    fscanf(arquivo_entrada,"disciplina de escalonamento = {%d,%d,%d,%d,%d}\n", &N_1, &N_2, &N_3, &N_4, &N_5);

    //Inicializa o escalonador.
    e_inicializar(e, QtdeCaixas, DTempo, N_1, N_2, N_3, N_4, N_5);

    //Coleta de informacoes gerais do cliente.
    while((fscanf(arquivo_entrada,"%s - conta %d - %d operacao(oes)", classe, &conta, &operacao) != EOF)){
        if(strcmp(classe, "Premium") == 0){
            classe_cont = 0;
        }else if(strcmp(classe, "Ouro") == 0){
            classe_cont = 1;
        }else if(strcmp(classe, "Prata") == 0){
            classe_cont = 2;
        }else if(strcmp(classe, "Bronze") == 0){
            classe_cont = 3;
        }else if(strcmp(classe, "Leezu") == 0){
            classe_cont = 4;
        }
        e_inserir_por_fila(e, classe_cont + 1, conta, operacao);
    }
    //Finaliza e fecha o arquivo.
    fclose(arquivo_entrada);
    return 1;
}


void e_rodar(Escalonador *e, char *nome_arq_in, char *nome_arq_out){
    Log *l;
    FILE *arquivo_saida;
    int timer = 0, caixa[10], contador, qtde_operacoes, conta, classe, verificador, caixaAtual, maior = 0, operacao[5], caixaValor[10],i;
    float qtde_clientes, qtde_operacoes_por_classe, tempoMedio, qtde_Media;
    Fila_FIFO* filas[] = {e->Premium, e->Ouro, e->Prata, e->Bronze, e->Leezu};
    char* classes[] = {"Premium", "Ouro", "Prata", "Bronze", "Leezu"}; // Adicionado declaração

    if(e_conf_por_arquivo(e, nome_arq_in) == 0) {
        printf("Erro ao abrir o arquivo de configuração.\n");
        return;
    }
    arquivo_saida = fopen(nome_arq_out, "w");
    if(arquivo_saida == NULL) {
        printf("Erro ao abrir o arquivo de saída.\n");
        return; 
    }

    /*Inicia o l.*/
    log_inicializar(&l);
    
    /*Inicia o verificador para ver se possui algum cliente nas filas.*/
    verificador = e_consultar_prox_num_conta(e);
    
    /*Inicializa os caixas e seus contadores.*/
    for(contador = 0; contador < e->caixas; contador++){
        caixa[contador] = 1;
        caixaValor[contador] = 0;
    }
    
    /*Inicializa os contadores de operações por classe.*/
    for(contador = 0; contador < 5; contador++){
        operacao[contador] = 0;
    }

    /*Verifica cada caixa e modifica seu timer.*/
    while(verificador != 0) {
        for(contador = 0; contador < e->caixas; contador++){
            caixa[contador] = caixa[contador] - 1;
            if(caixa[contador] == 0){
                classe = e->cliente_classe;
                qtde_operacoes = e_consultar_prox_qtde_oper(e);
                conta = e_obter_prox_num_conta(e);
                if(conta == -1){
                    conta = e_obter_prox_num_conta(e);
                    classe = e->cliente_classe;
                }
                if(conta != -1 && conta != 0){
                    operacao[classe-1] = operacao[classe-1] + qtde_operacoes;
                    caixaAtual = contador + 1;
                    log_registrar(&l, conta, classe, timer, caixaAtual);
                    fprintf(arquivo_saida, "T = %d min: Caixa %d chama da categoria %s cliente da conta %d para realizar %d operacao(oes).\n", timer, caixaAtual, classes[classe-1], conta, qtde_operacoes);
                    caixa[contador] = qtde_operacoes*e->tempo_Ope;
                    caixaValor[contador] = caixaValor[contador] + 1;
                }
            }
            verificador = e_consultar_prox_num_conta(e);
        }
        timer++;
    }
    
    /* Conserta o timer que andou mais um.*/
    timer--;

    /*Pega o tempo do ultimo clinte que sairá do caixa.*/
    for(contador = 0; contador < e->caixas; contador++){
        if (maior < caixa[contador])
            maior = caixa[contador];
    }

    timer = timer + maior;
    
    fprintf(arquivo_saida, "Tempo total de atendimento: %d minutos.\n", timer);

    /*Tempos medios de atendimento no arquivo.*/
    for(i = 0; i < 5; i++) {
        qtde_clientes = log_obter_contagem_por_classe(&l, i + 1);
        tempoMedio = log_media_por_classe(&l, i + 1);
        fprintf(arquivo_saida,"Tempo medio de espera dos %.0f clientes %s: %.2f\n", qtde_clientes, classes[i], tempoMedio);
    }

    /*Quantidades medias de operaçoes por classe.*/
    for(contador = 0; contador < 5; contador++){
        qtde_operacoes_por_classe = operacao[contador];
        qtde_clientes = log_obter_contagem_por_classe(&l, contador + 1);
        qtde_Media = qtde_operacoes_por_classe/qtde_clientes;
        fprintf(arquivo_saida,"Quantidade media de operacoes por cliente da classe %d = %.2f\n", contador + 1, qtde_Media);
    }

    /*Quantidade de clientes por caixa.*/
    for(contador = 0; contador < e->caixas; contador++){
        fprintf(arquivo_saida,"O caixa de número %d atendeu %d clientes.\n", contador+1, caixaValor[contador]);
    }
}





