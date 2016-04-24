#include "f_base.h"


void desenhar_matriz(HWND hwnd, HDC hdc, matriz *mat, int pos_x, int pos_y){

    HWND mat_base = LoadBitmap(GetModuleHandle(NULL), MAKEINTRESOURCE(GM_BMP_MATRIZ));
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
        BitBlt(hdc, pos_x, pos_y+M_FIELD_HEIGHT*j, M_FIELD_WIDTH, M_FIELD_HEIGHT, hdcMem, 0, 16, SRCCOPY);
        for(i=1;i<mat->dim_x-1;i++)
            BitBlt(hdc, pos_x+M_FIELD_WIDTH*i, pos_y+M_FIELD_HEIGHT*j, M_FIELD_WIDTH, M_FIELD_HEIGHT, hdcMem, 32, 16, SRCCOPY);
        BitBlt(hdc, pos_x+M_FIELD_WIDTH*i, pos_y+M_FIELD_HEIGHT*j, M_FIELD_WIDTH, M_FIELD_HEIGHT, hdcMem, 64, 16, SRCCOPY);
    }
    BitBlt(hdc, pos_x, pos_y+M_FIELD_HEIGHT*j, M_FIELD_WIDTH, M_FIELD_HEIGHT, hdcMem, 0, 32, SRCCOPY);
    for(i=1;i<mat->dim_x-1;i++)
        BitBlt(hdc, pos_x+M_FIELD_WIDTH*i, pos_y+M_FIELD_HEIGHT*j, M_FIELD_WIDTH, M_FIELD_HEIGHT, hdcMem, 32, 32, SRCCOPY);
    BitBlt(hdc, pos_x+M_FIELD_WIDTH*i, pos_y+M_FIELD_HEIGHT*j, M_FIELD_WIDTH, M_FIELD_HEIGHT, hdcMem, 64, 32, SRCCOPY);


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
    if(dado != 0){
        HWND mat_cor = LoadBitmap(GetModuleHandle(NULL), MAKEINTRESOURCE(GM_BMP_MATRIZ2));
        HDC hdcMem = CreateCompatibleDC(hdc);
        HBITMAP hbmOld = (HBITMAP)SelectObject(hdcMem, mat_cor);
        BitBlt(hdc, pos_x+1, pos_y, M_FIELD_WIDTH-2, M_FIELD_HEIGHT, hdcMem, 0, 0, SRCCOPY);
        //SetTextColor(hdc,RGB(0,0,0));
    }


    DrawText(hdc, text, -1, &rect, DT_WORDBREAK|DT_CENTER);
}

void desenhar_dados_matriz(HDC hdc, matriz *mat, int pos_x, int pos_y){
    int i,j;
    float *dados = mostrar_dados(mat->inicio, mat->dim_x, mat->dim_y);

    SetBkMode(hdc, TRANSPARENT);
    for(i=0;i<mat->dim_y;i++){
        for(j=0;j<mat->dim_x;j++){
            desenhar_dado(hdc, *(dados+i*mat->dim_x+j), pos_x+j*M_FIELD_WIDTH,pos_y+i*M_FIELD_HEIGHT);
        };
    };
}

void desenhar_dados_diagonal(HDC hdc, matriz *mat, int pos_x, int pos_y){
    int i,dim;
    if(mat->dim_x>mat->dim_y)
        dim = mat->dim_y;
    else
        dim = mat->dim_x;

    float *dados = mostrar_dados_diagonal(mat->inicio, dim);


    SetBkMode(hdc, TRANSPARENT);
    for(i=0;i<dim;i++){
        desenhar_dado(hdc, *(dados+i), pos_x+i*M_FIELD_WIDTH,pos_y+i*M_FIELD_HEIGHT);
    };
}

