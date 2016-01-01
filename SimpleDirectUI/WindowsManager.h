#pragma once
#include "BaseWindow.h"
#include <map>
#include <windows.h>
#include <boost/signals2.hpp>

//��ֱ��ʹ�ã���������ʱ���Զ�ע�ᣬ����ʱ�Զ���ע��
//��������ʱ���Զ���ע�ᣬ���Ա���ָ��Ҳ�ǰ�ȫ��
class WindowsManager
{
	std::map<HWND, XWindow*>mWndMap;
public:
	static WindowsManager& GetInstanc();
	static LRESULT CALLBACK WndProc(HWND hwnd, UINT iMsg, WPARAM wParam, LPARAM lParam);//���մ�����Ϣ���ַ��������window��ʵ����
public:
	bool Regist(HWND hwnd, XWindow* win);
	bool UnRegist(HWND hwnd);
private:
	//��ֹ�ⲿ����������
	WindowsManager(){}
	WindowsManager(const WindowsManager &){}//Ĭ�Ͽ�������  
	WindowsManager & operator=(const WindowsManager &){}//Ĭ�ϸ�ֵ�����

};