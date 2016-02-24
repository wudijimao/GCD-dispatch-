#pragma once
#include "IXRender.h"

class GLRender : public IXRender
{
public:
	GLRender(HWND hwnd);//��ʱ
	virtual bool Init(IXCanvas *canvas);
	virtual void Creat();
	virtual void ReSize(int width, int height);
	virtual void Paint();
	virtual void Destory();
	virtual void DrawBackGround(Gdiplus::Color &color, const XResource::XRect &xRect);
	virtual void DrawLine(int x1, int y1, int x2, int y2);
	//��Ҫ���Ƶľ�������
	virtual void DrawImage(XResource::XImage &img, const XResource::XRect &rect);
	//�ı����Ҫ���������� �������ͨͼ�ηֿ� �ֲ������л���루�ֿ���������OpenGlӦ��Ҳ��ʹ������Ⱦ�ı��� ����ʹ������������Ⱦ���棬����FreeType/DirectWrite��
	virtual void DrawString(const std::wstring &text, const XResource::XRect &xRect);
	virtual void DrawString(const std::wstring &text, const XResource::XRect &xRect, Gdiplus::StringAlignment align);
	virtual void DrawString(const XResource::XText &text, const XResource::XRect &xRect);
	virtual XResource::XRect MeasureString(const XResource::XText &text, const XResource::XRect &xRect);
	virtual XResource::XRect MeasureString(const std::wstring &text);

private:

};

