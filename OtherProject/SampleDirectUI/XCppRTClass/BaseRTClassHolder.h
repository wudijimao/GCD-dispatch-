#pragma once
#include "RTArgments.h"
#include "RTValue.h"
#include <vector>
#include <string>
#include <assert.h>

#define RegistFun(fun) RegistFunInternal(&fun, #fun)

struct FuncStrSign
{
	std::vector<RTType::RTTypeEnum> mArgTypes;
	RTType::RTTypeEnum mReturnType;
	std::string mName;
};

class BaseRTClassHolder
{
public:
	BaseRTClassHolder(const std::string& className, const std::string& objName, void* obj);
	const std::string& GetClassName();
	const std::string& GetObjName();
	void* GetObj();
	virtual bool CallFun(const std::string funName, const RTArgments &args, RTValue &oRet) = 0;
protected:
	//���ǵڼ���
	int GetFunIndex(const std::string funName, const RTArgments &args);
	template <typename CppFunc>
	void RegistFunInternal( CppFunc add, const char*name )
	{
		FuncStrSign func;
		std::string funFullName = name;
		func.mName = GetFunName(funFullName.c_str());
		if (func.mName.empty())
		{
			assert(false);
			return;
		}
		std::string funTypeStr = typeid(CppFunc).name();
		SaveFunType(funTypeStr, func);
		mFunSigns.push_back(func);
	}
protected:
	void* mObj;
	std::string mClassName;
	std::string mObjName;
	std::vector<FuncStrSign> mFunSigns;
private:
	//��ȡ���������ȶ������Ƿ����
	std::string GetFunName(const std::string &funcFullName);
	void SaveFunType(std::string &typeStr, FuncStrSign& func);
};