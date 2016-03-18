#pragma once
#include"BaseControl.h"
#include"GDICacheGraphics.h"
#include"XVScrollBar.h"
namespace XControls
{
	class XScrollViewer : public BaseControl
	{
	public:
		XScrollViewer(const std::wstring& id) : BaseControl(id)
		{
			AddChildIntenal(&mBar);
			SizeChange.connect(std::bind(&XScrollViewer::OnSizeChange, this, std::placeholders::_1, std::placeholders::_2));
			mBar.ScrollPostionChange.connect([this](double p){
				mScrollY = p;
			});
		}
		void AddContent(IBaseControl *content)
		{
			mContent.reset(content);
			//��ʱ����д���Ժ�Ҫ��취����chche�����Ĵ�С
			XResource::XRect temp = mContent->Rect();
			temp.Height(9999);
			mCacheGraphics.Creat(temp);
			mBar.ContentHeight(mContent->Rect().Height());
			mContent->SizeChange.connect(std::bind(&XScrollViewer::OnContentSizeChange, this, std::placeholders::_1, std::placeholders::_2));
		}
		void Draw(IXRender &g)
		{
			mContent->Draw(mCacheGraphics);
			//TODO::ʵ��CacheImg
			//g.DrawImage(mCacheGraphics.Bitmap(), mRect, 0, IntScrollY());
			BaseControl::Draw(g);
		}
		void OnContentSizeChange(IBaseControl& ctrl, const XResource::XRect &rect)
		{
			mBar.ContentHeight(rect.Height());
		}
		void OnSizeChange(IBaseControl& ctrl, const XResource::XRect &rect)
		{
			mBar.Rect(rect.IntWidth() - 10, 0, mBar.Rect().IntWidth(), rect.IntHeight());
		}
	private:
		int IntScrollY()
		{
			return (int)mScrollY;
		}
		double mScrollY = {0};
		XVScrollBar mBar = { L"bar" };
		GDICacheGraphics mCacheGraphics;
		BaseControlPtr mContent;//TODO::error!!�����Ͳ���������ϵ���� ����ѧ
	};
}