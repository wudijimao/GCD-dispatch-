/*
windows�汾
*/
#include "stdafx.h"
#include "BaseWindow.h"
#include "WindowsManager.h"
#include "XImage.h"
#include "XRect.h"
#include "GlobalStatus.h"
#include "XRenderFactory.h"

//��ʱ
#include "GDIRender.h"


using namespace XResource;
XWindow::XWindow(const XRect &rect)
: mRect(rect)
{
	mCtrls.GetRoot()->Rect(0, 0, rect.Width(), rect.Height());
	mCtrls.GetRoot()->BelongWnd(this);
}
const MouseStatusStruct& XWindow::MouseStauts()
{
	return mMouseStatus;
}
void XWindow::OnDraw()
{
	if (mNeedReDraw)
	{
		mNeedReDraw = false;
		mCtrls.GetRoot()->Draw(*mRender);
		mCanvas->Update();
	}
}
XWindow::~XWindow()
{
	//TODO:��Ҫ�����߳�ͬ��
	//WindowsManager::GetInstanc().UnRegist(mHwnd);
	delete this->mRender;
}

XControls::ControlManager& XWindow::Contrls()
{
	return mCtrls;
}

//HWND XWindow::Hwnd()
//{
//	return mHwnd;
//}
void XWindow::Drag(LPARAM lParam)
{
	ReleaseCapture();
	SendMessage(mHwnd, WM_NCLBUTTONDOWN, 2, 0);//SendMessage�Ῠסֱ���϶����������ִ�к�ߵ�PostMessage
	//SendMessage(hwnd, WM_SYSCOMMAND, SC_MOVE | HTCAPTION, 0); //��������ϱ�һ��Ч��һ��
	//TODO::�϶��������Ͷ�ʧ��WM_LBUTTONUP   wParam����Ϊ�������ʱ�� ϣ���ܻ�ȡ��ǰ��
	PostMessage(mHwnd, WM_LBUTTONUP, mMouseStatus.mWParam, lParam);
}
void XWindow::NeedReDraw()
{
	mNeedReDraw = true;
}
const int TimerMS = 50;
const int CaretShowMs = 500;

HWND XWindow::Create(HINSTANCE hInstance, int iCmdShow)
{
	mAppNameClass = L"appNameClass";
	WNDCLASSEX wndclass;
	wndclass.cbSize = sizeof(WNDCLASSEX);
	wndclass.style = CS_HREDRAW | CS_VREDRAW/* | WS_EX_TOOLWINDOW | WS_EX_TOPMOST*/;
	wndclass.lpfnWndProc = WindowsManager::WndProc;
	wndclass.cbClsExtra = 0;
	wndclass.cbWndExtra = 0;
	wndclass.hInstance = hInstance;
	wndclass.hIcon = LoadIcon(NULL, IDI_APPLICATION);
	wndclass.hCursor = LoadCursor(NULL, IDC_ARROW);
	wndclass.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);
	wndclass.lpszMenuName = NULL;
	wndclass.lpszClassName = mAppNameClass.c_str();
	wndclass.hIconSm = LoadIcon(NULL, IDI_WINLOGO);


	if (!RegisterClassEx(&wndclass))
	{
		MessageBox(NULL, TEXT("This program requires Windows NT!"),
			mAppNameClass.c_str(), MB_ICONERROR);
		DWORD a = ::GetLastError();
		return NULL;
	}

	mHwnd = CreateWindowEx(
		/*WS_EX_TOPMOST | */WS_EX_LAYERED,
		mAppNameClass.c_str(),
		L"",
		WS_POPUP | WS_MINIMIZEBOX,
		mRect.X(),
		mRect.Y(),
		mRect.Width(),
		mRect.Height(),
		NULL,
		NULL,
		hInstance,
		this);
	if (!::IsWindow(mHwnd))
	{
		DWORD a = ::GetLastError();
		assert("δ�ɹ���������" && 0);
		return NULL;
	}

	ShowWindow(mHwnd, iCmdShow);
	UpdateWindow(mHwnd);

	SetTimer(mHwnd, 0, TimerMS, NULL);
	//������� �ֲ㴰�ڲ����� ֻ���Ի�,�����Ƿ�Ӱ�����뷨��λ���أ���
	if (!CreateCaret(mHwnd, NULL, 500, 500))
	{
		assert(L"�������ʧ��");
	}
	return mHwnd;
};

LRESULT XWindow::RealWndProc(HWND hwnd, UINT iMsg, WPARAM wParam, LPARAM lParam)
{
	static int addMs = 0;
	switch (iMsg)
	{
	case WM_TIMER:
		addMs += TimerMS;
		if (addMs >= CaretShowMs)
		{
			addMs = 0;
			GlobalStatus::GetInstance().IsCaretShow(!GlobalStatus::GetInstance().IsCaretShow());
		}
		OnDraw();
		return 0;
	case WM_CREATE:
		mCanvas = XRenderFactory::getRender(hwnd);
		mRender = new GDIRender();
		mRender->Init(mCanvas);
		return 0;
	case WM_SIZE:
		mCanvas->ReSize(LOWORD(lParam), HIWORD(lParam));
		return 0;
	case WM_PAINT:
		//ϵͳ�й�
		return 0;
	case WM_DESTROY:
		delete mCanvas;
		WindowsManager::GetInstanc().UnRegist(mHwnd);
		PostQuitMessage(0);
		return 0;
	case WM_ERASEBKGND:
		return 0;

	case WM_LBUTTONDOWN:
		SetCapture(hwnd);
		goto SENDMOUSEEVENT;//���񴰿��������Ϣ��ͬһʱ��ֻ����һ����������Ϊ������
	case WM_LBUTTONUP:
		ReleaseCapture();
	//�������¼�
	case WM_MOUSEWHEEL:
	case WM_MOUSEMOVE:
	{
					 SENDMOUSEEVENT:
						 mMouseStatus.SetMouseStatus(wParam, lParam);
						 mCtrls.GetRoot()->MouseEvent(iMsg, mMouseStatus.X, mMouseStatus.Y);
						 OnDraw();
						 return 0;
	}
	case WM_KEYDOWN:
	{
		mCtrls.GetRoot()->KeyBoardEvent(iMsg, wParam, lParam);
		OnDraw();
		mCanvas->Update();
		return 0;
	}
	//�����ƶ��¼�
	case WM_MOVE:
		//mRect.X((int)(short)LOWORD(lParam));
		//mRect.Y((int)(short)HIWORD(lParam));
		return 0;
	}
	return DefWindowProc(hwnd, iMsg, wParam, lParam);
}

const std::wstring& XWindow::ID()
{
	return mID;
}

void XWindow::ID(const std::wstring& id)
{
	mID = id;
}


const XRect& XWindow::Rect() const
{
	return mRect;
}


void XWindow::Rect(const XRect& rect)
{
	mRect = rect;
}
