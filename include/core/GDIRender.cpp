#include "stdafx.hpp"
#include "GDICanvas.hpp"
#include "GDIRender.hpp"
using namespace Gdiplus;

#define TWO_PI (2.0 * 3.14159)
using namespace XResource;


GDIPlusInitHelper::GDIPlusInitHelper()
{
	//��ʼ��GDI+
	GdiplusStartup(&mGdiplusToken, &mGdiplusStartupInput, NULL);
}

GDIPlusInitHelper::~GDIPlusInitHelper()
{
	GdiplusShutdown(mGdiplusToken);
	
}
void abc()
{
	int a = 0;
}
GDIRender::GDIRender() : mIsCreated(false)
{
	static GDIPlusInitHelper helper;
}

GDIRender::GDIRender(HWND hwnd) : mIsCreated(false) {
	static GDIPlusInitHelper helper;
	mHwnd = hwnd;
}

GDIRender::~GDIRender()
{
	Destory();
}
void GDIRender::Paint()
{
	HDC hdc = ::GetDC(mHwnd);
	RECT rct;
	GetWindowRect(mHwnd, &rct);
	POINT ptWinPos = { rct.left, rct.top };

	POINT    ptSrc = { 0, 0 };

	SIZE    sizeWindow = { mWidth, mHeight };

	BLENDFUNCTION    m_Blend;
	m_Blend.BlendOp = AC_SRC_OVER; //theonlyBlendOpdefinedinWindows2000
	m_Blend.BlendFlags = 0; //nothingelseisspecial...
	m_Blend.AlphaFormat = AC_SRC_ALPHA; //...
	m_Blend.SourceConstantAlpha = 255;//AC_SRC_ALPHA 
	UpdateLayeredWindow(mHwnd, hdc, &ptWinPos, &sizeWindow, mMemDC, &ptSrc, 0, &m_Blend, ULW_ALPHA);
}
void GDIRender::Creat()
{
	//��ʼ������
	HDC hdc = ::GetDC(mHwnd);
	RECT rct;
	GetWindowRect(mHwnd, &rct);
	POINT ptWinPos = { rct.left, rct.top };
	mWidth = rct.right - rct.left;
	mHeight = rct.bottom - rct.top;

	mMemDC = CreateCompatibleDC(hdc);
	mBitMap = CreateCompatibleBitmap(hdc, mWidth, mHeight);
	SelectObject(mMemDC, mBitMap);//???
	mBkgGraphics = new Gdiplus::Graphics(mMemDC);
	mBkgGraphics->SetCompositingMode(CompositingMode::CompositingModeSourceOver);
	//mBkgGraphics->SetSmoothingMode(SmoothingMode::SmoothingModeAntiAlias);//����ݣ�����������ɫ��������
	mBkgGraphics->SetInterpolationMode(InterpolationModeHighQualityBicubic);//ͼƬ��������

	// ���ò�δ���
	DWORD dwExStyle = GetWindowLong(mHwnd, GWL_EXSTYLE);

	if ((dwExStyle & WS_EX_LAYERED) != WS_EX_LAYERED)
	{
		SetWindowLong(mHwnd, GWL_EXSTYLE, dwExStyle ^ WS_EX_LAYERED);
	}
	//mBkgGraphics->Clear(Color(254, 0, 0, 0));

/*	POINT    ptSrc = { 0, 0 };
	SIZE    sizeWindow = { mWidth, mHeight };

	BLENDFUNCTION    m_Blend;
	m_Blend.BlendOp = AC_SRC_OVER; //theonlyBlendOpdefinedinWindows2000
	m_Blend.BlendFlags = 0; //nothingelseisspecial...
	m_Blend.AlphaFormat = AC_SRC_ALPHA; //...
	m_Blend.SourceConstantAlpha = 255;//AC_SRC_ALPHA 

	// ���͸�������򴰿ڵĻ���
	UpdateLayeredWindow(hwnd, hdc, &ptWinPos, &sizeWindow, mMemDC, &ptSrc, 0, &m_Blend, ULW_ALPHA);*/
	mIsCreated = true;
}

void GDIRender::ReSize(int width, int height)
{
	mWidth = width;
	mHeight = height;
}

void GDIRender::Destory()
{
	if (mIsCreated)
	{
		mIsCreated = false;
		// �ͷſռ�
		mBkgGraphics->ReleaseHDC(mMemDC);
		DeleteObject(mBitMap);
		DeleteDC(mMemDC);
		//TODO:����δ����Createʱ���ٻ���������
		//DeleteObject(mGraphics);
		DeleteObject(mBkgGraphics);
	}
}


