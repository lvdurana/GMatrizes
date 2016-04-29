#include "f_base.h"

//Variáveis globais
TCHAR szClassName[] = _T("GMatrizes");
HWND h_buttons[NUM_BUTTONS];
matriz mat[NUM_MATRIZES+1];
HWND gm_active_window = NULL;
HWND main_window;
gm_select gm_selected;



int WINAPI WinMain (HINSTANCE hThisInstance,
                     HINSTANCE hPrevInstance,
                     LPSTR lpszArgument,
                     int nCmdShow)
{
    HWND hwnd;
    MSG messages;
    WNDCLASSEX wincl;

    wincl.hInstance = hThisInstance;
    wincl.lpszClassName = szClassName;
    wincl.lpfnWndProc = WindowProcedure;
    wincl.style = CS_DBLCLKS;
    wincl.cbSize = sizeof (WNDCLASSEX);
    wincl.hIcon = LoadIcon (NULL, IDI_APPLICATION);
    wincl.hIconSm = (HICON)LoadImage(GetModuleHandle(NULL), MAKEINTRESOURCE(IDI_MYICON), IMAGE_ICON, 16, 16, 0);
    wincl.hCursor = LoadCursor (NULL, IDC_ARROW);
    wincl.lpszMenuName = MAKEINTRESOURCE(IDR_MYMENU);
    wincl.cbClsExtra = 0;
    wincl.cbWndExtra = 0;
    wincl.hbrBackground = (HBRUSH) COLOR_BACKGROUND;

    if (!RegisterClassEx (&wincl))
        return 0;

    hwnd = CreateWindowEx (
           0,                   /* Extended possibilites for variation */
           szClassName,         /* Classname */
           _T("Gerenciador de Matrizes"),       /* Title Text */
           WS_OVERLAPPEDWINDOW, /* default window */
           CW_USEDEFAULT,       /* Windows decides the position */
           CW_USEDEFAULT,       /* where the window ends up on the screen */
           WINDOW_WIDTH,                 /* The programs width */
           WINDOW_HEIGHT,                 /* and height in pixels */
           HWND_DESKTOP,        /* The window is a child-window to desktop */
           NULL,                /* No menu */
           hThisInstance,       /* Program Instance handler */
           NULL                 /* No Window Creation data */
           );

    ShowWindow (hwnd, nCmdShow);
    main_window = hwnd;

    while (GetMessage (&messages, NULL, 0, 0))
    {
        TranslateMessage(&messages);
        DispatchMessage(&messages);
    }

    printf("%d",IDR_MYMENU);
    return messages.wParam;

}


BOOL CALLBACK box1proc(HWND hwnd, UINT Message, WPARAM wParam, LPARAM lParam)
{
    switch(Message)
    {
        case WM_PAINT:
            {
                PAINTSTRUCT ps;
                HDC hdc = BeginPaint(hwnd, &ps);
                desenhar_matriz(hwnd,hdc,&mat[2],M1_X_POS,M1_Y_POS);
                desenhar_dados_matriz(hdc,&mat[2],M1_X_POS,M1_Y_POS);
                EndPaint(hwnd, &ps);
            }
            break;
        case WM_CLOSE:
            DestroyWindow(hwnd);
            fechar_janela(&gm_active_window);
            break;
        default:
            return FALSE;
    }
    return TRUE;
}

BOOL CALLBACK diag_proc(HWND hwnd, UINT Message, WPARAM wParam, LPARAM lParam)
{
    switch(Message)
    {
        case WM_PAINT:
            {
                PAINTSTRUCT ps;
                HDC hdc = BeginPaint(hwnd, &ps);
                desenhar_matriz(hwnd,hdc,&mat[2],M1_X_POS,M1_Y_POS);
                desenhar_dados_diagonal(hdc,&mat[2],M1_X_POS,M1_Y_POS);
                EndPaint(hwnd, &ps);
            }
            break;
        case WM_CLOSE:
            DestroyWindow(hwnd);
            fechar_janela(&gm_active_window);
            break;
        default:
            return FALSE;
    }
    return TRUE;
}


BOOL CALLBACK box_data_proc(HWND hwnd, UINT Message, WPARAM wParam, LPARAM lParam)
{
    switch(Message)
    {
        case WM_COMMAND:
            switch(LOWORD(wParam))
            {

                case IDOK:
                    {
                        char *mione;
                        float dado;
                        mione = (char*)malloc(sizeof(char)*MAX_CHAR_SIZE);
                        GetWindowText(GetDlgItem(hwnd,4001),mione,MAX_CHAR_SIZE);
                        dado = atof(mione);
                        if(dado != 0)
                            inserir_dado_ordenado(&(mat[gm_selected.index].inicio),dado,gm_selected.x,gm_selected.y,mat[gm_selected.index].dim_x,mat[gm_selected.index].dim_y);
                        else
                            excluir_dado(&(mat[gm_selected.index].inicio), gm_selected.x, gm_selected.y);
                        SendMessage(hwnd,WM_CLOSE,0,0);
                        RedrawWindow(main_window, NULL, NULL, RDW_INVALIDATE | RDW_UPDATENOW);
                    }
                break;
                case IDCANCEL:
                    DestroyWindow(hwnd);
                    fechar_janela(&gm_active_window);
                break;
            }
        break;
        case WM_CLOSE:
            DestroyWindow(hwnd);
            fechar_janela(&gm_active_window);
            break;
        default:
            return FALSE;
    }
    return TRUE;
}

