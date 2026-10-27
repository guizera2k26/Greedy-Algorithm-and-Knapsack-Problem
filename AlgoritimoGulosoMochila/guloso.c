#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include "header.h"


void ordenarRazao(item itens[], int n)
{
    for (int i = 0; i < n - 1; i++)
    {
        for (int j = 0; j < n - 1 - i; j++)
        {
            if (itens[j].razao < itens[j + 1].razao)
            {
                item aux = itens[j];
                itens[j] = itens[j + 1];
                itens[j + 1] = aux;
            }
        }
    }
}

int mochilaGulosa(item itens[], int n, int capacidadeMoch)
{
    ordenarRazao(itens, n);

    int valorTotal = 0;
    int pesoAtual = 0;

    // printf("\nItens escolhidos:\n");

    for (int i = 0; i < n; i++)
    {
        if (pesoAtual + itens[i].peso <= capacidadeMoch)
        {
            pesoAtual += itens[i].peso;
            valorTotal += itens[i].valor;

            // printf("Item %d (peso=%d, valor=%d)\n",
            //        i + 1,
            //        itens[i].peso,
            //        itens[i].valor);
        }
    }

    return valorTotal;
}