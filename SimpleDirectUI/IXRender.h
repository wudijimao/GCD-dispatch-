#include "IXCanvas.h"
#include "XImage.h"
#include "XText.h"

class SIMPLEDIRECTUI_API IXRender
{
public:
	virtual ~IXRender(){};
	virtual bool Init(IXCanvas *canvas) = 0;
	virtual void ReSize(int width, int height) = 0;
	virtual void Paint() = 0;
	virtual void Destory() = 0;
	virtual void DrawBackGround(Gdiplus::Color &color, const XResource::XRect &xRect) = 0;
	virtual void DrawLine(int x1, int y1, int x2, int y2) = 0;
	//��Ҫ���Ƶľ�������
	virtual void DrawImage(XResource::XImage &img, const XResource::XRect &rect) = 0;
	//�ı����Ҫ���������� �������ͨͼ�ηֿ� �ֲ������л���루�ֿ���������OpenGlӦ��Ҳ��ʹ������Ⱦ�ı��� ����ʹ������������Ⱦ���棬����FreeType/DirectWrite��
	virtual void DrawString(const std::wstring &text, const XResource::XRect &xRect) = 0;
	virtual void DrawString(const std::wstring &text, const XResource::XRect &xRect, Gdiplus::StringAlignment align) = 0;
	virtual void DrawString(const XResource::XText &text, const XResource::XRect &xRect) = 0;
	virtual XResource::XRect MeasureString(const XResource::XText &text, const XResource::XRect &xRect) = 0;
	virtual XResource::XRect MeasureString(const std::wstring &text) = 0;
};