#ifndef HEADER_H
#define HEADER_H

typedef struct Item
{
    int valor;
    int peso;
    float razao;
} item;


void gerarValores(item itens[], int n);
double calcularDesvioPadraoTempo(double tempos[], int n, double *mediaSaida);

void executarInstanciasPD(int n);
void executarInstanciasGuloso(int n);

int max(int a, int b);
int mochilaPD(item itens[], int n, int capacidadeMoch);

void ordenarRazao(item itens[], int n);
int mochilaGulosa(item itens[], int n, int capacidadeMoch);

void compararAlgoritmos(int n);


void executarInstanciasAdversariais();
void instanciaAdversarial1();
void instanciaAdversarial2();

#endif