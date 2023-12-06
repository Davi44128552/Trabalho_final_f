#include <stdio.h>
#include <stdlib.h>
# include <string.h>
#include "escalonador.h"

int main() {
    Escalonador e;
    char nome_arq_in[] = "entrada-0001.txt";
    char nome_arq_out[] = "saida-0001.txt";

    // Inicializa o escalonador com os valores do arquivo de configuração
    if (!e_conf_por_arquivo(&e, nome_arq_in)) {
        fprintf(stderr, "Erro ao abrir o arquivo de configuração.\n");
        return EXIT_FAILURE;
    }

    // Executa o escalonador e gera o arquivo de saída
    e_rodar(&e, nome_arq_in, nome_arq_out);

    printf("Simulação concluída com sucesso. Resultados gravados em %s\n", nome_arq_out);

    return EXIT_SUCCESS;
}