void criar_botoes(HWND hwnd, HWND *buttons){
    //Estabelecer posições origem
    int m_y_point = M_MAX_HEIGHT+M1_Y_POS+Y_PADDING_2;
    int x_pos = M1_X_POS;
    int B3_area_x = M2_X_POS - (X_PADDING_2 / 2) - (B3_WIDTH*4 + B_X_PADDING*3) / 2;

    int B3_area_y = m_y_point + Y_PADDING_3 + B1_HEIGHT;


    buttons[0] = CreateWindow("BUTTON", "Transpor",WS_TABSTOP | WS_VISIBLE | WS_CHILD | BS_DEFPUSHBUTTON,
        x_pos, m_y_point, B1_WIDTH, B1_HEIGHT,
        hwnd, NULL, GetModuleHandle(NULL), NULL);
    x_pos += B1_WIDTH + B_X_PADDING;

    buttons[1] = CreateWindow("BUTTON", "Diagonal",WS_TABSTOP | WS_VISIBLE | WS_CHILD | BS_DEFPUSHBUTTON,
        x_pos, m_y_point, B1_WIDTH, B1_HEIGHT,
        hwnd, NULL, GetModuleHandle(NULL), NULL);
    x_pos += B1_WIDTH + B_X_PADDING;

    buttons[2] = CreateWindow("BUTTON", "Alterar dim",WS_TABSTOP | WS_VISIBLE | WS_CHILD | BS_DEFPUSHBUTTON,
        x_pos, m_y_point, B1_WIDTH, B1_HEIGHT,
        hwnd, NULL, GetModuleHandle(NULL), NULL);
    x_pos += B1_WIDTH + B_X_PADDING;

    buttons[3] = CreateWindow("BUTTON", "Limpar",WS_TABSTOP | WS_VISIBLE | WS_CHILD | BS_DEFPUSHBUTTON,
        x_pos, m_y_point, B1_WIDTH, B1_HEIGHT,
        hwnd, NULL, GetModuleHandle(NULL), NULL);
    x_pos = M2_X_POS+M_MAX_WIDTH - B1_WIDTH;

    buttons[4] = CreateWindow("BUTTON", "Transpor",WS_TABSTOP | WS_VISIBLE | WS_CHILD | BS_DEFPUSHBUTTON,
        x_pos, m_y_point, B1_WIDTH, B1_HEIGHT,
        hwnd, NULL, GetModuleHandle(NULL), NULL);
    x_pos -= B1_WIDTH + B_X_PADDING;

    buttons[5] = CreateWindow("BUTTON", "Diagonal",WS_TABSTOP | WS_VISIBLE | WS_CHILD | BS_DEFPUSHBUTTON,
        x_pos, m_y_point, B1_WIDTH, B1_HEIGHT,
        hwnd, NULL, GetModuleHandle(NULL), NULL);
    x_pos -= B1_WIDTH + B_X_PADDING;

    buttons[6] = CreateWindow("BUTTON", "Alterar dim",WS_TABSTOP | WS_VISIBLE | WS_CHILD | BS_DEFPUSHBUTTON,
        x_pos, m_y_point, B1_WIDTH, B1_HEIGHT,
        hwnd, NULL, GetModuleHandle(NULL), NULL);
    x_pos -= B1_WIDTH + B_X_PADDING;

    buttons[7] = CreateWindow("BUTTON", "Limpar",WS_TABSTOP | WS_VISIBLE | WS_CHILD | BS_DEFPUSHBUTTON,
        x_pos, m_y_point, B1_WIDTH, B1_HEIGHT,
        hwnd, NULL, GetModuleHandle(NULL), NULL);

    buttons[8] = CreateWindow("BUTTON", "Somar",WS_TABSTOP | WS_VISIBLE | WS_CHILD | BS_DEFPUSHBUTTON,
        B3_area_x, B3_area_y, B3_WIDTH, B3_HEIGHT,
        hwnd, NULL, GetModuleHandle(NULL), NULL);
    B3_area_x += B3_WIDTH + B_X_PADDING;

    buttons[9] = CreateWindow("BUTTON", "Subtrair",WS_TABSTOP | WS_VISIBLE | WS_CHILD | BS_DEFPUSHBUTTON,
        B3_area_x, B3_area_y, B3_WIDTH, B3_HEIGHT,
        hwnd, NULL, GetModuleHandle(NULL), NULL);
    B3_area_x += B3_WIDTH + B_X_PADDING;

    buttons[10] = CreateWindow("BUTTON", "Multiplicar",WS_TABSTOP | WS_VISIBLE | WS_CHILD | BS_DEFPUSHBUTTON,
        B3_area_x, B3_area_y, B3_WIDTH, B3_HEIGHT,
        hwnd, NULL, GetModuleHandle(NULL), NULL);
    B3_area_x += B3_WIDTH + B_X_PADDING;

    buttons[11] = CreateWindow("BUTTON", "Inverter posições",WS_TABSTOP | WS_VISIBLE | WS_CHILD | BS_DEFPUSHBUTTON,
        B3_area_x, B3_area_y, B3_WIDTH, B3_HEIGHT,
        hwnd, NULL, GetModuleHandle(NULL), NULL);


}

