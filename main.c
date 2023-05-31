#include <stdio.h>
#include <stdlib.h>

//nomes: Breno Marques Freitas, Rafael de Oliveira Évora

struct noavl
{
    int info;
    int fb;
    struct noavl *esq, *dir;
    //struct noavl *pai;
};
typedef struct noavl Noavl;

//PROTÓTIPO

void libera_avl(Noavl* raiz);
void recalcula_fb(Noavl *candidato,int info);
Noavl *cria_noavl(int info);
Noavl *insere_noavl(Noavl *tree, int info, Noavl **pai_candidato);
Noavl *insercao_geral(Noavl *tree,int info);
void em_ordem(Noavl* raiz, int* maior);

//MAIN

int main()
{
    int qnt = 0, count = 0, insert = 0, test = 0;
    Noavl* tree = NULL;
    //printf("Quantas arvores: ");
    scanf("%d",&qnt);

    for(count=0;count<qnt;count++)
    {
        insert = 0;

        while(insert != -1)
        {
            //printf("Inserindo:\n");
            scanf("%d",&insert);
            if(insert != -1)
            {
                tree = insercao_geral(tree,insert);
            }
        }
        em_ordem(tree, &test);
        //printf("%d",test);

        if((test <= -2) || (test >= 2))
        {
            printf("nao\n");
        } else
        {
            printf("sim\n");
        }

        libera_avl(tree);
        tree = NULL;
    }

    return 0;
}

//FUNÇÕES

Noavl *cria_noavl(int info)
{
    Noavl *novo = (Noavl *)malloc(sizeof(Noavl));
    novo->dir = novo->esq = NULL;
    novo->info = info;
    novo->fb = 0;

    return novo;
}

void em_ordem(Noavl* raiz, int* maior)
{

        if (raiz != NULL)
        {
            if((raiz->fb <= -2)||(raiz->fb >= 2))
            {
                *maior = raiz->fb;
            }
            em_ordem(raiz->esq, maior);
            em_ordem(raiz->dir, maior);

        }
}

void recalcula_fb(Noavl *candidato,
                  int info)
{
    Noavl *aux = candidato;
    while (aux->info != info)
    {
        if (info < aux->info)
        {
            aux->fb++;
            aux = aux->esq;
        }
        else
        {
            aux->fb--;
            aux = aux->dir;
        }
    }
}

Noavl *insere_noavl(Noavl *tree, int info, Noavl **pai_candidato)
{
    Noavl *aux = tree;
    Noavl *pai_aux = NULL;
    Noavl *novo = cria_noavl(info);
    Noavl *candidato = tree;

    while (aux != NULL)
    {
        if (aux->fb != 0)
        {
            candidato = aux;
            *pai_candidato = pai_aux;
        }
        pai_aux = aux;
        if (info < aux->info)
            aux = aux->esq;
        else
            aux = aux->dir;
    }
    if (info < pai_aux->info)
        pai_aux->esq = novo;
    else
        pai_aux->dir = novo;

    return candidato;
}

Noavl *insercao_geral(Noavl *tree,int info)
{
    Noavl *candidato = NULL;
    Noavl *pai_candidato = NULL;

    if (tree == NULL)
    {
        return cria_noavl(info);
    }
    else
    {
        candidato = insere_noavl(tree, info, &pai_candidato);
        recalcula_fb(candidato, info);
    }
    return tree;
}

void libera_avl(Noavl* raiz)
{

        if (raiz != NULL)
        {
            libera_avl(raiz->esq);
            libera_avl(raiz->dir);
            free(raiz);
        }
}