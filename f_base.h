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

//Dados da matriz
#define NUM_MATRIZES 2
#define MAX_CHAR_SIZE 8
#define MAX_PRECISION 2
#define MAX_X_DIMENSION 15
#define MAX_Y_DIMENSION 20

//Dados da interface
#define M_FIELD_WIDTH 32
#define M_FIELD_HEIGHT 16
#define M_MAX_WIDTH (MAX_X_DIMENSION*M_FIELD_WIDTH)
#define M_MAX_HEIGHT (MAX_Y_DIMENSION*M_FIELD_HEIGHT)

#define NUM_BUTTONS 12
#define B1_WIDTH 96
#define B1_HEIGHT 32
#define B2_WIDTH 32
#define B2_HEIGHT 32
#define B3_WIDTH 128
#define B3_HEIGHT 48

#define X_PADDING_1 10
#define X_PADDING_2 10
#define X_PADDING_3 20
#define Y_PADDING_1 20
#define Y_PADDING_2 20
#define Y_PADDING_3 20
#define Y_PADDING_4 32
#define B_X_PADDING 10
#define B_Y_PADDING 10

#define M1_X_POS X_PADDING_1
#define M1_Y_POS Y_PADDING_1
#define M2_X_POS (X_PADDING_1 + M_MAX_WIDTH + X_PADDING_2)
#define M2_Y_POS Y_PADDING_1

#define WINDOW_WIDTH (X_PADDING_1 + X_PADDING_2 + X_PADDING_3 + (M_MAX_WIDTH*2))
#define WINDOW_HEIGHT (Y_PADDING_1 + Y_PADDING_2 + Y_PADDING_3 + Y_PADDING_4 + M_MAX_HEIGHT + B1_HEIGHT + B3_HEIGHT)

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

void desenhar_matriz(HWND hwnd, HDC hdc, matriz *mat, int pos_x, int pos_y);
void desenhar_dado(HDC hdc, float dado, int pos_x, int pos_y);
void desenhar_dados_matriz(HDC hdc, matriz *mat, int pos_x, int pos_y);
void criar_botoes(HWND hwnd, HWND *buttons);
void verificar_botao_pressionado(int *act_win, LPARAM lParam, matriz *mat, HWND *h_buttons, HWND hwnd, gm_select *sel);
void fechar_janela(HWND *hwnd);
int verificar_cursor(gm_select *sel, int cur_x,int cur_y, int ox_mat, int oy_mat, int dim_x_mat, int dim_y_mat);
int verificar_cursor_matrizes(gm_select *sel, matriz *matrizes, int cur_x, int cur_y);



nodo * Cria_Nodo();
void inserir_dado_ordenado(nodo **p,float dado,int x ,int y ,int max_x ,int max_y);
void liberar_memoria(nodo *mat);
retornar_valor(int x, int y,int max_y);
float *mostrar_dados(nodo *lista,int max_x,int max_y);
char imprime_lista_encadeada(nodo *N);
nodo *somar_matriz(nodo *aux1, nodo *aux2,int max_col,int max_lin);
nodo *subtrair_matriz(nodo *aux1, nodo *aux2,int max_col,int max_lin);
nodo *transpor_matriz(nodo *mat1,int max_x,int max_y);
float procurar(nodo *aux, int x, int y);
nodo *multiplicar_matriz(nodo *mat1, nodo *mat2, int max_x1, int max_y1,int max_x2, int max_y2);

BOOL CALLBACK box1proc(HWND hwnd, UINT Message, WPARAM wParam, LPARAM lParam);
BOOL CALLBACK diag_proc(HWND hwnd, UINT Message, WPARAM wParam, LPARAM lParam);
BOOL CALLBACK box_data_proc(HWND hwnd, UINT Message, WPARAM wParam, LPARAM lParam);
BOOL CALLBACK edit_dim_proc(HWND hwnd, UINT Message, WPARAM wParam, LPARAM lParam);
LRESULT CALLBACK WindowProcedure (HWND, UINT, WPARAM, LPARAM);


