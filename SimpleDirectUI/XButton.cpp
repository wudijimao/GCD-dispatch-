#include "stdafx.h"
#include "XButton.h"
using namespace XControls;
XButton::XButton(const std::wstring& id) : BaseControl(id)
{
	this->MouseDown = std::bind(&XButton::OnMouseDown, this, std::placeholders::_1);
	this->MouseUp = std::bind(&XButton::OnMouseUp, this, std::placeholders::_1);
	this->MouseEnter = std::bind(&XButton::OnMouseEnter, this, std::placeholders::_1);
	this->MouseLeave = std::bind(&XButton::OnMouseLeave, this, std::placeholders::_1);
}
XButton::XButton(const std::wstring& id,
	const std::wstring& normalImg,
	const std::wstring& hoverImg,
	const std::wstring& downImg,
	const std::wstring& forceImg,
	const std::wstring& disableImg)
	:BaseControl(id),
	mNormalImg(normalImg),
	mDownImg(downImg),
	mHoverImg(hoverImg),
	mForceImg(forceImg),
	mDisableImg(disableImg)
{
	this->MouseDown = std::bind(&XButton::OnMouseDown, this, std::placeholders::_1);
	this->MouseUp = std::bind(&XButton::OnMouseUp, this, std::placeholders::_1);
	this->MouseEnter = std::bind(&XButton::OnMouseEnter, this, std::placeholders::_1);
	this->MouseLeave = std::bind(&XButton::OnMouseLeave, this, std::placeholders::_1);
}

XButton::~XButton()
{
}
void XButton::Draw(IXRender &g)
{
	BaseControl::Draw(g);
	//TODO:�ж����� Ч�ʲ��ߣ�Ӧ�ø����Ƿ�ı���Ƿ�ɼ��ڵݹ�ǰ�ж��Ƿ���Ҫ�ػ棬���������Ƿ�ɵ����������IsClickTestEnable��
	if (!mIsVisable)
	{
		return;
	}
	XResource::XImage *img;
	switch (mState)
	{
	case XControls::ButtonStates::NORMAL:
		img = &mNormalImg;
		break;
	case XControls::ButtonStates::DOWN:
	case XControls::ButtonStates::HOVERDOWN:
		img = &mDownImg;
		break;
	case XControls::ButtonStates::HOVER:
		img = &mHoverImg;
		break;
	case XControls::ButtonStates::FORCE:
		img = &mForceImg;
		break;
	case XControls::ButtonStates::DISABLE:
	default:
		img = &mDisableImg;
		break;
	}
	g.DrawImage(*img, mAbsRect);
}
void XButton::OnMouseDown(IBaseControl&)
{
	if (mState == ButtonStates::HOVER)
	{
		mState = ButtonStates::HOVERDOWN;
	}
	else
	{
		mState = ButtonStates::DOWN;
	}
	SetReDrawFlag();
}
void XButton::OnMouseUp(IBaseControl&)
{
	if (mState == ButtonStates::HOVER)
	{
		return;
	}
	if (mState == ButtonStates::HOVERDOWN)
	{
		mState = ButtonStates::HOVER;
	}
	else
	{
		mState = ButtonStates::NORMAL;
	}
	SetReDrawFlag();
}
void XButton::OnMouseEnter(IBaseControl&)
{
	mState = ButtonStates::HOVER;
	SetReDrawFlag();
}
void XButton::OnMouseLeave(IBaseControl&)
{
	if (mState == ButtonStates::HOVERDOWN)
	{
		mState = ButtonStates::DOWN;
	}
	else
	{
		mState = ButtonStates::NORMAL;
		SetReDrawFlag();
	}
}