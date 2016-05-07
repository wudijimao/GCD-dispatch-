#pragma once
#include "XRect.hpp"
#include <string>
#include <Windows.h>
#include <gdiplus.h>
namespace XResource
{
	enum class StretchEnum
	{
		None,		  //�����죨���У�
		Fill,         //�������
		Uniform,      //��Ӧ���пհף�
		UniformToFill //�ȱ������ţ����
	};
	class XImage
	{
	public:
		XImage() :mNeedLoadImg(false){}
		XImage(const std::wstring &path) :mImgPath(path), mNeedLoadImg(true){}
		bool operator = (const std::wstring& imgUrl)
		{
			return ImgPath(imgUrl);
		}
		Gdiplus::Image* Image()
		{
			return mImg;
		}
		Gdiplus::CachedBitmap* CacheImage(Gdiplus::Graphics &g)
		{
			if (mNeedLoadDrawImg || mNeedLoadImg)
			{
				Gdiplus::Bitmap bitmap(mRect.IntWidth(), mRect.IntHeight());
				Gdiplus::Graphics *imgG = Gdiplus::Graphics::FromImage(&bitmap);
				imgG->DrawImage(mImg, 0, 0, mRect.IntWidth(), mRect.IntHeight());
				mCacheImg = new Gdiplus::CachedBitmap(&bitmap, &g);
				mNeedLoadImg = false;
				mNeedLoadDrawImg = false;
			}
			return mCacheImg;
		}
		///�����������ü�������Ҫ���Ƶ�������Ŀ������rect��������ڴ���ľ�������
		XRect GetDrawRect(const XRect& rect)
		{
			if (mRect != rect)
			{
				mRect = rect;
				mNeedLoadDrawImg = true;
			}
			if (mNeedLoadImg)
			{
				if (mImg)
				{
					delete mImg;
				}
				mImg = new Gdiplus::Image(mImgPath.c_str());
			}
			return mRect;
		}
		///Ϊ�վ���û��ͼƬ
		std::wstring ImgPath() const
		{
			return mImgPath;
		}
		bool ImgPath(const std::wstring &path)
		{
			if (mImgPath != path)
			{
				mImgPath = path;
				mNeedLoadImg = true;
				return true;
			}
			return false;
		}
		StretchEnum Stretch()
		{
			return mStretch;
		}
		void Stretch(StretchEnum stretch)
		{
			if (mStretch != stretch)
			{
				mStretch = stretch;
				mNeedLoadDrawImg = true;
			}
		}
	private:
		XRect mRect;
		bool mNeedLoadImg;
		bool mNeedLoadDrawImg = false;
		Gdiplus::CachedBitmap *mCacheImg;
		Gdiplus::Image *mImg = NULL;
		std::wstring mImgPath;
		StretchEnum mStretch;
	};
}