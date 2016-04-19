#pragma once
#include"BaseControl.h"
#include"stdafx.h"
#include<map>

namespace XControls
{
	typedef std::map<std::wstring, BaseControlPtr> ControlMap;

	//��������ؼ������ṩ���ɾ���������ܶ��ѣ�������������
	class SIMPLEDIRECTUI_API ControlManager
	{
	public:
		ControlManager();
		~ControlManager();

		BaseControlPtr GetControl(const std::wstring& id);
		BaseControlPtr GetRoot();
	private:
		//�ؼ�map
		ControlMap mControls;
		//�ؼ�����
		BaseControlPtr mRoot;
	};
}