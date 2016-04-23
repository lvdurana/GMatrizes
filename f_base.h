#if defined(UNICODE) && !defined(_UNICODE)
    #define _UNICODE
#elif defined(_UNICODE) && !defined(UNICODE)
    #define UNICODE
#endif

#include <tchar.h>
#include <windows.h>
#include <stdio.h>
#include <math.h>

#include "resource.h"

#define NUM_MATRIZES 2
#define M1_X_POS 10
#define M1_Y_POS 30
#define M2_X_POS 680
#define M2_Y_POS 30
#define M_WIDTH 640
#define M_HEIGHT 320
#define M_FIELD_WIDTH 32
#define M_FIELD_HEIGHT 16
#define MAX_CHAR_SIZE 8
#define MAX_PRECISION 2

#define M_X_POS(index) M##index##_X_POS
#define M_Y_POS(index) M##index##_Y_POS


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

typedef struct selec {
    int index;
    int x;
    int y;
}gm_select;


void inserir_dado_ordenado(nodo **p ,float dado,int x ,int y ,int max_x ,int max_y);
float procurar(nodo *aux, int x, int y);

