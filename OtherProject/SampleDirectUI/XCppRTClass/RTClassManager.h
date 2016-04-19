#include "IRTClass.h"

#include <vector>
#include <boost/shared_ptr.hpp>



class RTClassManager
{
public:
	RTClassManager(){}
	void Regist(IRTClass& obj);
	typedef std::map < std::string, boost::shared_ptr<RTClassHolder> > ObjMap;
	//����-1ʧ��  >=0�ɹ�
	bool CallFun(const std::string&objName, const std::string&funName, const RTArgments &args, RTValue& oRet );
private:
	void OnObjDestory(IRTClass* obj);
	void CallFun( const FuncStrSign &func, void* obj = NULL);
	ObjMap mObjMap;
};
