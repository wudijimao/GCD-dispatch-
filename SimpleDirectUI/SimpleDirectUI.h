#pragma once
#include"DllExport.h"
#include "WindowsManager.h"
#include<boost\shared_ptr.hpp>
#include<Windows.h>



//ʵ�ֹ���֮��д�ɽӿ� ֻ��¶���ʹ�õĲ���
class SIMPLEDIRECTUI_API SimpleDirectUI {
public:
	static boost::shared_ptr<SimpleDirectUI> getInstance();
	//exeʵ��������Ƿ���ʾ����
	int Show(HINSTANCE hInstance, HINSTANCE hPrevInstance,
		PSTR szCmdLine, int iCmdShow);
	boost::shared_ptr<XWindow>&Window()
	{
		return mWindow;
	}
private:
	boost::shared_ptr<XWindow>mWindow;
	SimpleDirectUI(void){};
};
