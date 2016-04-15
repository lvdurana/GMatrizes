#include <tchar.h>
#include <windows.h>
#include <stdio.h>
#include "resource.h"

#define M1_X_POS 30
#define M1_Y_POS 30
#define M2_X_POS 680
#define M2_Y_POS 30
#define M_WIDTH 640
#define M_HEIGHT 320
#define M_FIELD_WIDTH 32
#define M_FIELD_HEIGHT 16

typedef struct mat{
    int dim_x;
    int dim_y;

}matriz;

typedef struct jmat {
    matriz mat;
    HBITMAP bmp_mat;



}j_matriz;


