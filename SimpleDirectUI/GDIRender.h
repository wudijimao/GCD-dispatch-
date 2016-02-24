#pragma once
#pragma warning( disable: 4251 )
#include "IXRender.h"
#include <boost/signals2.hpp>
#include <windows.h>
#include <gdiplus.h>

class GDIPlusInitHelper
{
public:
	GDIPlusInitHelper();
	~GDIPlusInitHelper();
private:
	Gdiplus::GdiplusStartupInput mGdiplusStartupInput;
	ULONG_PTR mGdiplusToken;
};


//�ṩ���ߡ���Բ����ͼ���������ߵȱ�ݷ�����ֱ���ں�̨�����ϻ���
class SIMPLEDIRECTUI_API GDIRender : public IXRender
{
	friend class GDIRender;
public:
	GDIRender();
	~GDIRender();
	GDIRender(HWND hwnd);//��ʱ
	bool Init(IXCanvas *canvas);
	void Creat();
	void ReSize(int width, int height);
	void Paint();
	void Destory();
	void DrawBackGround(Gdiplus::Color &color, const XResource::XRect &xRect);
	//���Ƽ�ʹ�ã�ֱ�Ӳ���graphics��û��ͳһ�Ľӿ�
	Gdiplus::Graphics& GetGraphics()
	{
		return *mBkgGraphics;
	}
	void DrawLine(int x1, int y1, int x2, int y2)
	{
		Gdiplus::Pen pen(Gdiplus::Color(255, 0, 0, 0));
		mBkgGraphics->DrawLine(&pen, x1, y1, x2, y2);
	}
	//��Ҫ���Ƶľ�������
	void DrawImage(XResource::XImage &img, const XResource::XRect &rect);
	void DrawImage(Gdiplus::Bitmap &img, const XResource::XRect &rect, int x, int y);
	void DrawString(const std::wstring &text, const XResource::XRect &xRect);
	void DrawString(const std::wstring &text, const XResource::XRect &xRect, Gdiplus::StringAlignment align);
	void DrawString(const XResource::XText &text, const XResource::XRect &xRect);
	virtual XResource::XRect MeasureString(const XResource::XText &text, const XResource::XRect &xRect);
	virtual XResource::XRect MeasureString(const std::wstring &text);
private:
	bool mIsCreated;
	//��ͼ�����С
	int  mWidth, mHeight;
protected:
	Gdiplus::Graphics *mBkgGraphics;
private:
	HWND mHwnd;
	HDC mMemDC;
	HBITMAP mBitMap;
private:
	static GDIPlusInitHelper sGdiPlus;
};