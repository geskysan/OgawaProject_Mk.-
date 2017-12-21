// メイン処理 [main.cpp]

//------------------------------------------------
// インクルードファイル
//------------------------------------------------
#include "main.h"
#include "manager.h"
#include "debugproc.h"

//------------------------------------------------
// マクロ定義
//------------------------------------------------
#define CLASS_NAME "AppClass"	//ウィンドウのクラス名
#define WINDOW_NAME "美女釣Re"		//ウィンドウのキャプション名

//------------------------------------------------
// プロトタイプ宣言
//------------------------------------------------
LRESULT CALLBACK WndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);

//------------------------------------------------
// メイン処理
//------------------------------------------------
int APIENTRY WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
#ifdef _DEBUG
	//メモリーリーク検出
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
#endif
	
	WNDCLASSEX wcex =
	{
		sizeof(WNDCLASSEX),
		CS_CLASSDC,
		WndProc,
		0,
		0,
		hInstance,
		NULL,
		LoadCursor(NULL,IDC_ARROW),
		(HBRUSH)(COLOR_WINDOW + 1),
		NULL,
		CLASS_NAME,
		NULL
	};
	RECT rect = { 0,0,SCREEN_WIDTH,SCREEN_HEIGHT };
	HWND hWnd;
	MSG msg;
	DWORD dwExecLastTime;
	DWORD dwFPSLastTime;
	DWORD dwCurrentTime;
	DWORD dwFrameCount;
	CManager *pManager;

#ifdef _DEBUG
	int nCountFPS = 0;	//FPSカウンター
#endif // _DEBUG
							//ウィンドウクラスの登録
	RegisterClassEx(&wcex);

	//指定したクライアント領域を確保するために必要なウィンドウ座標を計算
	AdjustWindowRect(&rect, WS_OVERLAPPEDWINDOW, false);

	//ウィンドウの作成
	hWnd = CreateWindow(CLASS_NAME,
		WINDOW_NAME,
		WS_OVERLAPPEDWINDOW,
		CW_USEDEFAULT,
		CW_USEDEFAULT,
		(rect.right - rect.left),
		(rect.bottom - rect.top),
		NULL,
		NULL,
		hInstance,
		NULL);

	//マネージャの生成
	pManager = new CManager;
	pManager->Init(hInstance, hWnd, TRUE);

	//分解能を設定
	timeBeginPeriod(1);

	//フレームカウント初期化
	dwExecLastTime =
		dwFPSLastTime = timeGetTime();
	dwCurrentTime =
		dwFrameCount = 0;

	//ウィンドウの表示
	ShowWindow(hWnd, nCmdShow);
	UpdateWindow(hWnd);

	//メッセージループ
	while (1)
	{
		if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
		{
			if (msg.message == WM_QUIT)
			{
				//PostQuitMessage()が呼ばれたらループ終了
				break;
			}
			else
			{
				//メッセージの翻訳とディスパッチ
				TranslateMessage(&msg);
				DispatchMessage(&msg);
			}
		}
		else
		{
			dwCurrentTime = timeGetTime();
			if ((dwCurrentTime - dwFPSLastTime) >= 500) //0.5秒ごとに実行
			{
#ifdef _DEBUG
				nCountFPS	= dwFrameCount * 1000 / (dwCurrentTime - dwFPSLastTime);
#endif // _DEBUG
				dwFPSLastTime = dwCurrentTime;
				dwFrameCount = 0;
			}
			if ((dwCurrentTime - dwExecLastTime) >= (1000 / 60))
			{
				dwExecLastTime = dwCurrentTime;

				//マネージャの更新処理
				pManager->Update();
				//マネージャの描画処理
				pManager->Draw();
#ifdef _DEBUG
				CDebugProc::Print("FPS : %d\n", nCountFPS);
#endif // _DEBUG
				dwFrameCount++;
			}
		}
	}

	//ウィンドウクラスの登録を解除
	UnregisterClass(CLASS_NAME, wcex.hInstance);

	//分解能を戻す
	timeEndPeriod(1);

	//マネージャーの破棄
	if (pManager)
	{
		pManager->Uninit();
		delete pManager;
		pManager = NULL;
	}
	return (int)msg.wParam;
}

//------------------------------------------------
// プロシージャ
//------------------------------------------------
LRESULT CALLBACK WndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	switch (uMsg)
	{
	case WM_CREATE:
		break;

	case WM_DESTROY:
		PostQuitMessage(0);
		break;

	case WM_KEYDOWN:
		switch (wParam)
		{
		case VK_ESCAPE:
			DestroyWindow(hWnd);
			break;
		}
		break;

	default:
		return DefWindowProc(hWnd, uMsg, wParam, lParam);
		break;
	}
	return 0;
}