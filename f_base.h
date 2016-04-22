#if defined(UNICODE) && !defined(_UNICODE)
    #define _UNICODE
#elif defined(_UNICODE) && !defined(UNICODE)
    #define UNICODE
#endif

#include <tchar.h>
#include <windows.h>
#include <stdio.h>
#include "resource.h"

#define M1_X_POS 10
#define M1_Y_POS 30
#define M2_X_POS 680
#define M2_Y_POS 30
#define M_WIDTH 640
#define M_HEIGHT 320
#define M_FIELD_WIDTH 32
#define M_FIELD_HEIGHT 16

typedef struct no
{
     float dado;
     int lin, col;
     struct nodo *prox;
} nodo;

typedef struct mat{
    int dim_x;
    int dim_y;
    nodo *inicio;

}matriz;

typedef struct jmat {
    matriz mat;
    HBITMAP bmp_mat;



}j_matriz;

void inserir_dado_ordenado(nodo **p ,float dado,int x ,int y ,int max_x ,int max_y);

