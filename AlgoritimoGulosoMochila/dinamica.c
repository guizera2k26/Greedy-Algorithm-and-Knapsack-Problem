#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include "header.h"



int max(int a, int b)
{
    if (a > b)
        return a;
    else
        return b;
}

int mochilaPD(item itens[], int n, int capacidadeMoch)
{
    int **tabelaMemoria = malloc((n + 1) * sizeof(int *));

    if (tabelaMemoria == NULL)
    {
        printf("Erro ao alocar memoria.\n");
        return 0;
    }

    for (int i = 0; i <= n; i++)
    {
        tabelaMemoria[i] = malloc((capacidadeMoch + 1) * sizeof(int));

        if (tabelaMemoria[i] == NULL)
        {
            printf("Erro ao alocar memoria.\n");

            for (int j = 0; j < i; j++)
            {
                free(tabelaMemoria[j]);
            }

            free(tabelaMemoria);

            return 0;
        }
    }

    for (int i = 0; i <= n; i++)
    {
        for (int w = 0; w <= capacidadeMoch; w++)
        {
            if (i == 0 || w == 0)
                tabelaMemoria[i][w] = 0;
        }
    }

    for (int i = 1; i <= n; i++)
    {
        for (int w = 0; w <= capacidadeMoch; w++)
        {
            if (itens[i - 1].peso <= w)
            {
                int a = tabelaMemoria[i - 1][w];
                int b = itens[i - 1].valor +
                        tabelaMemoria[i - 1][w - itens[i - 1].peso];

                if (a > b)
                    tabelaMemoria[i][w] = a;
                else
                    tabelaMemoria[i][w] = b;
            }
            else
            {
                tabelaMemoria[i][w] = tabelaMemoria[i - 1][w];
            }
        }
    }

    int i = n;
    int w = capacidadeMoch;

    while (i > 0 && w > 0)
    {
        if (tabelaMemoria[i][w] != tabelaMemoria[i - 1][w])
        {
            w -= itens[i - 1].peso;
        }

        i--;
    }

    int resultado = tabelaMemoria[n][capacidadeMoch];

    for (int i = 0; i <= n; i++)
    {
        free(tabelaMemoria[i]);
    }

    free(tabelaMemoria);

    return resultado;
}