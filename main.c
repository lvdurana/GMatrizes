#if defined(UNICODE) && !defined(_UNICODE)
    #define _UNICODE
#elif defined(_UNICODE) && !defined(UNICODE)
    #define UNICODE
#endif


#include "f_base.c"

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

void desenhar_dado(HDC hdc, matriz *mat, int pos_x, int pos_y){
    RECT rect;
    char text[15];

    rect.top = pos_y+1;
    rect.left = pos_x+1;
    rect.right = pos_x+M_FIELD_WIDTH-1;
    rect.bottom = pos_y+M_FIELD_HEIGHT-1;
    sprintf(text,"%d",666);

    DrawText(hdc, text, -1, &rect, DT_WORDBREAK|DT_CENTER);


}

void desenhar_dados_matriz(HDC hdc, matriz *mat, int pos_x, int pos_y){
    int i,j;
    for(i=0;i<mat->dim_y;i++){
        for(j=0;j<mat->dim_x;j++){
            desenhar_dado(hdc, mat, pos_x+j*M_FIELD_WIDTH,pos_y+i*M_FIELD_HEIGHT);
            //printf("%d\n",M_FIELD_WIDTH);

        };
    };



}


/*  Declare Windows procedure  */
LRESULT CALLBACK WindowProcedure (HWND, UINT, WPARAM, LPARAM);

/*  Make the class name into a global variable  */
TCHAR szClassName[ ] = _T("CodeBlocksWindowsApp");
//Global variables
HBITMAP matriz_base = NULL;

HWND box1 = NULL;
HWND mat_box1, mat_box2;


int WINAPI WinMain (HINSTANCE hThisInstance,
                     HINSTANCE hPrevInstance,
                     LPSTR lpszArgument,
                     int nCmdShow)
{
    HWND hwnd;               /* This is the handle for our window */
    MSG messages;            /* Here messages to the application are saved */
    WNDCLASSEX wincl;        /* Data structure for the windowclass */

    //Extra Windows



    /* The Window structure */
    wincl.hInstance = hThisInstance;
    wincl.lpszClassName = szClassName;
    wincl.lpfnWndProc = WindowProcedure;      /* This function is called by windows */
    wincl.style = CS_DBLCLKS;                 /* Catch double-clicks */
    wincl.cbSize = sizeof (WNDCLASSEX);

    /* Use default icon and mouse-pointer */
    wincl.hIcon = LoadIcon (NULL, IDI_APPLICATION);
    wincl.hIconSm = (HICON)LoadImage(GetModuleHandle(NULL), MAKEINTRESOURCE(IDI_MYICON), IMAGE_ICON, 16, 16, 0);
    wincl.hCursor = LoadCursor (NULL, IDC_ARROW);
    wincl.lpszMenuName = MAKEINTRESOURCE(IDR_MYMENU);                 /* No menu */
    wincl.cbClsExtra = 0;                      /* No extra bytes after the window class */
    wincl.cbWndExtra = 0;                      /* structure or the window instance */
    /* Use Windows's default colour as the background of the window */
    wincl.hbrBackground = (HBRUSH) COLOR_BACKGROUND;

    /* Register the window class, and if it fails quit the program */
    if (!RegisterClassEx (&wincl))
        return 0;

    /* The class is registered, let's create the program*/
    hwnd = CreateWindowEx (
           0,                   /* Extended possibilites for variation */
           szClassName,         /* Classname */
           _T("Code::Blocks Template Windows App"),       /* Title Text */
           WS_OVERLAPPEDWINDOW, /* default window */
           CW_USEDEFAULT,       /* Windows decides the position */
           CW_USEDEFAULT,       /* where the window ends up on the screen */
           544,                 /* The programs width */
           375,                 /* and height in pixels */
           HWND_DESKTOP,        /* The window is a child-window to desktop */
           NULL,                /* No menu */
           hThisInstance,       /* Program Instance handler */
           NULL                 /* No Window Creation data */
           );





    /* Make the window visible on the screen */
    ShowWindow (hwnd, nCmdShow);





    /* Run the message loop. It will run until GetMessage() returns 0 */
    while (GetMessage (&messages, NULL, 0, 0))
    {
        /* Translate virtual-key messages into character messages */
        TranslateMessage(&messages);
        /* Send message to WindowProcedure */
        DispatchMessage(&messages);
    }

    /* The program return-value is 0 - The value that PostQuitMessage() gave */
    printf("%d",IDR_MYMENU);
    return messages.wParam;

}


