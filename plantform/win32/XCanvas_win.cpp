#include "XCanvas_win.hpp"

using namespace Gdiplus;

bool GLCanvas_ios::initMemDC() {
	static GDIPlusInitHelper helper;
	RECT rct;
	GetWindowRect(mHWND, &rct);
	POINT ptWinPos = { rct.left, rct.top };
	_size.Width(rct.right - rct.left);
	_size.Height(rct.bottom - rct.top);

	mMemDC = CreateCompatibleDC(mHDC);
	mBitMap = CreateCompatibleBitmap(mHDC, _size.Width(), _size.Height());
	SelectObject(mMemDC, mBitMap);//???
	mBkgGraphics = new Graphics(mMemDC);
	mBkgGraphics->SetCompositingMode(Gdiplus::CompositingMode::CompositingModeSourceOver);
	mBkgGraphics->SetSmoothingMode(Gdiplus::SmoothingMode::SmoothingModeAntiAlias);//����ݣ�����������ɫ��������
	mBkgGraphics->SetInterpolationMode(Gdiplus::InterpolationModeHighQualityBicubic);//ͼƬ��������


	DWORD dwExStyle = GetWindowLong(mHWND, GWL_EXSTYLE);  // ���ò�δ���

	if ((dwExStyle & WS_EX_LAYERED) != WS_EX_LAYERED)
	{
		SetWindowLong(mHWND, GWL_EXSTYLE, dwExStyle ^ WS_EX_LAYERED);
	}
	mBkgGraphics->Clear(Gdiplus::Color(254, 0, 0, 0));
	return true;
}