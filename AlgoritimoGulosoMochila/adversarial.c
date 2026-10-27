#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include "header.h"

#include <stdio.h>
#include "header.h"

void executarInstanciasAdversariais()
{
    instanciaAdversarial1();

    printf("\n\n");

    instanciaAdversarial2();
}


void instanciaAdversarial1()
{
    item itens[3];

    itens[0].peso = 10;
    itens[0].valor = 80;
    itens[0].razao = (float)itens[0].valor / itens[0].peso;

    itens[1].peso = 5;
    itens[1].valor = 39;
    itens[1].razao = (float)itens[1].valor / itens[1].peso;

    itens[2].peso = 6;
    itens[2].valor = 45;
    itens[2].razao = (float)itens[2].valor / itens[2].peso;

    int capacidade = 11;

    int resultadoPD = mochilaPD(itens, 3, capacidade);
    int resultadoGuloso = mochilaGulosa(itens, 3, capacidade);

    printf("=====================================\n");
    printf("INSTANCIA ADVERSARIAL 1\n");
    printf("=====================================\n");

    printf("Capacidade da mochila: %d\n\n", capacidade);

    printf("Itens:\n");
    printf("Item 1. Peso: %d - Valor: %d\n", itens[0].peso, itens[0].valor);
    printf("Item 2. Peso: %d - Valor: %d\n", itens[1].peso, itens[1].valor);
    printf("Item 3. Peso: %d - Valor: %d\n\n", itens[2].peso, itens[2].valor);

    printf("Programacao Dinamica: %d\n", resultadoPD);
    printf("Algoritmo Guloso: %d\n", resultadoGuloso);

    printf("Qualidade da heuristica: %.2f\n",
           ((double)resultadoGuloso / resultadoPD) * 100.0);

   
}


void instanciaAdversarial2()
{
    item itens[4];

    itens[0].peso = 2;
    itens[0].valor = 4;
    itens[0].razao = (float)itens[0].valor / itens[0].peso; /* 2*/

    itens[1].peso = 1;
    itens[1].valor = 1;
    itens[1].razao = (float)itens[1].valor / itens[1].peso; /* 1*/

    itens[2].peso = 3;
    itens[2].valor = 1;
    itens[2].razao = (float)itens[2].valor / itens[2].peso; /*0,33*/

    itens[3].peso = 4;
    itens[3].valor = 5;
    itens[3].razao = (float)itens[3].valor / itens[3].peso; /*1,25*/

   
    int capacidade = 5;

    int resultadoPD = mochilaPD(itens, 4, capacidade);
    int resultadoGuloso = mochilaGulosa(itens, 4, capacidade);

    printf("=====================================\n");
    printf("INSTANCIA ADVERSARIAL 2\n");
    printf("=====================================\n");

    printf("Capacidade da mochila: %d\n\n", capacidade);

    printf("Itens:\n");
    printf("Item 1. Peso: %d - Valor: %d\n", itens[0].peso, itens[0].valor);
    printf("Item 2. Peso: %d - Valor: %d\n", itens[1].peso, itens[1].valor);
    printf("Item 3. Peso: %d - Valor: %d\n\n", itens[2].peso, itens[2].valor);
    printf("Item 4. Peso: %d - Valor: %d\n", itens[3].peso, itens[3].valor);
   

    printf("Programacao Dinamica: %d\n", resultadoPD);
    printf("Algoritmo Guloso: %d\n", resultadoGuloso);

    printf("Qualidade da heuristica: %.2f\n",
           ((double)resultadoGuloso / resultadoPD) * 100.0);

  
}