void verificar_botao_pressionado(int *act_win, LPARAM lParam, matriz *mat, HWND *h_buttons, HWND hwnd, gm_select *sel){

    if(lParam == h_buttons[8]){
        //Somar matrizes
        mat[2].inicio = somar_matriz(mat[0].inicio,mat[1].inicio,mat[0].dim_x,mat[0].dim_y);
        mat[2].dim_x = mat[0].dim_x;
        mat[2].dim_y = mat[0].dim_y;
        *act_win = CreateDialog(GetModuleHandle(NULL),MAKEINTRESOURCE(1001),hwnd,box1proc);
        if(*act_win != NULL){
            ShowWindow(*act_win, SW_SHOW);
            SendMessage(*act_win,WM_CREATE,0,0);
        };
    }
    else
    if(lParam == h_buttons[9]){
        //Subtrair matrizes
        mat[2].inicio = subtrair_matriz(mat[0].inicio,mat[1].inicio,mat[0].dim_x,mat[0].dim_y);
        mat[2].dim_x = mat[0].dim_x;
        mat[2].dim_y = mat[0].dim_y;
        *act_win = CreateDialog(GetModuleHandle(NULL),MAKEINTRESOURCE(1001),hwnd,box1proc);
        if(*act_win != NULL){
            ShowWindow(*act_win, SW_SHOW);
            SendMessage(*act_win,WM_CREATE,0,0);
        };
    }
    else
    if(lParam == h_buttons[10]){
        //Multiplicar matrizes
        mat[2].inicio = multiplicar_matriz(mat[0].inicio,mat[1].inicio,mat[0].dim_x,mat[0].dim_y,mat[1].dim_x,mat[1].dim_y);
        mat[2].dim_x = mat[0].dim_x;
        mat[2].dim_y = mat[0].dim_y;
        *act_win = CreateDialog(GetModuleHandle(NULL),MAKEINTRESOURCE(1001),hwnd,box1proc);
        if(*act_win != NULL){
            ShowWindow(*act_win, SW_SHOW);
            SendMessage(*act_win,WM_CREATE,0,0);
        };
    }
    else
    if(lParam == h_buttons[11]){
        //Trocar lugares
        mat[2].inicio = mat[0].inicio;
        mat[2].dim_x = mat[0].dim_x;
        mat[2].dim_y = mat[0].dim_y;
        mat[0].inicio = mat[1].inicio;
        mat[0].dim_x = mat[1].dim_x;
        mat[0].dim_y = mat[1].dim_y;
        mat[1].inicio = mat[2].inicio;
        mat[1].dim_x = mat[2].dim_x;
        mat[1].dim_y = mat[2].dim_y;
    }
    else
    if(lParam == h_buttons[0]){
        //Transpor matriz 1
        mat[0].inicio = transpor_matriz(mat[0].inicio,mat[0].dim_x,mat[0].dim_y);
        mat[2].dim_x = mat[0].dim_x;
        mat[0].dim_x = mat[0].dim_y;
        mat[0].dim_y = mat[2].dim_x;
    }
    else
    if(lParam == h_buttons[4]){
        //Transpor matriz 2
        mat[1].inicio = transpor_matriz(mat[1].inicio,mat[1].dim_x,mat[1].dim_y);
        mat[2].dim_x = mat[1].dim_x;
        mat[1].dim_x = mat[1].dim_y;
        mat[1].dim_y = mat[2].dim_x;
    }
    else
    if(lParam == h_buttons[1]){
        //Diagonal da matriz 1
        mat[2].inicio = mat[0].inicio;
        mat[2].dim_x = mat[0].dim_x;
        mat[2].dim_y = mat[0].dim_y;
        *act_win = CreateDialog(GetModuleHandle(NULL),MAKEINTRESOURCE(1001),hwnd,diag_proc);
        if(*act_win != NULL){
            ShowWindow(*act_win, SW_SHOW);
            SendMessage(*act_win,WM_CREATE,0,0);
        };
    }
    else
    if(lParam == h_buttons[5]){
        //Diagonal da matriz 2
        mat[2].inicio = mat[1].inicio;
        mat[2].dim_x = mat[1].dim_x;
        mat[2].dim_y = mat[1].dim_y;
        *act_win = CreateDialog(GetModuleHandle(NULL),MAKEINTRESOURCE(1001),hwnd,diag_proc);
        if(*act_win != NULL){
            ShowWindow(*act_win, SW_SHOW);
            SendMessage(*act_win,WM_CREATE,0,0);
        };

    }
    else
    if(lParam == h_buttons[2]){
        //Alterar dimensão da matriz 1
        char *col, *lin;
        col = (char*)malloc(sizeof(char)*MAX_CHAR_SIZE);
        lin = (char*)malloc(sizeof(char)*MAX_CHAR_SIZE);

        sprintf(col,"%d", mat[0].dim_x);
        sprintf(lin,"%d", mat[0].dim_y);

        sel->index = 0;
        *act_win = CreateDialog(GetModuleHandle(NULL),MAKEINTRESOURCE(1003),hwnd,edit_dim_proc);
        SendDlgItemMessage(*act_win,4001,WM_SETTEXT,0,col);
        SendDlgItemMessage(*act_win,4003,WM_SETTEXT,0,lin);
        SendDlgItemMessage(*act_win,4001,WM_PAINT,0,0);
        SendDlgItemMessage(*act_win,4003,WM_PAINT,0,0);

    }
    else
    if(lParam == h_buttons[6]){
        //Alterar dimensão da matriz 2
        char *col, *lin;
        col = (char*)malloc(sizeof(char)*MAX_CHAR_SIZE);
        lin = (char*)malloc(sizeof(char)*MAX_CHAR_SIZE);

        sprintf(col,"%d", mat[1].dim_x);
        sprintf(lin,"%d", mat[1].dim_y);

        sel->index = 1;
        *act_win = CreateDialog(GetModuleHandle(NULL),MAKEINTRESOURCE(1003),hwnd,edit_dim_proc);
        SendDlgItemMessage(*act_win,4001,WM_SETTEXT,0,col);
        SendDlgItemMessage(*act_win,4003,WM_SETTEXT,0,lin);
        SendDlgItemMessage(*act_win,4001,WM_PAINT,0,0);
        SendDlgItemMessage(*act_win,4003,WM_PAINT,0,0);
    }
    else
    if(lParam == h_buttons[3]){
        //Limpar matriz 1
        mat[0].inicio = NULL;
        //liberar_memoria(mat[0].inicio);

    }
    else
    if(lParam == h_buttons[7]){
        //Limpar matriz 1
        mat[1].inicio = NULL;
        //liberar_memoria(mat[0].inicio);

    };




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
            if(!verificar_cursor(sel,cur_x,cur_y,M2_X_POS , M2_Y_POS,(matrizes+1)->dim_x,(matrizes+1)->dim_y)){
                sel->index = 1;
                return 0;
            };
        };
    //}
    return 1;

};

