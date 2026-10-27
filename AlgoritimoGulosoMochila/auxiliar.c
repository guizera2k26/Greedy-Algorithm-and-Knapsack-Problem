#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include "header.h"
#include <math.h> 
#include <string.h>

double calcularDesvioPadraoTempo(double tempos[], int n, double *mediaSaida)
{
    double soma = 0.0;
    
  
    for (int i = 0; i < n; i++)
    {
        soma += tempos[i];
    }
    double media = soma / n;
    *mediaSaida = media; 

   
    double somaQuadrados = 0.0;
    for (int i = 0; i < n; i++)
    {
        double diferenca = tempos[i] - media;
        somaQuadrados += diferenca * diferenca;
    }

   
    return sqrt(somaQuadrados / n);
}

void gerarValores(item itens[], int n)
{
    for (int i = 0; i < n; i++)
    {
        itens[i].peso = rand() % 100 + 1;
        itens[i].valor = rand() % 100 + 1;
        itens[i].razao = (float) itens[i].valor / itens[i].peso;
    }
}



void executarInstanciasPD(int n)
{
    double tempoExec[10];
    
    char nomeArquivo[30];
    sprintf(nomeArquivo, "PD%d.txt", n);

   
    FILE *arquivoPD = fopen(nomeArquivo, "w"); 
    if (arquivoPD == NULL)
    {
        printf("Erro ao abrir o arquivo resultados. (PD)\n");
        return;
    }

  
    fprintf(arquivoPD, "Algoritmo;Tamanho;Semente;Execucao;Tempo Segundos;Valor\n");

    for (int semente = 0; semente < 5; semente++)
    {
        printf("\n==============================\n");
        printf("Semente %d\n", semente + 1);
        printf("==============================\n");

        item *itens = malloc(n * sizeof(item));
        if (itens == NULL)
        {
            printf("Erro ao alocar memoria.\n");
            fclose(arquivoPD);
            return;
        }

        srand(semente + 5);
        gerarValores(itens, n);

        int MochilaEspaco = 50 * n;
        int resultado = 0;
     
        
        for (int execucao = 0; execucao < 10; execucao++)
        {
            clock_t inicio = clock();
            resultado = mochilaPD(itens, n, MochilaEspaco);
            clock_t fim = clock();
            
            tempoExec[execucao] = (double)(fim - inicio) / CLOCKS_PER_SEC;
            printf("Execucao %d: %.6f s | valor: %d\n", execucao + 1, tempoExec[execucao], resultado);
           
            // Grava a execução atual no arquivo
            fprintf(arquivoPD, "PD;%d;%d;%d;%.6f;%d\n", 
                    n, semente + 1, execucao + 1, tempoExec[execucao], resultado);
        }
            
        
        double media = 0.0;
        double desvioPadrao = calcularDesvioPadraoTempo(tempoExec, 10, &media);

        printf("\nTempo medio: %.6f segundos\n", media);
        printf("Desvio padrao do tempo:  %.6f segundos\n", desvioPadrao);
        printf("Valor da solucao: %d\n", resultado);

       
        fprintf(arquivoPD, "PD;%d;%d;MEDIA;%.6f;%d\n", 
                n, semente + 1, media, resultado);

        fprintf(arquivoPD, "PD;%d;%d;DESVIO;%.6f;0.000000\n\n", 
                n, semente + 1, desvioPadrao);

        free(itens);
    }

    
    fclose(arquivoPD);
}


void executarInstanciasGuloso(int n)
{
    double tempoExec[10];
    
    char nomeArquivo[30];
    sprintf(nomeArquivo, "GULOSO%d.txt", n);

   
    FILE *arquivoG = fopen(nomeArquivo, "w"); 
    if (arquivoG == NULL)
    {
        printf("Erro ao abrir o arquivo resultados. (Guloso)\n");
        return;
    }

   
    fprintf(arquivoG, "Algoritmo;Tamanho;Semente;Execucao;Tempo Segundos;Valor\n");

    for (int semente = 0; semente < 5; semente++)
    {
        printf("\n==============================\n");
        printf("Semente %d\n", semente + 1);
        printf("==============================\n");

        item *itens = malloc(n * sizeof(item));
        item *backup = malloc(n * sizeof(item));

        if (itens == NULL || backup == NULL)
        {
            printf("Erro ao alocar memoria.\n");
            if (itens) free(itens);
            if (backup) free(backup);
            fclose(arquivoG);
            return;
        }

        srand(semente + 5);
        gerarValores(itens, n);

        memcpy(backup, itens, n * sizeof(item));

        int mochilaEspaco = 50 * n;
        int resultado = 0;

        for (int execucao = 0; execucao < 10; execucao++)
        {
            memcpy(itens, backup, n * sizeof(item));

            clock_t inicio = clock();
            resultado = mochilaGulosa(itens, n, mochilaEspaco);
            clock_t fim = clock();

            tempoExec[execucao] = (double)(fim - inicio) / CLOCKS_PER_SEC;
            printf("Execucao %d: %.6f s | valor: %d\n", execucao + 1, tempoExec[execucao], resultado);

          
            fprintf(arquivoG, "GULOSO;%d;%d;%d;%.6f;%d\n", 
                    n, semente + 1, execucao + 1, tempoExec[execucao], resultado);
        }

        double media = 0.0;
        double desvioPadrao = calcularDesvioPadraoTempo(tempoExec, 10, &media);

        printf("\nTempo medio: %.6f segundos\n", media);
        printf("Desvio padrao: %.6f segundos\n", desvioPadrao);
        printf("Valor da solucao: %d\n", resultado);

       
        fprintf(arquivoG, "GULOSO;%d;%d;MEDIA;%.6f;%d\n", 
                n, semente + 1, media, resultado);

        fprintf(arquivoG, "GULOSO;%d;%d;DESVIO;%.6f;0.000000\n\n", 
                n, semente + 1, desvioPadrao);

        free(backup);
        free(itens);
    }

    
    fclose(arquivoG);
}


