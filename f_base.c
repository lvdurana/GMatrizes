#include "f_base.h"


void desenhar_matriz(HWND hwnd, HDC hdc, matriz *mat, int pos_x, int pos_y){

    HWND mat_base = LoadBitmap(GetModuleHandle(NULL), MAKEINTRESOURCE(SM_BMP_MATRIZ));
    if(mat_base == NULL)
        MessageBox(hwnd, "Could not load SM_BMP_MATRIZ!", "Error", MB_OK | MB_ICONEXCLAMATION);

    HDC hdcMem = CreateCompatibleDC(hdc);
    HBITMAP hbmOld = (HBITMAP)SelectObject(hdcMem, mat_base);
    int i,j;

    //Desenhar grade
    BitBlt(hdc, pos_x, pos_y, M_FIELD_WIDTH, M_FIELD_HEIGHT, hdcMem, 0, 0, SRCCOPY);
    for(i=1;i<mat->dim_x-1;i++)
        BitBlt(hdc, pos_x+M_FIELD_WIDTH*i, pos_y, M_FIELD_WIDTH, M_FIELD_HEIGHT, hdcMem, 32, 0, SRCCOPY);
    BitBlt(hdc, pos_x+M_FIELD_WIDTH*i, pos_y, M_FIELD_WIDTH, M_FIELD_HEIGHT, hdcMem, 64, 0, SRCCOPY);
    for(j=1;j<mat->dim_y-1;j++){
        BitBlt(hdc, pos_x, pos_y+M_FIELD_HEIGHT*j, M_FIELD_WIDTH, M_FIELD_HEIGHT, hdcMem, 0, 32, SRCCOPY);
        for(i=1;i<mat->dim_x-1;i++)
            BitBlt(hdc, pos_x+M_FIELD_WIDTH*i, pos_y+M_FIELD_HEIGHT*j, M_FIELD_WIDTH, M_FIELD_HEIGHT, hdcMem, 32, 32, SRCCOPY);
        BitBlt(hdc, pos_x+M_FIELD_WIDTH*i, pos_y+M_FIELD_HEIGHT*j, M_FIELD_WIDTH, M_FIELD_HEIGHT, hdcMem, 64, 32, SRCCOPY);
    }
    BitBlt(hdc, pos_x, pos_y+M_FIELD_HEIGHT*j, M_FIELD_WIDTH, M_FIELD_HEIGHT, hdcMem, 0, 64, SRCCOPY);
    for(i=1;i<mat->dim_x-1;i++)
        BitBlt(hdc, pos_x+M_FIELD_WIDTH*i, pos_y+M_FIELD_HEIGHT*j, M_FIELD_WIDTH, M_FIELD_HEIGHT, hdcMem, 32, 64, SRCCOPY);
    BitBlt(hdc, pos_x+M_FIELD_WIDTH*i, pos_y+M_FIELD_HEIGHT*j, M_FIELD_WIDTH, M_FIELD_HEIGHT, hdcMem, 64, 64, SRCCOPY);


    SelectObject(hdcMem, hbmOld);
    DeleteDC(hdcMem);




};

void desenhar_dado(HDC hdc, float dado, int pos_x, int pos_y){
    RECT rect;
    char text[15];

    rect.top = pos_y+1;
    rect.left = pos_x+1;
    rect.right = pos_x+M_FIELD_WIDTH-1;
    rect.bottom = pos_y+M_FIELD_HEIGHT-1;
    sprintf(text,"%.0f",dado);

    DrawText(hdc, text, -1, &rect, DT_WORDBREAK|DT_CENTER);


}

void desenhar_dados_matriz(HDC hdc, matriz *mat, int pos_x, int pos_y){
    int i,j;
    float *dados = mostrar_dados(mat->inicio,mat->dim_x,mat->dim_y);

    for(i=0;i<mat->dim_y;i++){
        for(j=0;j<mat->dim_x;j++){
            desenhar_dado(hdc, *(dados+i*mat->dim_y+j), pos_x+j*M_FIELD_WIDTH,pos_y+i*M_FIELD_HEIGHT);
            //printf("%d\n",M_FIELD_WIDTH);

        };
    };



}

void criar_botoes(HWND hwnd, HWND *buttons){
            //Criar caixas das matrizes
            buttons[0] = CreateWindow(
                "BUTTON",  // Predefined class; Unicode assumed
                "Somar",      // Button text
                WS_TABSTOP | WS_VISIBLE | WS_CHILD | BS_DEFPUSHBUTTON,  // Styles
                10,         // x position
                300,         // y position
                100,        // Button width
                100,        // Button height
                hwnd,     // Parent window
                NULL,       // No menu.
                GetModuleHandle(NULL),//(HINSTANCE)GetWindowLong(hwnd, GWL_HINSTANCE),
                NULL);      // Pointer not needed.



}

void fechar_janela(HWND *hwnd){
    *hwnd = NULL;
}

int verificar_cursor(gm_select *sel, int cur_x,int cur_y, int ox_mat, int oy_mat, int dim_x_mat, int dim_y_mat){

    cur_x = (int)floor((float)(cur_x-ox_mat)/M_FIELD_WIDTH);
    cur_y = (int)floor((float)(cur_y-oy_mat)/M_FIELD_HEIGHT);
    /*cur_x-=ox_mat;
    cur_y-=oy_mat;

    cur_x/=M_FIELD_WIDTH;
    cur_y/=M_FIELD_HEIGHT;*/
    //printf("%d %d\n",cur_x, cur_y);

    if(cur_x<dim_x_mat && cur_x >= 0)
        if(cur_y<dim_y_mat && cur_y >= 0){
            sel->x = cur_x;
            sel->y = cur_y;
            return 0;
        };
    return 1;

}

int verificar_cursor_matrizes(gm_select *sel, matriz *matrizes, int cur_x, int cur_y){
    //for(i=0;i<NUM_MATRIZES;i++){
        if(!verificar_cursor(sel,cur_x,cur_y,M1_X_POS,M1_Y_POS,(matrizes+0)->dim_x,(matrizes+0)->dim_y)){
            sel->index = 0;
            return 0;
        }
        else{
            if(!verificar_cursor(sel,cur_x,cur_y,M2_X_POS,M2_Y_POS,(matrizes+1)->dim_x,(matrizes+1)->dim_y)){
                sel->index = 1;
                return 0;
            };
        };
    //}
    return 1;

};

