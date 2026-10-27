#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include "header.h"

int main()
{
    srand(time(NULL));

    int acao_para;
    int acao_inst;
    int n = 0;

    printf("\tAvaliacao Pratica 03\n");
    printf("\tSelecione o que deseja executar.\n");
    printf("1 - Programacao Dinamica\n");
    printf("2 - Guloso\n");
    printf("3 - Comparar algoritmos\n");
    printf("4 - Instancia adversarias.(seleciona qualquer instacia para pular.)\n");
    scanf("%d", &acao_para);

    printf("\nSelecione a instancia.\n");
    printf("1 - 100\n");
    printf("2 - 500\n");
    printf("3 - 1000\n");
    printf("4 - 2000\n");
    printf("5 - 5000\n");
    scanf("%d", &acao_inst);

    switch (acao_inst)
    {
        case 1:
            n = 100;
            break;

        case 2:
            n = 500;
            break;

        case 3:
            n = 1000;
            break;

        case 4:
            n = 2000;
            break;

        case 5:
            n = 5000;
            break;

        default:
            printf("Instancia invalida.\n");
            return 0;
    }

    switch (acao_para)
    {
        case 1:
            executarInstanciasPD(n);
            break;

        case 2:
            executarInstanciasGuloso(n);
            break;

        case 3:
            compararAlgoritmos(n);
            break;
        case 4:
            executarInstanciasAdversariais();
            break;

        default:
            printf("Opcao invalida.\n");
            break;
    }

    return 0;
}