void compararAlgoritmos(int n)
{
    double tempoPD[10];
    double tempoG[10];

    char nomeArquivo[30];
    sprintf(nomeArquivo, "COMPARACAO%d.txt", n);

    FILE *arquivoC = fopen(nomeArquivo, "w");

    if (arquivoC == NULL)
    {
        printf("Erro ao abrir arquivo.\n");
        return;
    }

    fprintf(arquivoC, "Algoritmo;Tamanho;Semente;Execucao;ValorPD;ValorGuloso;TempoPD;TempoGuloso;Qualidade\n");

    for (int semente = 0; semente < 5; semente++)
    {
        printf("\n==============================\n");
        printf("Semente %d\n", semente + 1);
        printf("==============================\n");

        item *itens = malloc(n * sizeof(item));
        item *backup = malloc(n * sizeof(item));

        if (itens == NULL || backup == NULL)
        {
            printf("Erro ao alocar memoria.\n");
            fclose(arquivoC);
            return;
        }

        srand(semente + 5);
        gerarValores(itens, n);

        memcpy(backup, itens, n * sizeof(item));

        int mochilaEspaco = 50 * n;

        int resultadoPD = 0;
        int resultadoGuloso = 0;

        for (int execucao = 0; execucao < 10; execucao++)
        {
            /* ---------- Programação Dinâmica ---------- */

            clock_t inicioPD = clock();

            resultadoPD = mochilaPD(itens, n, mochilaEspaco);

            clock_t fimPD = clock();

            tempoPD[execucao] =
                (double)(fimPD - inicioPD) / CLOCKS_PER_SEC;

            /* ---------- Guloso ---------- */

            memcpy(itens, backup, n * sizeof(item));

            clock_t inicioG = clock();

            resultadoGuloso = mochilaGulosa(itens, n, mochilaEspaco);

            clock_t fimG = clock();

            tempoG[execucao] = (double)(fimG - inicioG) / CLOCKS_PER_SEC;

            double qualidade = ((double)resultadoGuloso / resultadoPD) * 100.0;

            fprintf(arquivoC, "COMPARACAO;%d;%d;%d;%d;%d;%.6f;%.6f;%.2f\n", n, semente + 1, execucao + 1, resultadoPD, resultadoGuloso, tempoPD[execucao], tempoG[execucao], qualidade);
        }

        double mediaPD = 0.0;
        double mediaG = 0.0;

        double desvioPD = calcularDesvioPadraoTempo(tempoPD, 10, &mediaPD);

        double desvioG = calcularDesvioPadraoTempo(tempoG, 10, &mediaG);

        double qualidade = ((double)resultadoGuloso / resultadoPD) * 100.0;

       

        printf("\nProgramacao Dinamica\n");

        for (int i = 0; i < 10; i++)
        {
            printf("Execucao %d: %.6f s | Valor: %d\n", i + 1, tempoPD[i], resultadoPD);
        }

        printf("\nTempo medio: %.6f segundos\n", mediaPD);
        printf("Desvio padrao: %.6f segundos\n", desvioPD);
        printf("Valor da solucao: %d\n", resultadoPD);

     

        printf("\nAlgoritmo Guloso\n");

        for (int i = 0; i < 10; i++)
        {
            printf("Execucao %d: %.6f s | Valor: %d\n", i + 1, tempoG[i], resultadoGuloso);
        }

        printf("\nTempo medio: %.6f segundos\n", mediaG);
        printf("Desvio padrao: %.6f segundos\n", desvioG);
        printf("Valor da solucao: %d\n", resultadoGuloso);

        printf("\nQualidade da heuristica: %.2f\n", qualidade);

       fprintf(arquivoC, "COMPARACAO;%d;%d;MEDIA;%d;%d;%.6f;%.6f;%.2f\n", 
                n, semente + 1, resultadoPD, resultadoGuloso, mediaPD, mediaG, qualidade);

        fprintf(arquivoC, "COMPARACAO;%d;%d;DESVIO;;;%.6f;%.6f;\n\n", 
                n, semente + 1, desvioPD, desvioG);
        free(backup);
        free(itens);
    }

    fclose(arquivoC);
}