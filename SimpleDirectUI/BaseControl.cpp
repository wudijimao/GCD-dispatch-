#include"stdafx.h"
#include"BaseControl.h"

using namespace XControls;
using namespace XResource;

BaseControl::BaseControl(const std::wstring& id)
: mNeedReDraw(false),
mIsLButtonDown(false),
mDragWindowEnable(false),
mIsVisable(true)
{
	mBgkColor = Gdiplus::Color(0, 255, 255, 255);
	mId = id;
}
BaseControl::~BaseControl()
{
	//�ͷ������ӿؼ����ӿؼ�����ָ�����˳��� Ҳ���Զ��ͷ�
	mChildrens.clear();
}
bool BaseControl::NeedReDraw()
{
	return mNeedReDraw;
}
void BaseControl::Draw(IXRender &g)
{
	mNeedReDraw = false;
	//�Ȼ��Լ�
	if (!mIsVisable)
	{
		return;
	}
	if (mBgkImg.ImgPath() != L"")
	{
		g.DrawImage(mBgkImg, mAbsRect);
	}
	else if (mBgkColor.GetAlpha() != 0)
	{
		g.DrawBackGround(mBgkColor, mAbsRect);
	}
	//˳���Լ����ӿؼ�
	for (auto child : mRealChildrens)
	{
		child->Draw(g);
	}
}
const MouseStatusStruct& BaseControl::MouseStatus()
{
	return mBelongWnd->MouseStauts();
}
void BaseControl::KeyBoardEvent(UINT key, WPARAM wParam, LPARAM lParam)
{
	KeyDown(*this, wParam, lParam);
	for (auto child : mRealChildrens)
	{
		child->KeyBoardEvent(key, wParam, lParam);
	}
}
void BaseControl::MouseEvent(UINT key, int x, int y)
{
	x = x - mRect.IntX();
	y = y - mRect.IntY();
	mClickedX = x;//��ʱ  Ӧ�ö���һ���������¼���Ӧ����¼����
	mClickedY = y;

	//TODO::�Ժ�֧�ֲ��������������ԣ�����PNG͸�����򲻿ɵ����
	//����Ѿ��ڿؼ���Χ�ڰ����ˣ���������ڿؼ���Χ��
	if ((x > 0 && x< mRect.IntWidth() && y >0 && y < mRect.IntHeight()) || mIsLButtonDown)
	{
		switch (key)
		{
		case WM_LBUTTONDOWN:
			mIsLButtonDown = true;
			if (MouseDown)
			{
				MouseDown(*this);
			}
			if (!mHasFocus)
			{
				mHasFocus = true;
				if (GotFocus)
				{
					GotFocus(*this);
				}
			}
			if (mDragWindowEnable)
			{
				LPARAM lparm = (x << 16) && (y);
				mBelongWnd->Drag(lparm);
			}
			break;
		case WM_LBUTTONUP:
			if (mIsLButtonDown)
			{
				mIsLButtonDown = false;
				if (MouseClick)
				{
					MouseClick(*this);
				}
			}
			if (MouseUp)
			{
				MouseUp(*this);
			}
			break;
		case WM_MOUSEMOVE:
			if (!mIsMouseEntered)
			{
				mIsMouseEntered = true;
				if (MouseEnter) {
					MouseEnter(*this);
				}
			}
			if (MouseMove)
			{
				MouseMove(*this);
			}
			break;
		case WM_MOUSEWHEEL:
			{
				//int zDelta = GET_WHEEL_DELTA_WPARAM(wParam);
				//MouseWheel(*this);
				break;
			}
		}
	}
	else
	{
		if (mIsMouseEntered)
		{
			mIsMouseEntered = false;
			//רΪ����뿪֪ͨһ���ӿؼ�
			for (auto child : mRealChildrens)
			{
				child->MouseEvent(key, x, y);
			}
			if (MouseLeave)
			{
				MouseLeave(*this);
			}
		}
		if (key == WM_LBUTTONDOWN && mHasFocus)
		{
			mHasFocus = false;
			if (LostFocus)
			{
				LostFocus(*this);
			}
		}
	}
	for (auto child : mRealChildrens)
	{
		child->MouseEvent(key, x, y);
	}
}


XResource::XRect& BaseControl::AbsRect()
{
	return mAbsRect;
}

const XResource::XRectPro& XControls::BaseControl::Rect() const
{
	return mRect;
}

XResource::XRectPro& BaseControl::Rect()
{
	return mRect;
}
void BaseControl::Rect(double x, double y, double width, double height)
{
	Rect(XResource::XRect(x, y, width, height));
}
void BaseControl::Rect(const XResource::XRect& rect)
{
	XResource::XRect temp = rect;
	//��߱�����ڵ���0������⣬  X��Yλ�ò���С������趨��˼�ǲ��ܳ������ؼ��ķ�Χ����������Χ�������ԻḲ�ǲ����������ؼ��Ĳ���
	if (rect.X() < 0 || rect.Y() < 0 || rect.Width() < 0 || rect.Height() < 0)
	{
		return;
	}
	if (PosChange &&( temp.X() != mRect.X() || temp.Y() != mRect.Y()))
	{
		PosChange(*this, temp);
	}
	if (SizeChange && (temp.Width() != mRect.Width() || temp.Height() != mRect.Height()))
	{
		SizeChange(*this, temp);
	}
	mRect = temp;
	RefreshAbsRect();
	SetReDrawFlag();
}

void XControls::BaseControl::Rect(const XResource::XRectPro& rect)
{
	mRect = rect;
	RefreshAbsRect();
	SetReDrawFlag();
}


void XControls::BaseControl::RefreshAbsRect()
{
	if (mId == L"middle")
	{
		int a = 0;
	}
	if (mParent != NULL)
	{
		AbsRect(mRect.MakeAbsRect(mParent->AbsRect()));
	}
	else
	{
		AbsRect(mRect);
	}
	for (auto child : mRealChildrens)
	{
		child->RefreshAbsRect();
	}
}
