#pragma once
#include"stdafx.h"
#include "XImage.h"
#include "XRectPro.h"
#include "IBaseControl.h"
#include "IBaseWindow.h"
#include "DllExport.h"
#include<boost\shared_ptr.hpp>
#include<vector>

namespace XControls
{
	//TODO:д��ControlInterFace�ӿ�
	class SIMPLEDIRECTUI_API BaseControl : public IBaseControl
	{
	public:
		BaseControl(const std::wstring& id);
		~BaseControl();
		virtual void Draw(IXRender &g);
		virtual bool NeedReDraw();
		Gdiplus::Rect GetRect();
	protected:
		XResource::XImage mBgkImg;
		Gdiplus::Color mBgkColor;
	protected:
		IBaseControl* mParent = {NULL};//��������������
		//�����ط�����������ӿؼ�������ָ�룬����ᵼ�¿ؼ����ͷŲ���ȫ
		std::vector<BaseControlPtr> mChildrens;//����ʱ�ȴӺ�������
	protected:
		virtual void AbsRect(const XResource::XRect& rect)
		{
			mAbsRect = rect;
		}
		virtual void AddChildIntenal(IBaseControl* ctrl)
		{
			ctrl->BelongWnd(&this->BelongWnd());
			ctrl->Parent(this);
			mRealChildrens.push_back(ctrl);
		}
		void SetReDrawFlag()
		{
			mNeedReDraw = true;
			if (mBelongWnd)
			{
				//TODO:If not transparent, parent need't redraw
				//If  opengl, parent need't run draw to recode info
				mBelongWnd->NeedReDraw();
			}
		}
	public:
		virtual const MouseStatusStruct& MouseStatus();
		virtual void MouseEvent(UINT key, int x, int y);
		virtual void KeyBoardEvent(UINT key, WPARAM wParam, LPARAM lParam);
		void Parent(IBaseControl* parent)
		{
			mParent = parent;
			RefreshAbsRect();
		}
		IBaseControl& Parent()
		{
			return *mParent;
		}
		///ָ�봫����֮���벻Ҫ�ͷţ�ȫ�������ڲ����� !!������new������ ������ȡ��ַ�ģ��Ժ����ù��������ؼ�
		void AddChild(IBaseControl* ctrl)
		{
			ctrl->BelongWnd(&this->BelongWnd());
			ctrl->Parent(this);
			mRealChildrens.push_back(ctrl);
			mChildrens.push_back(BaseControlPtr(ctrl));
		}

		void BkgColor(byte a, byte r, byte g, byte b)
		{
			mBgkColor = Gdiplus::Color(a, r, g, b);
			SetReDrawFlag();
		}
		void BkgImg(const std::wstring& path)
		{
			if (mBgkImg.ImgPath() != path)
			{
				mBgkImg.ImgPath(path);
				SetReDrawFlag();
			}
		}
		const std::wstring BkgImg()
		{
			return mBgkImg.ImgPath();
		}
		std::wstring ID()
		{
			return mId;
		}
		XResource::XRect& AbsRect();
		const XResource::XRectPro& Rect() const;
		XResource::XRectPro& Rect();
		void Rect(double x, double y, double width, double height);
		void Rect(const XResource::XRect& rect);
		void Rect(const XResource::XRectPro& rect);

		bool Visable()
		{
			return mIsVisable;
		}
		void Visable(bool visable)
		{
			if (mIsVisable != visable)
			{
				mIsVisable = visable;
				SetReDrawFlag();
			}
		}
		void DragWindowEnable(bool enable)
		{
			mDragWindowEnable = enable;
		}
		///��ȡ�ؼ��Ƿ���϶�����
		bool DragWindowEnable()
		{
			return mDragWindowEnable;
		}

		IXWindow& BelongWnd()
		{
			return *mBelongWnd;
		}
		bool BelongWnd(IXWindow *wnd)
		{
			mBelongWnd = wnd;
			for (auto child : mRealChildrens)
			{
				child->BelongWnd(wnd);
			}
			return true;
		}
	protected:
		IXWindow *mBelongWnd = {NULL};
		bool mNeedReDraw;
		XResource::XRectPro mRect;
		std::wstring mId;
		bool mIsLButtonDown;
		bool mHasFocus = false;
		bool mIsVisable;
		bool mDragWindowEnable;
		bool mIsMouseEntered = false;
		MouseStatusStruct mMouseStauts;
		//�Դ���ľ���λ��
		XResource::XRect mAbsRect;
		void RefreshAbsRect();
		virtual XResource::XPoint GetMousePos()
		{
			auto temp = mBelongWnd->MouseStauts();
			XResource::XPoint point(temp.X - mAbsRect.IntX(), temp.Y - mAbsRect.IntY());
			return point;
		}


		int mClickedX = 0, mClickedY = 0;//��ʱ
	private:
		std::vector<IBaseControl*> mRealChildrens;//������ȫ��children�������ؼ��ڲ������ģ�����������
	};
}