#include <stdio.h>
#include <stdlib.h>

struct nod
{
    void *info;
    struct nod *ant;
    struct nod *prox;
};
typedef struct nod Nod;

struct listad
{
    Nod *ini;
    Nod *fim;
};
typedef struct listad Listad;
typedef Listad Fila;

typedef struct grafo
{
    int ordem;
    int *vertices;
    int **adjacencias;
    int eh_direcionado;
    int eh_valorado;
    int *visitados;
    Listad *lista;
} Grafo;

Fila *cria_fila();
Fila *enqueue(Fila *f, void *elemento);
void *dequeue(Fila *f);
Listad *cria_listad();
void mostra_listad(Listad* L);
Nod *cria_nod(void *valor);
Listad *insere_fim_listad(Listad *L, void *valor);
void *remove_inicio_listad(Listad *L);
Listad *libera_listad(Listad *L);
Grafo *cria_grafo(int n, int valorado, int direcionado);
void preenche_arestas(Grafo *g);
void *percurso_larg_lim(Grafo *g, int vertice, int lim, int vertice_inicial);
void swapList(Nod *a, Nod *b);
void sort_vertices_byValue(Listad *L);
int *create_int(int valor);

int main()
{
    int c = 0, e = 0, l = 0, p = 0;
    int contador = 1, x = 0, y = 0;
    Grafo *g = NULL;

    do
    {
        // printf("Cidade\n");
        scanf("%d", &c);
        // printf("Estradas\n");
        scanf("%d", &e);
        // printf("Cidade onde esta\n");
        scanf("%d", &l);
        // printf("Numero de pedagios disposto a pagar\n");
        scanf("%d", &p);

        g = cria_grafo(c, 0, 0);

        if ((c > 0 && c <= 50) && (e > 0 && e <= 2500) && (l > 0 && l <= c) && (p > 0 && p <= c))
        {
            preenche_arestas(g);

            for (int i = 0; i < e; i++)
            {
                // printf("x\n");
                scanf("%d", &x);
                // printf("y\n");
                scanf("%d", &y);
                g->adjacencias[x - 1][y - 1] = g->adjacencias[y - 1][x - 1] = 1;
            }

                printf("Teste %d\n", contador);
                percurso_larg_lim(g, l, p, l);
                sort_vertices_byValue(g->lista);
                mostra_listad(g->lista);

                printf("\n");
            contador++;
        }

    } while (c != 0 || e != 0 || l != 0 || p != 0);
    return 0;
}

Fila *cria_fila()
{
    return cria_listad();
}

Fila *enqueue(Fila *f, void *elemento)
{
    return insere_fim_listad(f, elemento);
}

void *dequeue(Fila *f)
{
    return remove_inicio_listad(f);
}

Listad *cria_listad()
{
    Listad *novalista;
    novalista = (Listad *)malloc(sizeof(Listad));
    novalista->ini = novalista->fim = NULL;
    return novalista;
}

Nod *cria_nod(void *valor)
{
    Nod *novo = (Nod *)malloc(sizeof(Nod));
    novo->ant = novo->prox = NULL;
    novo->info = valor;
    return novo;
}

Listad *insere_fim_listad(Listad *L, void *valor)
{
    Nod *novo = cria_nod(valor);

    if (L == NULL)
    {
        L = cria_listad();
        L->ini = L->fim = novo;
    }
    else
    {

        if (L->ini == NULL)
        {
            L->ini = L->fim = novo;
        }
        else
        {
            novo->ant = L->fim;
            L->fim->prox = novo;
            L->fim = novo;
        }
    }
    return L;
}

void *remove_inicio_listad(Listad *L)
{
    Nod *aux;
    void *resposta = NULL; // quando nao tem nada pra remover
    if (L != NULL)
        if (L->ini != NULL)
        {
            aux = L->ini;

            if (L->ini != L->fim)
            {
                L->ini->prox->ant = NULL;
                L->ini = L->ini->prox;
            }
            else
                L->ini = L->fim = NULL;

            resposta = aux->info;
            free(aux);
        }
    return resposta;
}

Listad *libera_listad(Listad *L)
{
    Nod *aux = L->ini;

    while (aux != NULL)
    {
        L->ini = L->ini->prox;
        free(aux->info);
        free(aux);
        aux = L->ini;
    }

    free(L);
    return NULL;
}


Grafo *cria_grafo(int n, int valorado, int direcionado)
{
    int i;
    Grafo *g = (Grafo *)malloc(sizeof(Grafo));

    g->eh_direcionado = direcionado;
    g->eh_valorado = valorado;
    g->ordem = n;
    g->vertices = (int *)malloc(sizeof(int) * n);
    g->visitados = (int *)malloc(sizeof(int) * n);
    g->adjacencias = (int **)malloc(sizeof(int *) * n);
    g->lista = cria_listad();
    for (i = 0; i < n; i++)
        g->adjacencias[i] = (int *)malloc(sizeof(int) * n);
    return g;
}

void preenche_arestas(Grafo *g)
{
    int i, j;
    for (i = 0; i < g->ordem; i++)
        for (j = 0; j < g->ordem; j++)
            // scanf("%d", &g->adjacencias[i][j]);
            g->adjacencias[i][j] = 0;
}

int verifica_grafo(Grafo *g)
{
    int i, j, k;
    int validacao = 0;

    for (i = 0; i < g->ordem; i++)
    {
        k = 0;
        for (j = 0; j < g->ordem; j++)
        {
            k = k + g->adjacencias[i][j];
        }
        if (k == 0)
        {
            return validacao;
        }
    }
    validacao = 1;
    return validacao;
}

void sort_vertices_byValue(Listad *L)
{
    int swapped, i;
    Nod *ptr1;
    Nod *lptr = NULL;

    Nod *start = L->ini;
    /* Checking for empty list */
    if (start == NULL)
        return;
    do
    {
        swapped = 0;
        ptr1 = start;

        while (ptr1->prox != lptr)
        {
            if (*((int*)ptr1->info) > *((int*)ptr1->prox->info))
            {
                swapList(ptr1, ptr1->prox);
                swapped = 1;
            }
            ptr1 = ptr1->prox;
        }
        lptr = ptr1;
    } while (swapped);
}

void swapList(Nod *a, Nod *b)
{
    void *temp = a->info;
    a->info = b->info;
    b->info = temp;
}

void *percurso_larg_lim(Grafo *g, int vertice, int lim, int vertice_inicial)
{
    int i = 0;
    if (g->visitados[vertice - 1] != 1)
    {
        g->visitados[vertice - 1] = 1;
        if (vertice_inicial != vertice)
        {
            lim -= 1;
            g->lista = insere_fim_listad(g->lista, (void*) create_int(vertice));
            // printf("%d ", vertice);
        }
        if (lim != 0)
        {
            for (i = 0; i < g->ordem; i++)
            {
                if (g->adjacencias[vertice - 1][i] == 1)
                {
                    percurso_larg_lim(g, i + 1, lim, vertice_inicial);
                }
            }
        }
    }
}

void mostra_listad(Listad* L)
{
    Nod* aux = L->ini;

    while(aux != NULL)
    {
        printf("%d ", *((int*)aux->info));
        aux = aux->prox;
    }
    printf("\n ");
}

int *create_int(int valor)
{
    int *new = (int *)malloc(sizeof(int));
    *new = valor;
    return new;
}