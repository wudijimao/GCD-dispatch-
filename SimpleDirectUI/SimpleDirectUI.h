#pragma once
#include"DllExport.h"
#include "WindowsManager.h"
#include<Windows.h>



//ʵ�ֹ���֮��д�ɽӿ� ֻ��¶���ʹ�õĲ���
class SIMPLEDIRECTUI_API SimpleDirectUI {
public:
	static std::shared_ptr<SimpleDirectUI> getInstance();
	//exeʵ��������Ƿ���ʾ����
	int Show(HINSTANCE hInstance, HINSTANCE hPrevInstance,
		PSTR szCmdLine, int iCmdShow);
	std::shared_ptr<XWindow>&Window()
	{
		return mWindow;
	}
private:
	std::shared_ptr<XWindow>mWindow;
	SimpleDirectUI(void){};
};
