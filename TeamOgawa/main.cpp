// ���C������ [main.cpp]

//------------------------------------------------
// �C���N���[�h�t�@�C��
//------------------------------------------------
#include "main.h"
#include "manager.h"
#include "debugproc.h"

//------------------------------------------------
// �}�N����`
//------------------------------------------------
#define CLASS_NAME "AppClass"	//�E�B���h�E�̃N���X��
#define WINDOW_NAME "������Re"		//�E�B���h�E�̃L���v�V������

//------------------------------------------------
// �v���g�^�C�v�錾
//------------------------------------------------
LRESULT CALLBACK WndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);

//------------------------------------------------
// ���C������
//------------------------------------------------
int APIENTRY WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
#ifdef _DEBUG
	//�������[���[�N���o
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
	int nCountFPS = 0;	//FPS�J�E���^�[
#endif // _DEBUG
							//�E�B���h�E�N���X�̓o�^
	RegisterClassEx(&wcex);

	//�w�肵���N���C�A���g�̈���m�ۂ��邽�߂ɕK�v�ȃE�B���h�E���W���v�Z
	AdjustWindowRect(&rect, WS_OVERLAPPEDWINDOW, false);

	//�E�B���h�E�̍쐬
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

	//�}�l�[�W���̐���
	pManager = new CManager;
	pManager->Init(hInstance, hWnd, TRUE);

	//����\��ݒ�
	timeBeginPeriod(1);

	//�t���[���J�E���g������
	dwExecLastTime =
		dwFPSLastTime = timeGetTime();
	dwCurrentTime =
		dwFrameCount = 0;

	//�E�B���h�E�̕\��
	ShowWindow(hWnd, nCmdShow);
	UpdateWindow(hWnd);

	//���b�Z�[�W���[�v
	while (1)
	{
		if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
		{
			if (msg.message == WM_QUIT)
			{
				//PostQuitMessage()���Ă΂ꂽ�烋�[�v�I��
				break;
			}
			else
			{
				//���b�Z�[�W�̖|��ƃf�B�X�p�b�`
				TranslateMessage(&msg);
				DispatchMessage(&msg);
			}
		}
		else
		{
			dwCurrentTime = timeGetTime();
			if ((dwCurrentTime - dwFPSLastTime) >= 500) //0.5�b���ƂɎ��s
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

				//�}�l�[�W���̍X�V����
				pManager->Update();
				//�}�l�[�W���̕`�揈��
				pManager->Draw();
#ifdef _DEBUG
				CDebugProc::Print("FPS : %d\n", nCountFPS);
#endif // _DEBUG
				dwFrameCount++;
			}
		}
	}

	//�E�B���h�E�N���X�̓o�^������
	UnregisterClass(CLASS_NAME, wcex.hInstance);

	//����\��߂�
	timeEndPeriod(1);

	//�}�l�[�W���[�̔j��
	if (pManager)
	{
		pManager->Uninit();
		delete pManager;
		pManager = NULL;
	}
	return (int)msg.wParam;
}

//------------------------------------------------
// �v���V�[�W��
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