void GDIRender::DrawBackGround(Gdiplus::Color &color, const XResource::XRect &r)
{
	Gdiplus::Color c = color;
	//�ֲ㴰��FillRectangle��255��͸����ʱ�ử�ɸ�����Ƭ���ס��෴�Ľ�������ɫ�������⴦��
	if (c.GetAlpha() == 255)
	{
		c = Gdiplus::Color(254, c.GetR(), c.GetB(), c.GetG());
	}
	Gdiplus::SolidBrush brush(c);
	mBkgGraphics->FillRectangle(&brush, r.IntX(), r.IntY(), r.IntWidth(), r.IntHeight());
}
void GDIRender::DrawImage(Gdiplus::Bitmap &img, const XResource::XRect &rect, int x, int y)
{
	Gdiplus::Rect temp(rect.X(), rect.Y(), rect.Width(), rect.Height());
	mBkgGraphics->DrawImage(&img, temp, x, y, rect.Width(), rect.Height(), Gdiplus::UnitPixel);
}
void GDIRender::DrawImage(XResource::XImage &xImg, const XResource::XRect &xRect)
{
	XRect r = xImg.GetDrawRect(xRect);
	mBkgGraphics->DrawCachedBitmap(xImg.CacheImage(*mBkgGraphics), r.X(), r.Y());
}

void GDIRender::DrawString(const std::wstring &text, const XResource::XRect &xRect)
{
	FontFamily  fontFamily(L"Times New Roman");
	Font        font(&fontFamily, 24, FontStyleRegular, UnitPixel);
	PointF      pointF(xRect.X(), xRect.Y());
	SolidBrush  solidBrush(Color(255, 0, 0, 255));

	mBkgGraphics->DrawString(text.c_str(), -1, &font, pointF, &solidBrush);
}
void GDIRender::DrawString(const std::wstring &text, const XResource::XRect &xRect, Gdiplus::StringAlignment align)
{
	FontFamily   fontFamily(L"Arial");
	Font         font(&fontFamily, 12, FontStyleBold, UnitPoint);
	RectF        rectF(30.0f, 10.0f, 120.0f, 40.0f);
	StringFormat stringFormat;
	SolidBrush   solidBrush(Color(255, 0, 0, 255));

	// Center-justify each line of text.
	stringFormat.SetAlignment(StringAlignmentNear);

	// Center the block of text (top to bottom) in the rectangle.
	stringFormat.SetLineAlignment(StringAlignmentNear);

	stringFormat.SetTrimming(StringTrimmingNone);

	mBkgGraphics->DrawString(text.c_str(), -1, &font, rectF, &stringFormat, &solidBrush);

}
void GDIRender::DrawString(const XResource::XText &text, const XResource::XRect &xRect)
{
	FontFamily   fontFamily(text.mFont.c_str());
	Font         font(&fontFamily, text.FontSize, text.mFontStyle, UnitPoint);
	StringFormat stringFormat;
	stringFormat.SetAlignment(StringAlignmentNear);
	stringFormat.SetLineAlignment(StringAlignmentNear);
	stringFormat.SetTrimming(StringTrimmingNone);

	Gdiplus::Color c = text.mColor;
	//�ֲ㴰��FillRectangle��255��͸����ʱ�ử�ɸ�����Ƭ���ס��෴�Ľ�������ɫ�������⴦��
	if (c.GetAlpha() == 255)
	{
		c = Gdiplus::Color(254, c.GetR(), c.GetB(), c.GetG());
	}
	SolidBrush   solidBrush(c);
	RectF rect(xRect.X(), xRect.Y(), xRect.Width(), xRect.Height());

	mBkgGraphics->DrawString(text.mText.c_str(), -1, &font, rect, &stringFormat, &solidBrush);
}


XRect GDIRender::MeasureString(const std::wstring &text)
{
	RectF temp;
	FontFamily fontFamily(L"Arial");
	Font font(&fontFamily, 12, FontStyleBold, UnitPoint);
	mBkgGraphics->MeasureString(text.c_str(), -1, &font, RectF(0, 0, 1000, 1000), &temp);
	return XRect(temp.X, temp.Y, temp.Width, temp.Height);
}

XRect GDIRender::MeasureString(const XResource::XText &text, const XResource::XRect &xRect)
{
	FontFamily   fontFamily(text.mFont.c_str());
	Font         font(&fontFamily, text.FontSize, text.mFontStyle, UnitPoint);
	StringFormat stringFormat;
	stringFormat.SetAlignment(StringAlignmentNear);
	stringFormat.SetLineAlignment(StringAlignmentNear);
	stringFormat.SetTrimming(StringTrimmingNone);
	SolidBrush solidBrush(text.mColor);

	RectF rect(xRect.X(), xRect.Y(), xRect.Width(), xRect.Height());

	RectF temp;
	mBkgGraphics->MeasureString(text.mText.c_str(), -1, &font, rect, &stringFormat, &temp);
	return XRect(temp.X, temp.Y, temp.Width, temp.Height);
}

bool GDIRender::Init(IXCanvas *canvas)
{
	if (canvas->GetType() == RenderType::GDIPlus)
	{
		//TODO::����ѧ Ӧ��ֱ�ӱ���canvas �������Ӧ��ʹ������ָ�룡������
		mBkgGraphics = dynamic_cast<GDICanvas*>(canvas)->mGraphics;
		return true;
	}
	return false;
}
