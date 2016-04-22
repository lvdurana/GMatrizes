#include "f_base.h"



nodo * Cria_Nodo() //aloca mem�ria para o nodo
{
     nodo *p;
     p = (nodo *) malloc(sizeof(nodo));
     if(!p)
     {
     printf("Problema de aloca��o");
     exit(0);
     }
     return p;
}


void inserir_dado_ordenado(nodo **p , float dado, int x ,int y ,int max_x ,int max_y)
{
    printf("%f\n",dado);
    if (y < max_y)//garante que o y n�o seja maior que o limite da matriz
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
            if (retornar_valor(x, y,max_y) <= retornar_valor(aux->col,aux->lin,max_y))
            {
                if (retornar_valor(x, y,max_y) != retornar_valor(aux->col,aux->lin,max_y))
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
                    if (retornar_valor(aux->col,aux->lin,max_y) >= retornar_valor(x,y,max_y))
                        break;
                    aux2 = aux;
                    //explica��o aqui: ele da break antes pra deixar o aux2 com o endere�o anterior
                }

                if (aux != NULL)//se o novo n�o � o ultimo
                {
                    if (retornar_valor(aux->col,aux->lin,max_y) == retornar_valor(x,y,max_y))
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

void yay()
{
    printf("*yay*");
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




retornar_valor(int x, int y,int max_y)
{
    return (y*max_y)+x;
};

float *mostrar_dados(nodo *lista,int max_x,int max_y)
{

int c,d;
nodo *aux;
aux = lista;
float *mat;

mat = (float*)malloc(sizeof(float)*max_x*max_y);


if (aux == NULL)
{
    for(d=0;d<max_y;d++)
    {
        for(c=0;c<max_x;c++)
        {
            *(mat+d*max_y+c) = 0;
            //mat[d][c] = 0;
            printf("0 ");

        }
        printf("\n");
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
                *(mat+d*max_y+c) = aux->dado;
                printf("%.0f ", aux->dado);
                if (aux->prox != NULL)
                    aux = aux->prox;
            }
            else
            {
                *(mat+d*max_y+c) = 0;
                printf("0 ");

            }
        }
        printf("\n");
    }

}
return mat;

}

char imprime_lista_ecandeada(nodo *N)
{
     nodo *aux;

     if(N == NULL)
     printf("\n A lista est� vazia!!");
     else
     {
     for(aux = N; aux != NULL; aux = aux->prox)
     {
        printf("\n%d ", aux->dado);
        printf("%d ", aux->col);
        printf("%d ", aux->lin);
     }
     }
}


int somar_matriz(nodo *aux1, nodo *aux2,int max_col,int max_lin)
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
            //inserir_dado_ordenado((&aux3),a,c,d,max_col,max_lin);

        }

    }

    return aux3;

}



int subtrair_matriz(nodo *aux1, nodo *aux2,int max_col,int max_lin)
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
            //printf("%d",*aux3);
            //inserir_dado_ordenado((&aux3),a,c,d,max_col,max_lin);

        }

    }

    return aux3;

}


int transpor_matriz(nodo *mat1,int max_x,int max_y)
{
    nodo *aux,*mat2;
    mat2 = NULL;

    for(aux = mat1; ((aux) != NULL); aux = aux->prox)
    {
        //inserir_dado_ordenado(&mat2,aux->dado,aux->lin,aux->col,max_y,max_x);
    }

    return mat2;
}


void maina()
{
    //x = col
    //y = lin
    //n�o me questione porque
    int tp0,c,d,x,y;
    int max_lin[3];
    int max_col[3];
    float dado;
    nodo *mat1,*mat2,*mat3;

    //primeira matriz

    mat1 = NULL;
    mat3 = NULL;

    printf("Primeira matriz\n");
    printf("tamanho maximo da linha:\n");
    scanf("%d",&max_col[0]);


    printf("tamanho maximo da coluna:\n");
    scanf("%d",&max_lin[0]);

    while (1){

        printf("X:");
        scanf("%d",&x);

        if (x < 0)
            break;

        printf("Y:");
        scanf("%d",&y);

        printf("Entre o dado\n");
        scanf("%f",&dado);


        system("cls");

        //inserir_dado_ordenado((&mat1),dado,x,y,max_col[0],max_lin[0]);

        mostrar_dados(mat1,max_col[0],max_lin[0]);

        imprime_lista_ecandeada(mat1);
        getch();
        system("cls");
    };
    system("cls");
/*
   //segunda matriz

    mat2 = NULL;

    printf("Segunda matriz\n");
    printf("Tamanho da primeira matriz:%dX%d\n",max_col[0],max_lin[0]);
    printf("tamanho maximo da linha:\n");
    scanf("%d",&max_col[1]);


    printf("tamanho maximo da coluna:\n");
    scanf("%d",&max_lin[1]);


    while (1){

        printf("X:");
        scanf("%d",&x);

        if (x < 0)
            break;

        printf("Y:");
        scanf("%d",&y);

        printf("Entre o dado\n");
        scanf("%f",&dado);


        system("cls");

        inserir_dado_ordenado((&mat2),dado,x,y,max_col[1],max_lin[1]);

        mostrar_dados(mat2,max_col[1],max_lin[1]);

        imprime_lista_ecandeada(mat2);
        getch();
        system("cls");
    };

    system("cls");
    printf("\n");
    mostrar_dados(mat1,max_col[0],max_lin[0]);
    printf("\n\n");
    mostrar_dados(mat2,max_col[1],max_lin[1]);
    printf("\n\n");
    mat3 = somar_matriz(mat1,mat2,max_col[0],max_lin[0]);
    mostrar_dados(mat3,max_col[0],max_lin[0]);

    liberar_memoria(mat3);
    printf("\n\n");
    mat3 = subtrair_matriz(mat1,mat2,max_col[0],max_lin[0]);
    mostrar_dados(mat3,max_col[0],max_lin[0]);
*/

    mat3 = transpor_matriz(mat1,max_col[0],max_lin[0]);

    mostrar_dados(mat3,max_lin[0],max_col[0]);

}