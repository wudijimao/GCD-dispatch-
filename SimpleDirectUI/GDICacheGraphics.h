#pragma once
#include"GDIRender.h"

//ר�Ż���
class SIMPLEDIRECTUI_API GDICacheGraphics : public GDIRender
{
public:
	void Creat(const XResource::XRect& rect);
	~GDICacheGraphics();
	Gdiplus::Bitmap& Bitmap()
	{
		return *mBitmap;
	}
private:
	Gdiplus::Bitmap *mBitmap = {NULL};
};

