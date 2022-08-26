// GhibliButton.cpp : アプリケーションのエントリ ポイントを定義します。
//

#include "framework.h"
#include "GhibliButton.h"

#define MAX_LOADSTRING 100

// グローバル変数:
HINSTANCE hInst;                                // 現在のインターフェイス
WCHAR szTitle[MAX_LOADSTRING];                  // タイトル バーのテキスト
WCHAR szWindowClass[MAX_LOADSTRING];            // メイン ウィンドウ クラス名
LPPICTURE lp_Picture;

// このコード モジュールに含まれる関数の宣言を転送します:
ATOM                MyRegisterClass(HINSTANCE hInstance);
BOOL                InitInstance(HINSTANCE, int);
LRESULT CALLBACK    WndProc(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK    About(HWND, UINT, WPARAM, LPARAM);

int APIENTRY wWinMain(_In_ HINSTANCE hInstance,
                     _In_opt_ HINSTANCE hPrevInstance,
                     _In_ LPWSTR    lpCmdLine,
                     _In_ int       nCmdShow)
{
    UNREFERENCED_PARAMETER(hPrevInstance);
    UNREFERENCED_PARAMETER(lpCmdLine);

    // TODO: ここにコードを挿入してください。

    // グローバル文字列を初期化する
    LoadStringW(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
    LoadStringW(hInstance, IDC_GHIBLIBUTTON, szWindowClass, MAX_LOADSTRING);
    MyRegisterClass(hInstance);

    // アプリケーション初期化の実行:
    if (!InitInstance (hInstance, nCmdShow))
    {
        return FALSE;
    }

    HACCEL hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_GHIBLIBUTTON));

    MSG msg;

    // メイン メッセージ ループ:
    while (GetMessage(&msg, nullptr, 0, 0))
    {
        if (!TranslateAccelerator(msg.hwnd, hAccelTable, &msg))
        {
            TranslateMessage(&msg);
            DispatchMessage(&msg);
        }
    }

    return (int) msg.wParam;
}



//
//  関数: MyRegisterClass()
//
//  目的: ウィンドウ クラスを登録します。
//
ATOM MyRegisterClass(HINSTANCE hInstance)
{
    WNDCLASSEXW wcex;

    wcex.cbSize = sizeof(WNDCLASSEX);

    wcex.style          = CS_HREDRAW | CS_VREDRAW;
    wcex.lpfnWndProc    = WndProc;
    wcex.cbClsExtra     = 0;
    wcex.cbWndExtra     = 0;
    wcex.hInstance      = hInstance;
    wcex.hIcon          = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_GHIBLIBUTTON));
    wcex.hCursor        = LoadCursor(nullptr, IDC_ARROW);
    wcex.hbrBackground  = (HBRUSH)(COLOR_WINDOW+1);
    wcex.lpszMenuName   = MAKEINTRESOURCEW(IDC_GHIBLIBUTTON);
    wcex.lpszClassName  = szWindowClass;
    wcex.hIconSm        = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));

    return RegisterClassExW(&wcex);
}

//
//   関数: InitInstance(HINSTANCE, int)
//
//   目的: インスタンス ハンドルを保存して、メイン ウィンドウを作成します
//
//   コメント:
//
//        この関数で、グローバル変数でインスタンス ハンドルを保存し、
//        メイン プログラム ウィンドウを作成および表示します。
//
BOOL InitInstance(HINSTANCE hInstance, int nCmdShow)
{
   hInst = hInstance; // グローバル変数にインスタンス ハンドルを格納する

   HWND hWnd = CreateWindowW(szWindowClass, szTitle, WS_OVERLAPPEDWINDOW,
      CW_USEDEFAULT, 0, CW_USEDEFAULT, 0, nullptr, nullptr, hInstance, nullptr);

   if (!hWnd)
   {
      return FALSE;
   }

   ShowWindow(hWnd, nCmdShow);
   UpdateWindow(hWnd);

   return TRUE;
}

//
//  関数: LoadPictureResource(LPCTSTR, LPCTSTR)
//
//  目的: リソースから画像を読み込みます。
//
//
void LoadPictureResource(LPCTSTR lpName, LPCTSTR lpType)
{
    HRSRC hRsrc = FindResource(0, lpName, lpType);
    DWORD dwFileSize = SizeofResource(0, hRsrc);
    LPVOID pvData = NULL;
    HGLOBAL hGlobal = GlobalAlloc(GMEM_MOVEABLE, dwFileSize);
    pvData = GlobalLock(hGlobal);
    CopyMemory(pvData, LockResource(LoadResource(0, hRsrc)), dwFileSize);
    GlobalUnlock(hGlobal);
    LPSTREAM pstm = NULL;
    HRESULT hr = CreateStreamOnHGlobal(hGlobal, TRUE, &pstm);
    if (lp_Picture) {
        lp_Picture->Release();
        lp_Picture = nullptr;
    }
    hr = OleLoadPicture(pstm, dwFileSize, FALSE, IID_IPicture, (LPVOID*)&lp_Picture);
    pstm->Release();
}

