#include "f_base.h"



nodo * Cria_Nodo() //aloca memória para o nodo
{
     nodo *p;
     p = (nodo *) malloc(sizeof(nodo));
     if(!p)
     {
     printf("Problema de alocação");
     exit(0);
     }
     return p;
}

void debug_mostrar_matriz(nodo *inicio){
    int index = 0;
    nodo *aux = inicio;

    system("cls");
    for(; aux!=NULL; aux = aux->prox){
        printf("%d  x:%d y:%d dado: %f\n",index,aux->col,aux->lin,aux->dado);
        index++;

    };

}

int excluir_dado(nodo **inicio, int x, int y){

    nodo *ant = NULL, *aux = *inicio;

    while(aux!=NULL){
        if(aux->col == x && aux->lin == y){
            if(ant!=NULL)
                ant->prox = aux->prox;
            else
                *inicio = aux->prox;
            liberar_memoria_nodo(aux);
            return 1;
        };
        ant = aux;
        aux = aux->prox;
    };
    return 0;

}

int liberar_memoria_nodo(nodo *nodo){
    free(nodo);

}


void inserir_dado_ordenado(nodo **p,float dado,int x ,int y ,int max_x ,int max_y)
{
    if (y < max_y)//garante que o y não seja maior que o limite da matriz
    {
        nodo *novo,*aux,*aux2;
        novo = Cria_Nodo();
        (novo->dado) = dado;
        (novo->col) = x;
        (novo->lin) = y;
        if (*p == NULL)//primeiro nodo da matriz
        {
            novo->prox = NULL;
            *p = novo;

        }
        else
        {
            //nodo menor que o primeiro
            aux = *p;
            if (retornar_valor(x, y,max_x) <= retornar_valor(aux->col,aux->lin,max_x))
            {
                if (retornar_valor(x, y,max_x) != retornar_valor(aux->col,aux->lin,max_x))
                {
                    novo->prox = aux;
                    *p = novo;
                }
                else
                {
                    novo->prox = aux->prox;
                    *p = novo;
                    free(aux);

                }
            }
            else
            {
                //insert ordenado
                for(aux = *p; ((aux) != NULL); aux = aux->prox)
                {
                    if (retornar_valor(aux->col,aux->lin,max_x) >= retornar_valor(x,y,max_x))
                        break;
                    aux2 = aux;
                    //explicação aqui: ele da break antes pra deixar o aux2 com o endereço anterior
                }

                if (aux != NULL)//se o novo não é o ultimo
                {
                    if (retornar_valor(aux->col,aux->lin,max_x) != retornar_valor(x,y,max_x))
                    {
                        novo->prox = aux;
                        aux2->prox = novo;
                    }
                    else
                    {
                        aux2->prox = novo;
                        novo->prox = aux->prox;
                        free(aux);
                    }
                }
                else
                {

                    aux2->prox = novo;
                    novo->prox = NULL;
                }
            }

        }
    }
}

void liberar_memoria(nodo *mat)
{
    while (mat != NULL)
    {
        nodo *aux = mat->prox;
        free(mat);
        mat = aux;
    }

}

void limpar_matriz(nodo **inicio){
    *inicio = NULL;
}

void alterar_dimensao(nodo **inicio, int *old_x, int *old_y, int new_x, int new_y){
    *inicio = NULL;
    *old_x = new_x;
    *old_y = new_y;

}



int retornar_valor(int x, int y,int max_y)
{
    return (y*max_y)+x;
};

float *mostrar_dados(nodo *lista,int max_x,int max_y)
{

int c,d;
nodo *aux;
aux = lista;
float *mats;

mats = (float*)malloc(sizeof(float)*(max_x*max_y));

if (aux == NULL)
{
    for(d=0;d<max_y;d++)
    {
        for(c=0;c<max_x;c++)
        {
            *(mats +(d*max_x)+c) = 0;

        }
    }

}
else
{
    for(d=0;d<max_y;d++)
    {
        for(c=0;c<max_x;c++)
        {
            if ((aux->col == c) && (aux->lin == d))
            {
                *(mats+(d*max_x)+c) = aux->dado;
                if (aux->prox != NULL)
                    aux = aux->prox;
            }
            else
            {
                *(mats+(d*max_x)+c) = 0;

            }

        }
    }

}

return mats;

}

