#include <windows.h>
#include <thread>
#include <chrono>
LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);
char szClassNme[] = "�E�B���h�E�N���X�E�l�[��";

bool isGameRarning; // �Q�[�����I�����邩�ǂ�������

// �Q�[���X���b�h
void GameThreadEntryPoint()
{
	// DirectX�̏�����
	auto previousTime = std::chrono::steady_clock::now(); // �O��̎���
	while (isGameRarning)
	{
		auto currentTime = std::chrono::steady_clock::now(); // ���݂̎���
		auto elaosedTime = currentTime - previousTime; // �o�ߎ���
		if (elaosedTime > std::chrono::microseconds(16666)) // 16�~���b�Ԋu�ŃQ�[���������s����
		{

			// �Q�[����ʂ̃����_�����O


			// �Q�[��(�t���[��)�̍X�V
			previousTime = currentTime;
		}
	}
}



int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPreInst,
	LPSTR lpszCmdLine, int nCmdShow)
{
	HWND hWnd;
	MSG msg;
	WNDCLASS myProg;
	if (!hPreInst) {
		myProg.style = CS_HREDRAW | CS_VREDRAW;
		myProg.lpfnWndProc = WndProc;
		myProg.cbClsExtra = 0;
		myProg.cbWndExtra = 0;
		myProg.hInstance = hInstance;
		myProg.hIcon = NULL;
		myProg.hCursor = LoadCursor(NULL, IDC_ARROW);
		myProg.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);
		myProg.lpszMenuName = NULL;
		myProg.lpszClassName = szClassNme;
		if (!RegisterClass(&myProg))
			return FALSE;
	}

	static const int GameResolutionWidth = 1280;
	static const int GameResolutionHeight = 768;

	DWORD windowStyle = WS_OVERLAPPEDWINDOW;
	RECT rect;
	rect.left = 0;
	rect.top = 0;
	rect.right = GameResolutionWidth;
	rect.bottom = GameResolutionHeight;


	// �N���C�A���g�̈�m�ۏ���
	AdjustWindowRect(&rect,windowStyle,FALSE); // �N���C�A���g�̈���m�ۂ���

	// �N���C�A���g�̈�̃T�C�Y����K�؂ȃE�B���h�E�T�C�Y�����߂�
	SIZE windowSize;
	windowSize.cx = rect.right - rect.left; // �������E�B���h�E�T�C�Y(1296)
	windowSize.cy = rect.bottom - rect.top; // 807

	// �Z���^�����O����
	// �E�B���h�E����ʒ����ɔz�u�����悤�ȍ�����̈ʒu�����߂�
	POINT windowPos;
	windowPos.x = (GetSystemMetrics(SM_CXSCREEN) - windowSize.cx) / 2; // GetSystemMetrics(SM_CXSCREEN)�Ŏ������g�̉𑜓x��������
	windowPos.y = (GetSystemMetrics(SM_CYSCREEN) - windowSize.cy) / 2;

	hWnd = CreateWindow(szClassNme,
		"�L�ł��킩��v���O���~���O",
		WS_OVERLAPPEDWINDOW,
		windowPos.x,
		windowPos.y,
		windowSize.cx,
		windowSize.cy,
		NULL,
		NULL,
		hInstance,
		NULL);
	
	// �Q�[���p�X���b�h�̋N����Ԃɂ���
	isGameRarning = true;

	// �Q�[���p�̃X���b�h�̍쐬
	std::thread gameThread(GameThreadEntryPoint);

	ShowWindow(hWnd, nCmdShow);
	UpdateWindow(hWnd);
	while (GetMessage(&msg, NULL, 0, 0)) {
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}
	// �Q�[���p�X���b�h�𒆒f����
	isGameRarning = false;

	// �Q�[���X���b�h�̏I����҂�
	gameThread.join();

	return (msg.wParam);
}

LRESULT CALLBACK WndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	switch (msg) {
	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	default:
		return(DefWindowProc(hWnd, msg, wParam, lParam));
	}
	return (0L);
}