//
//  関数: WndProc(HWND, UINT, WPARAM, LPARAM)
//
//  目的: メイン ウィンドウのメッセージを処理します。
//
//  WM_COMMAND  - アプリケーション メニューの処理
//  WM_PAINT    - メイン ウィンドウを描画する
//  WM_DESTROY  - 中止メッセージを表示して戻る
//
//
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    static HWND hButton[11];
    static LPCWSTR lpszButtonName[] = { L"すばらしい！", L"ほう..", L"またねっ", L"ＯＫ", L"ハハハハッ", L"いいね！", L"ありがとう①", L"フフフ", L"なるほど", L"ほほぅ", L"ありがとう②", L"ゴォォォ・・・",L"やなヤツやなヤツ",L"♩♪♩♩♫♪",L"！",L"いいよ",L"おっと",L"ごめんね",L"またね"};
    static INT nImageID[] = { IDB_BITMAP7, IDB_BITMAP8, IDB_BITMAP9, IDB_BITMAP6, IDB_BITMAP2, IDB_BITMAP3, IDB_BITMAP5, IDB_BITMAP4, IDB_BITMAP11, IDB_BITMAP1, IDB_BITMAP10, IDB_BITMAP12, IDB_BITMAP13, IDB_BITMAP14, IDB_BITMAP15, IDB_BITMAP16, IDB_BITMAP17, IDB_BITMAP18, IDB_BITMAP19 };
    switch (message)
    {
    case WM_CREATE:
        for (int i = 0; i < 18; i++) {
            hButton[i] = CreateWindow(L"BUTTON", lpszButtonName[i], WS_VISIBLE | WS_CHILD, 10 + 110 * i, 10, 100, 32, hWnd, (HMENU)(1000 + nImageID[i]), ((LPCREATESTRUCT)lParam)->hInstance, 0);
        }
        LoadPictureResource(MAKEINTRESOURCE(nImageID[0]), TEXT("JPG"));
        break;
    case WM_COMMAND:
        {
            int wmId = LOWORD(wParam);
            // 選択されたメニューの解析:
            for (auto imageid : nImageID) {
                if (1000 + imageid == wmId) {
                    LoadPictureResource(MAKEINTRESOURCE(imageid), TEXT("JPG"));
                    InvalidateRect(hWnd, 0, TRUE);
                    return 0;
                }
            }
            switch (wmId)
            {
            case IDM_ABOUT:
                DialogBox(hInst, MAKEINTRESOURCE(IDD_ABOUTBOX), hWnd, About);
                break;
            case IDM_EXIT:
                DestroyWindow(hWnd);
                break;
            default:
                return DefWindowProc(hWnd, message, wParam, lParam);
            }
        }
        break;
    case WM_PAINT:
        {
            PAINTSTRUCT ps;
            HDC hdc = BeginPaint(hWnd, &ps);
            if (lp_Picture) {
                long hmWidth;
                long hmHeight;
                lp_Picture->get_Width(&hmWidth);
                lp_Picture->get_Height(&hmHeight);
                int nWidth = MulDiv(hmWidth, GetDeviceCaps(hdc, LOGPIXELSX), 2540);
                int nHeight = MulDiv(hmHeight, GetDeviceCaps(hdc, LOGPIXELSY), 2540);
                RECT rect;
                GetClientRect(hWnd, &rect);
                lp_Picture->Render(hdc, 10, 50, nWidth, nHeight, 0, hmHeight, hmWidth, -hmHeight, &rect);
            }
            EndPaint(hWnd, &ps);
        }
        break;
    case WM_DESTROY:
        if (lp_Picture) {
            lp_Picture->Release();
            lp_Picture = nullptr;
        }
        PostQuitMessage(0);
        break;
    default:
        return DefWindowProc(hWnd, message, wParam, lParam);
    }
    return 0;
}

// バージョン情報ボックスのメッセージ ハンドラーです。
INT_PTR CALLBACK About(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
    UNREFERENCED_PARAMETER(lParam);
    switch (message)
    {
    case WM_INITDIALOG:
        return (INT_PTR)TRUE;

    case WM_COMMAND:
        if (LOWORD(wParam) == IDOK || LOWORD(wParam) == IDCANCEL)
        {
            EndDialog(hDlg, LOWORD(wParam));
            return (INT_PTR)TRUE;
        }
        break;
    }
    return (INT_PTR)FALSE;
}