float *mostrar_dados_diagonal(nodo *lista,int dim){

int c;
float *mats = (float*)malloc(sizeof(float)*dim);

if (lista == NULL)
    for(c=0;c<dim;c++)
        *(mats+c) = 0;
else
    for(c=0;c<dim;c++)
        *(mats+c) = procurar(lista,c,c);

return mats;

}

char imprime_lista_encadeada(nodo *N)
{
     nodo *aux;

     if(N == NULL)
        printf("\n A lista está vazia!!");
     else
     {
     for(aux = N; aux != NULL; aux = aux->prox)
     {
        printf("\n%f ", aux->dado);
        printf("%d ", aux->col);
        printf("%d ", aux->lin);
     }
     }
}


nodo *somar_matriz(nodo *aux1, nodo *aux2,int max_col,int max_lin)
{
int c,d;
float a,b;
nodo *aux3;

aux3 = NULL;


for(d=0;d<max_lin;d++)
    for(c=0;c<=max_col;c++)
    {
        a = 0;
        b = 0;
        if (aux1 != NULL)
        {
            if ((aux1->col == c) && (aux1->lin == d))
            {
                a = aux1->dado;
                aux1 = aux1->prox;
            }
        }
        if (aux2 != NULL)
        {
            if ((aux2->col == c) && (aux2->lin == d))
            {
                b = aux2->dado;
                aux2 = aux2->prox;
            }
        }

        a = a+b;
        if (a != 0)
        {
            inserir_dado_ordenado((&aux3),a,c,d,max_col,max_lin);

        }

    }

    return aux3;

}



nodo *subtrair_matriz(nodo *aux1, nodo *aux2,int max_col,int max_lin)
{
int c,d;
float a,b;
nodo *aux3;

aux3 = NULL;


for(d=0;d<max_lin;d++)
    for(c=0;c<=max_col;c++)
    {
        a = 0;
        b = 0;
        if (aux1 != NULL)
        {
            if ((aux1->col == c) && (aux1->lin == d))
            {
                a = aux1->dado;
                aux1 = aux1->prox;
            }
        }
        if (aux2 != NULL)
        {
            if ((aux2->col == c) && (aux2->lin == d))
            {
                b = aux2->dado;
                aux2 = aux2->prox;
            }
        }

        a = a-b;
        if (a != 0)
        {
            inserir_dado_ordenado((&aux3),a,c,d,max_col,max_lin);

        }

    }

    return aux3;

}


nodo *transpor_matriz(nodo *mat1,int max_x,int max_y)
{
    nodo *aux,*mat2;
    mat2 = NULL;

    for(aux = mat1; ((aux) != NULL); aux = aux->prox)
    {
        inserir_dado_ordenado(&mat2,aux->dado,aux->lin,aux->col,max_y,max_x);
    }

    return mat2;
}

float procurar(nodo *aux, int x, int y)
{

    float dado = 0;
    for(aux = aux; ((aux) != NULL); aux = aux->prox)
    {
        if ((aux->col == x) && (aux->lin == y))
        {
            dado = aux->dado;
        }
    }
    return dado;
}

nodo *multiplicar_matriz(nodo *mat1, nodo *mat2, int max_x1, int max_y1,int max_x2, int max_y2)
{
    int c,d,i,j;
    float dado1,dado2,dado3;
    nodo *mat3;
    mat3 = NULL;

    for(d=0;d<max_y1;d++)
    {
        for(c=0;c<=max_x2;c++)
        {
            dado3 = 0;
            for(i=0;i<max_x1;i++)
            {
                dado1 = procurar(mat1,i,d);
                dado2 = procurar(mat2,c,i);
                dado3 = (dado3 + (dado1*dado2));
            }
            inserir_dado_ordenado(&mat3,dado3,c,d,max_x2,max_y1);
        }

    }

    return mat3;
}
