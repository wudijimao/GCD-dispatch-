#pragma once
#include "ControlManager.h"
#include "IXRender.h"
#include "XRect.h"
#include "IBaseWindow.h"
#include <boost/signals2.hpp>
class SIMPLEDIRECTUI_API XWindow : public IXWindow
{
public:
	XWindow(const XResource::XRect &rect);
	XWindow::~XWindow();
	///ע�⣺���ڴ���ʧ��ʱ�᷵��NULL
	HWND Create(HINSTANCE hInstance, int iCmdShow);
	XControls::ControlManager& Contrls();
	void OnDraw();
	//HWND Hwnd();
	void Drag(LPARAM lParam);
	virtual void NeedReDraw();
	virtual const MouseStatusStruct& MouseStauts();
	virtual const std::wstring& ID();
	virtual void ID(const std::wstring& id);
	virtual const XResource::XRect& Rect() const;
	virtual void Rect(const XResource::XRect& rect);
private:
protected:
	//һ����������ֻ��һ���ؼ���
	XControls::ControlManager mCtrls;
	//����һ����ͼ�������������пؼ�
	IXRender *mRender;

	std::wstring mAppNameClass;
	HINSTANCE mHInstance;
	HWND mHwnd;//������
	XResource::XRect mRect;//�����С��λ��
	MouseStatusStruct mMouseStatus;
	bool mNeedReDraw = true;
	std::wstring mID;
public:
	LRESULT RealWndProc(HWND hwnd, UINT iMsg, WPARAM wParam, LPARAM lParam);
private:
	//������������,��ֹ���⿽����δ��windowsManager��ע��Ĵ���ʵ��
	XWindow(const XWindow &){}//Ĭ�Ͽ�������  
	XWindow & operator=(const XWindow &){ return *this; }//Ĭ�ϸ�ֵ�����
};