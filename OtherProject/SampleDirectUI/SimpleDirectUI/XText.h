#pragma once
#include <string>
#include <windows.h>
#include <gdiplus.h>

namespace XResource
{
	class XText
	{
	public:
		XText()
		{
			mFontStyle = Gdiplus::FontStyleRegular;
		}
		~XText(){}
	public:
		std::wstring mFont = { L"����" };
		int FontSize = { 10 };
		Gdiplus::FontStyle mFontStyle;

		std::wstring mText;
		Gdiplus::Color mColor = { 0, 0, 0 };//��ɫ
		Gdiplus::Color mBakColor = { 0, 0, 0, 0 };//͸��
		Gdiplus::Color mSelectedColor = { 255, 255, 255 };
		Gdiplus::Color mSelectedBakColor = { 0, 162, 232 };
	};
}