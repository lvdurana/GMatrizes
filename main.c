#include "f_base.h"




/*  Declare Windows procedure  */
LRESULT CALLBACK WindowProcedure (HWND, UINT, WPARAM, LPARAM);

/*  Make the class name into a global variable  */
TCHAR szClassName[ ] = _T("CodeBlocksWindowsApp");
//Global variables
HBITMAP matriz_base = NULL;

HWND box1,box2;
HWND mat_box1, mat_box2;
HWND h_buttons[5]; //button
matriz mat[2];


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
        //case WM_CREATE:
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

            PAINTSTRUCT ps;

            HDC hdc = BeginPaint(hwnd, &ps);

            matriz mat;
            mat.dim_x = 20;
            mat.dim_y = 20;
            desenhar_matriz(hwnd,hdc,&mat,M1_X_POS,M1_Y_POS);

            desenhar_dados_matriz(hdc,&mat,M1_X_POS,M1_Y_POS);


            //desenhar_matriz(hwnd,hdc,&mat,40,M1_Y_POS);

            EndPaint(hwnd, &ps);

            }
            break;
        case WM_CLOSE:
            DestroyWindow(hwnd);        /* send a WM_QUIT to the message queue */
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
        //case WM_CREATE:
        case WM_COMMAND:
            switch(LOWORD(wParam))
            {
                case IDOK:
                    MessageBox(hwnd, "Hi!", "This is a message",
                        MB_OK | MB_ICONEXCLAMATION);
                break;


            }
        break;
        case WM_PAINT:
            {

            }
            break;
        case WM_CLOSE:
            DestroyWindow(hwnd);        /* send a WM_QUIT to the message queue */
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
            {
                int i;
                nodo  *d[2];
                matriz materia;
                float l = 2.015;
                for(i=0;i<2;i++){
                    mat[i].inicio = NULL;
                    mat[i].dim_x = 5;
                    mat[i].dim_y = 5;
                    d[i]=&(mat[i].inicio);


                    materia.inicio = NULL;
                    materia.dim_x = 5;
                    materia.dim_y = 5;

                    printf("%f\n",l);
                    inserir_dado_ordenado(d[i],32,2,3,mat[i].dim_x,mat[i].dim_y);
                    //printf("%f",mat[0].inicio->dado);
                }
            }

            criar_botoes(hwnd, h_buttons);

            matriz_base = LoadBitmap(GetModuleHandle(NULL), MAKEINTRESOURCE(SM_BMP_MATRIZ));
            if(matriz_base == NULL)
                MessageBox(hwnd, "Could not load SM_BMP_MATRIZ!", "Error", MB_OK | MB_ICONEXCLAMATION);

            SendMessage(hwnd,WM_PAINT,0,0);

            break;

        case WM_PAINT:
        {
            PAINTSTRUCT ps;

            HDC hdc = BeginPaint(hwnd, &ps);


            desenhar_matriz(hwnd,hdc,&mat[0],M1_X_POS,M1_Y_POS);
            desenhar_matriz(hwnd,hdc,&mat[0],M2_X_POS,M2_Y_POS);
            desenhar_dados_matriz(hdc,&mat[0],M1_X_POS,M1_Y_POS);
            desenhar_dados_matriz(hdc,&mat[0],M2_X_POS,M2_Y_POS);

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
                case BN_CLICKED:
                    printf("%s","click");
                    box1 = CreateDialog(GetModuleHandle(NULL),MAKEINTRESOURCE(1001),hwnd,box1proc);
            if(box1 != NULL)
                ShowWindow(box1, SW_SHOW);
            SendMessage(box1,WM_CREATE,0,0);
                    //lParam=handle

                break;
            }
            break;
        case WM_LBUTTONDOWN:
            printf("%d %d\n",HIWORD(lParam),LOWORD(lParam));
            box2 = CreateDialog(GetModuleHandle(NULL),MAKEINTRESOURCE(1002),hwnd,box_data_proc);
            SendDlgItemMessage(box2,4001,WM_SETTEXT,0,"oizinho");
            //SetWindowText(GetDlgItem(box2,4001),"oizinho");
        break;
        case WM_DESTROY:
            PostQuitMessage (0);       /* send a WM_QUIT to the message queue */
            break;
        default:                      /* for messages that we don't deal with */
            return DefWindowProc (hwnd, message, wParam, lParam);
    }

    return 0;
};


