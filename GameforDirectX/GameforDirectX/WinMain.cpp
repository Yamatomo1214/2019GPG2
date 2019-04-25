#include <windows.h>

LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);
char szClassNme[] = "ウィンドウクラス・ネーム";

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


	// クライアント領域確保処理
	AdjustWindowRect(&rect,windowStyle,FALSE); // クライアント領域を確保する

	// クライアント領域のサイズから適切なウィンドウサイズを求める
	SIZE windowSize;
	windowSize.cx = rect.right - rect.left; // 正しいウィンドウサイズ(1296)
	windowSize.cy = rect.bottom - rect.top; // 807

	// センタリング処理
	// ウィンドウが画面中央に配置されるような左上隅の位置を求める
	POINT windowPos;
	windowPos.x = (GetSystemMetrics(SM_CXSCREEN) - windowSize.cx) / 2; // GetSystemMetrics(SM_CXSCREEN)で自分自身の解像度が分かる
	windowPos.y = (GetSystemMetrics(SM_CYSCREEN) - windowSize.cy) / 2;

	hWnd = CreateWindow(szClassNme,
		"猫でもわかるプログラミング",
		WS_OVERLAPPEDWINDOW,
		windowPos.x,
		windowPos.y,
		windowSize.cx,
		windowSize.cy,
		NULL,
		NULL,
		hInstance,
		NULL);
	ShowWindow(hWnd, nCmdShow);
	UpdateWindow(hWnd);
	while (GetMessage(&msg, NULL, 0, 0)) {
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}
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
