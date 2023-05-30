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
} Grafo;

Fila *cria_fila();
Fila *enqueue(Fila *f, void *elemento);
void *dequeue(Fila *f);
int eh_vazia_fila(Fila *f);
Listad *cria_listad();
Nod *cria_nod(void *valor);
Listad *insere_inicio_listad(Listad *L, void *valor);
Listad *insere_fim_listad(Listad *L, void *valor);
void *remove_fim_listad(Listad *L);
void *remove_inicio_listad(Listad *L);
Listad *libera_listad(Listad *L);
int eh_vazia_listad(Listad *L);
Grafo *cria_grafo(int n, int valorado, int direcionado);
void preenche_vertices(Grafo *g);
void preenche_arestas(Grafo *g);
void mostra_grafo(Grafo *g);
void percurso_largura(Grafo *g);
void profundidade(Grafo *g);
int verifica_grafo(Grafo* g);

int main()
{
    int e = 0, l = 0, x = 0, y = 0, verificacao = 0, contador = 1;
    Grafo* g = NULL;

    do
    {
    //printf("Numero de estacoes\n");
    scanf("%i", &e);
    //printf("Numero de linhas\n");
    scanf("%i", &l);
    g = cria_grafo(e, 0, 0);
    preenche_arestas(g);
    preenche_vertices(g);

    if(e >= 3 && e <= 100)
    {
        if(l >= (e - 1) && l <= (e*((e-1)/2)))
        {
            while(l > 0)
            {
            //printf("x\n");
            scanf("%i", &x);
            //printf("y\n");
            scanf("%i", &y);

            g->adjacencias[x-1][y-1] = g->adjacencias[y-1][x-1] = 1;
            
            l--;
            }
        }
        verificacao = verifica_grafo(g);
        if(verificacao == 0)
        {

            printf("Teste %d\nfalha\n\n", contador);
        }
        if(verificacao == 1)
        {
            printf("Teste %d\nnormal\n\n", contador);
        }
        contador++;
    }
    }while(l > 0 || e > 0);

    free(g);

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

int eh_vazia_fila(Fila *f)
{
    return eh_vazia_listad(f);
}

int *cria_inteiro(int n)
{
    int *a = malloc(sizeof(int));
    *a = n;
    return a;
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

Listad *insere_inicio_listad(Listad *L, void *valor)
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
            L->ini = L->fim = novo;
        else
        {
            novo->prox = L->ini;
            L->ini->ant = novo;
            L->ini = novo;
        }
    }
    return L;
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

void *remove_fim_listad(Listad *L)
{
    Nod *aux;
    void *resposta = NULL;

    if (L != NULL && L->fim != NULL)
    {
        aux = L->fim;
        if (L->ini != L->fim) // mais de um elemento na lista
        {
            L->fim->ant->prox = NULL;
            L->fim = L->fim->ant;
        }
        else // s� tem um elemento na lista
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

int eh_vazia_listad(Listad *L)
{
    if (L == NULL || L->ini == NULL)
        return 1;
    else
        return 0;
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
    g->adjacencias = (int **)malloc(sizeof(int*) * n);
    for (i = 0; i < n; i++)
        g->adjacencias[i] = (int *)malloc(sizeof(int) * n);
    return g;
}

void preenche_vertices(Grafo *g)
{
    int i;
    for (i = 0; i < g->ordem; i++)
        g->vertices[i] = i + 1;
}

void preenche_arestas(Grafo *g)
{
    int i, j;
    for (i = 0; i < g->ordem; i++)
        for (j = 0; j < g->ordem; j++)
            //scanf("%d", &g->adjacencias[i][j]);
            g->adjacencias[i][j] = 0;
}

void mostra_grafo(Grafo *g)
{
    int i, j;
    for (i = 0; i < g->ordem; i++)
    {
        printf("%i -> ", g->vertices[i]);
        for (j = 0; j < g->ordem; j++)
            if (g->adjacencias[i][j] != 0)
                printf("%d - ", j + 1);
    }
}

void limpa(Grafo *g)
{
    int i;
    for (i = 0; i < g->ordem; i++)
        g->visitados[i] = 0;
}

void percurso_largura(Grafo *g)
{
    Fila *f = cria_fila();
    int *w, *nro;
    int i;

    limpa(g);
    g->visitados[0] = 1; // visitei o primeiro vertice
    w = (int *)malloc(sizeof(int));
    *w = 0;
    enqueue(f, (void *)nro);

    while (!eh_vazia_fila(f))
    {
        w = (int *)dequeue(f);
        printf("%d \n", g->vertices[*w]);
        for (i = 0; i < g->ordem; i++)
        {
            if (g->adjacencias[*w][i] == 1)
            {
                if (!g->visitados[i])
                {
                    g->visitados[i] = 1; // visitei o primeiro vertice
                    nro = (int *)malloc(sizeof(int));
                    *nro = i;
                    enqueue(f, (void *)nro);
                }
            }
        }
    }
}

void prof(int v, Grafo* g)
{
    int w;
    g->visitados[v] = 1;
    printf("%d \n", v + 1);
    for (w = 0; w < g->ordem; w++)
    {
        if (g->adjacencias[v][w] == 1)
        {
            if (!g->visitados[w])
            {
                prof(w, g);
            }
        }
    }
}

void profundidade(Grafo *g)
{
    int i;
    limpa(g);

    for (i = 0; i < g->ordem; i++)
    {

        if (!g->visitados[i])
        {
            prof(i, g);
        }
    }
}

int busca_profundidade_recursao(int origem, int destino, Grafo *g)
{
   if(origem == destino){
    return 1;
   }

   g->visitados[origem] = 1;
   printf(" PROFUNDIDADE %d \n", origem+1);
   for(int i = 0; i < g->ordem; i++){
        
        if(g->adjacencias[origem][i] >= 1 && !g->visitados[i]){
            if(busca_profundidade_recursao(i, destino, g)){
                return 1;
            }
        }
   }
    
    return 0;
}


//retorna 1 se houver um caminho e 0 se nao houver
int busca_profundidade(int origem, int destino, Grafo *g)
{
    limpa(g);
    return busca_profundidade_recursao(origem, destino, g);
}


//retorna 1 se houver caminho e 0 se nao houver
int busca_largura(int origem, int destino, Grafo *g)
{
    Fila *f = cria_fila();
    int *w;
    int i;

    limpa(g);
    g->visitados[origem] = 1;
    w = (int *)malloc(sizeof(int));
    *w = origem;
    enqueue(f, (void *)w);

    while (!eh_vazia_fila(f))
    {
        w = (int *)dequeue(f);
        printf(" LARGURA %d \n", g->vertices[*w]);
        if (*w == destino)
        {
            return 1;
        }
        for (i = 0; i < g->ordem; i++)
        {
            if (g->adjacencias[*w][i] == 1)
            {
                if (!g->visitados[i])
                {
                    g->visitados[i] = 1;
                    w = (int *)malloc(sizeof(int));
                    *w = i;
                    enqueue(f, (void *)w);
                }
            }
        }
    }

    return 0;
}

int verifica_grafo(Grafo* g)
{
    int i, j, k;
    int validacao = 0;

    for(i = 0; i < g->ordem; i++)
    {
        k = 0;
        for(j = 0; j < g->ordem; j++)
        {
            k = k + g->adjacencias[i][j];
        }
        if(k == 0)
        {
            return validacao;    
        }
    }
    validacao = 1;
    return validacao;
}
