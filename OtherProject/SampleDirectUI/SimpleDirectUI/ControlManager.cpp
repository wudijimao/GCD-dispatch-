#include "stdafx.h"
#include "ControlManager.h"

using namespace XControls;


ControlManager::ControlManager()
{
	mRoot.reset(new BaseControl(L"Root"));
}

ControlManager::~ControlManager()
{
	//���뱣֤���������б��ؼ����Ż����������ٺ��Զ�ȫ������
	mControls.clear();
}


BaseControlPtr ControlManager::GetControl(const std::wstring& id)
{
	ControlMap::iterator iter = mControls.find(id);
	if (iter != mControls.end())
	{
		return iter->second;
	}
	return BaseControlPtr();
}
BaseControlPtr ControlManager::GetRoot()
{
	return mRoot;
}