BOOL CALLBACK box1proc(HWND hwnd, UINT Message, WPARAM wParam, LPARAM lParam)
{
    switch(Message)
    {
        case WM_CREATE:
            {
            SCROLLINFO info;
            info.cbSize = sizeof(SCROLLINFO);
            info.fMask = SIF_ALL;
            info.nMin = 0;
            info.nMax = 255;
            info.nPage = 200;
            info.nPos = 0;
            info.nTrackPos = 0;
            SetScrollInfo(GetDlgItem(hwnd,4002),SB_CTL,&info,1);
            };
            break;

        case WM_COMMAND:
            switch(LOWORD(wParam))
            {
                //case IDC_PRESS:
                //    MessageBox(hwnd, "Hi!", "This is a message",
                //        MB_OK | MB_ICONEXCLAMATION);
                //break;


            }
        break;
        case WM_PAINT:
            {

            SCROLLINFO info;

            GetScrollInfo(GetDlgItem(hwnd,4002),SB_CTL,&info);
            //printf("%d\n",info.nTrackPos);

            }
            break;
        case WM_DESTROY:
            PostQuitMessage (0);       /* send a WM_QUIT to the message queue */
            break;
        default:
            return FALSE;
    }
    return TRUE;
}


/*  This function is called by the Windows function DispatchMessage()  */

LRESULT CALLBACK WindowProcedure (HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam)
{



    switch (message)                  /* handle the messages */
    {
        case WM_CREATE:


            //Criar caixas das matrizes
            //mat_box1 = CreateWindowEx (0,"Static", _T("M1"),SS_BITMAP|SS_CENTERIMAGE|WS_CHILD,M1_X_POS,M1_Y_POS,M_WIDTH,M_HEIGHT,hwnd,NULL,GetModuleHandle(NULL),NULL);
            //ShowWindow(mat_box1, SW_SHOW);

            //box1 = CreateDialog(GetModuleHandle(NULL),MAKEINTRESOURCE(1001),hwnd,box1proc);
            if(box1 != NULL)
                ShowWindow(box1, SW_SHOW);
            SendMessage(box1,WM_CREATE,0,0);

            matriz_base = LoadBitmap(GetModuleHandle(NULL), MAKEINTRESOURCE(SM_BMP_MATRIZ));
            if(matriz_base == NULL)
                MessageBox(hwnd, "Could not load SM_BMP_MATRIZ!", "Error", MB_OK | MB_ICONEXCLAMATION);

            SendMessage(hwnd,WM_PAINT,0,0);

            break;

        case WM_PAINT:
        {
            PAINTSTRUCT ps;

            HDC hdc = BeginPaint(hwnd, &ps);


            /*HDC hdc = BeginPaint(hwnd, &ps);

            HDC hdcMem = CreateCompatibleDC(hdc);
            HBITMAP hbmOld = (HBITMAP)SelectObject(hdcMem, matriz_base);

            GetObject(matriz_base, sizeof(bm), &bm);

            BitBlt(hdc, 0, 0, bm.bmWidth, bm.bmHeight, hdcMem, 0, 0, SRCCOPY);

            SelectObject(hdcMem, hbmOld);
            DeleteDC(hdcMem);

            EndPaint(hwnd, &ps);*/
            matriz mat;
            mat.dim_x = 20;
            mat.dim_y = 20;
            desenhar_matriz(hwnd,hdc,&mat,M1_X_POS,M1_Y_POS);
            desenhar_matriz(hwnd,hdc,&mat,M2_X_POS,M2_Y_POS);
            desenhar_dados_matriz(hdc,&mat,M1_X_POS,M1_Y_POS);
            desenhar_dados_matriz(hdc,&mat,M2_X_POS,M2_Y_POS);

            //desenhar_matriz(hwnd,hdc,&mat,40,M1_Y_POS);

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
                    SetBkMode(GetDC(hwnd), TRANSPARENT);
                    //DrawText(GetDC(hwnd), "Oi Cassiano", -1, prc, DT_WORDBREAK);
                    TextOut(GetDC(hwnd),0,30,"Oi Cassianooooooooooooooooooo",20);
                break;
            }
            break;
        case WM_LBUTTONDOWN:
            printf("%d %d\n",HIWORD(lParam),LOWORD(lParam));
        break;
        case WM_DESTROY:
            PostQuitMessage (0);       /* send a WM_QUIT to the message queue */
            break;
        default:                      /* for messages that we don't deal with */
            return DefWindowProc (hwnd, message, wParam, lParam);
    }

    return 0;
};