BOOL CALLBACK edit_dim_proc(HWND hwnd, UINT Message, WPARAM wParam, LPARAM lParam)
{
    switch(Message)
    {
        case WM_COMMAND:
            switch(LOWORD(wParam))
            {
                case IDOK:
                    {
                        char *col, *lin;
                        int x, y;
                        col = (char*)malloc(sizeof(char)*MAX_CHAR_SIZE);
                        lin = (char*)malloc(sizeof(char)*MAX_CHAR_SIZE);

                        GetWindowText(GetDlgItem(hwnd,4001),col,MAX_CHAR_SIZE);
                        GetWindowText(GetDlgItem(hwnd,4003),lin,MAX_CHAR_SIZE);
                        x = atoi(col);
                        y = atoi(lin);

                        if(x <= MAX_X_DIMENSION && x > 0 && y <= MAX_Y_DIMENSION && y > 0){
                            alterar_dimensao(&(mat[gm_selected.index].inicio), &(mat[gm_selected.index].dim_x) ,&(mat[gm_selected.index].dim_y) ,x, y);
                            SendMessage(hwnd,WM_CLOSE,0,0);
                            InvalidateRect(main_window,NULL,1);
                            UpdateWindow(main_window);
                            atualizar_botoes_permitidos(mat,h_buttons);

                        };
                    }
                break;
                case IDCANCEL:
                    DestroyWindow(hwnd);
                    fechar_janela(&gm_active_window);
                break;
            }
        break;
        case WM_CLOSE:
            DestroyWindow(hwnd);
            fechar_janela(&gm_active_window);
            break;
        default:
            return FALSE;
    }
    return TRUE;
}

LRESULT CALLBACK WindowProcedure (HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam)
{



    switch (message)
    {
        case WM_CREATE:
            {
                int i;
                nodo  *d[2];
                HWND matriz_base;
                for(i=0;i<2;i++){
                    mat[i].inicio = NULL;
                    mat[i].dim_x = 4;
                    mat[i].dim_y = 3;
                    d[i]=&(mat[i].inicio);

                    inserir_dado_ordenado(d[i],32,2,3,mat[i].dim_x,mat[i].dim_y);

                }


                criar_botoes(hwnd, h_buttons);
                atualizar_botoes_permitidos(mat,h_buttons);

                matriz_base = LoadBitmap(GetModuleHandle(NULL), MAKEINTRESOURCE(GM_BMP_MATRIZ));
                if(matriz_base == NULL)
                    MessageBox(hwnd, "Could not load SM_BMP_MATRIZ!", "Error", MB_OK | MB_ICONEXCLAMATION);
                UpdateWindow(hwnd);
            };
            break;

        case WM_PAINT:
        {
            PAINTSTRUCT ps;

            HDC hdc = BeginPaint(hwnd, &ps);


            desenhar_matriz(hwnd,hdc,&mat[0],M1_X_POS,M1_Y_POS);
            desenhar_matriz(hwnd,hdc,&mat[1],M2_X_POS,M2_Y_POS);
            desenhar_dados_matriz(hdc,&mat[0],M1_X_POS,M1_Y_POS);
            desenhar_dados_matriz(hdc,&mat[1],M2_X_POS,M2_Y_POS);
            EndPaint(hwnd, &ps);
        }
        break;
        case WM_COMMAND:
            switch(LOWORD(wParam))
            {
                case ID_FILE_EXIT:
                    PostMessage(hwnd,WM_CLOSE,0,0);
                break;
                case ID_STUFF_GO:
                    debug_mostrar_matriz(mat[0].inicio);
                break;
                case ID_STUFF_M2:
                    debug_mostrar_matriz(mat[1].inicio);
                break;
                case BN_CLICKED:
                    if(!gm_active_window){
                        verificar_botao_pressionado(&gm_active_window,lParam,mat,h_buttons,hwnd,&gm_selected);
                        InvalidateRect(hwnd,NULL,1);
                        UpdateWindow(hwnd);
                    };

                break;
            }
            break;
        case WM_LBUTTONDOWN:
            {
                if(!gm_active_window){
                    if(!verificar_cursor_matrizes(&gm_selected,mat,LOWORD(lParam),HIWORD(lParam))){
                        char *dado;
                        dado = (char*)malloc(sizeof(char)*(MAX_CHAR_SIZE+MAX_PRECISION+2));
                        sprintf(dado,"%.*f",MAX_PRECISION,procurar(mat[gm_selected.index].inicio,gm_selected.x,gm_selected.y));
                        gm_active_window = CreateDialog(GetModuleHandle(NULL),MAKEINTRESOURCE(1002),hwnd,box_data_proc);
                        SendDlgItemMessage(gm_active_window,4001,WM_SETTEXT,0,dado);
                        SendDlgItemMessage(gm_active_window,4001,WM_PAINT,0,0);
                    };
                };
            }
        break;
        case WM_DESTROY:
            PostQuitMessage (0);
            break;
        default:
            return DefWindowProc (hwnd, message, wParam, lParam);
    }

    return 0;
};


