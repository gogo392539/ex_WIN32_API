#include "stdafx.h"

C_MYWIN* C_MYWIN::m_pMyWin = nullptr;

C_MYWIN::C_MYWIN() :
	m_hInstance(NULL),
	m_hWnd(NULL)
{
}

void C_MYWIN::createWin()
{
	if (!m_pMyWin)
		m_pMyWin = new C_MYWIN();
}

C_MYWIN * C_MYWIN::getWin()
{
	return m_pMyWin;
}

void C_MYWIN::releaseWin()
{
	if (m_pMyWin)
	{
		delete m_pMyWin;
		m_pMyWin = nullptr;
	}
}

bool C_MYWIN::init(HINSTANCE hInstance)
{
	//������ Ŭ���� ���
	WNDCLASSEXW wcex;
	wcex.cbSize = sizeof(WNDCLASSEX);
	wcex.style = CS_HREDRAW | CS_VREDRAW;
	wcex.lpfnWndProc = wndProc;
	wcex.cbClsExtra = 0;
	wcex.cbWndExtra = 0;
	wcex.hInstance = hInstance;
	wcex.hIcon = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_WIN32APIEX));
	wcex.hCursor = LoadCursor(nullptr, IDC_ARROW);
	wcex.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
	wcex.lpszMenuName = 0;
	wcex.lpszClassName = L"className";
	wcex.hIconSm = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));
	RegisterClassExW(&wcex);


	//������ ����
	m_hWnd = CreateWindowW(L"className", nullptr, WS_OVERLAPPEDWINDOW,
		CW_USEDEFAULT, 0, CW_USEDEFAULT, 0, nullptr, nullptr, hInstance, nullptr);

	if (!m_hWnd)
		return false;

	//�ʱ�ȭ �۾��� ���⿡
	m_hInstance = hInstance;

	ShowWindow(m_hWnd, SW_SHOWDEFAULT);
	UpdateWindow(m_hWnd);

	return true;
}

void C_MYWIN::updateMsg()
{
	MSG msg = {};

	// �⺻ �޽��� �����Դϴ�.
	while (GetMessage(&msg, nullptr, 0, 0))
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}
}

void C_MYWIN::release()
{
}

LRESULT C_MYWIN::wndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	return m_pMyWin->myProc(hWnd, message, wParam, lParam);
}

LRESULT C_MYWIN::myProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	switch (message)
	{
	case WM_PAINT:
	{
		PAINTSTRUCT ps;
		HDC hdc = BeginPaint(hWnd, &ps);
		// TODO: ���⿡ hdc�� ����ϴ� �׸��� �ڵ带 �߰��մϴ�.
		EndPaint(hWnd, &ps);
	}
	break;
	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	default:
		return DefWindowProc(hWnd, message, wParam, lParam);
	}
	return 0;
}
