#pragma once
#include <string>
#include <boost/shared_ptr.hpp>
#include <vector>
#include <map>

namespace PlatformAPI
{
	namespace StringAddFuns
	{
		long long ToInt64(std::string str);
		long long ToInt64(std::wstring str);
	}


	template<class _char>
	class JsonObjectTemplate;
	template<class _char>
	class JsonArrayTemplate;


	template<class _char>
	class JsonArrayTemplate
	{
		typedef std::basic_string<_char> _string;
		typedef boost::shared_ptr<JsonObjectTemplate<_char>> JsonObjectTemplatePtr;
		typedef boost::shared_ptr<JsonArrayTemplate<_char>> JsonArrayTemplatePtr;
	private:
		std::string mJson;
		std::vector<_string> mObjs;
	public:
		JsonArrayTemplate(const _string& json_in)
		{
			mJson = json_in;

		}
		int Length()
		{
			return 1;
		}
		JsonObjectTemplatePtr GetJsonObject(int index)
		{
			JsonObjectTemplatePtr obj;
			return obj;
		}
		JsonObjectTemplatePtr operator[] (int index)
		{
			return GetJsonObject(index);
		}
	};
	enum JsonValueType
	{
		JsonValueType_String,
		JsonValueType_Number,
		JsonValueType_Object,
		JsonValueType_Array,
		JsonValueType_Bool,
		JsonValueType_Null
	};

	template<class _char>
	class JsonValueTemplate
	{
	public:
		typedef std::basic_string<_char> _string;
		_string mJsonStr;//δ���� ��ȫԭ��
		_string mValStr;//��������תΪ���� �����ַ����Ĵ�������
		bool mBoolVal;
		JsonValueType mType;
		JsonValueTemplate():mType(JsonValueType_Null){}
		JsonValueTemplate(const _string& str)
		{
			//TODO::����
			mJsonStr = str;
		}
		JsonObjectTemplate<_char> *mObj;
	};

	template<class _char>
	class JsonObjectTemplate
	{
		typedef std::basic_string<_char> _string;
		typedef boost::shared_ptr<JsonObjectTemplate<_char>> JsonObjectTemplatePtr;
		typedef boost::shared_ptr<JsonArrayTemplate<_char>> JsonArrayTemplatePtr;
	private:
		bool mIsOk;
		std::string mJson;
		std::map<_string, JsonValueTemplate<_char>> mDatas;
	public:
		JsonObjectTemplate(const _string& json_in)
		{
			mIsOk = false;
			mJson = json_in;
			int status = -1;
			vector<_char> key, val;//���µ�
			const _char* iter = json_in.c_str(); //ʣ�µ�
			int	nestNum = 0;//'['']'Ƕ�׵�����
			int bigNestNum = 0;
			while(true)
			{
				if (*iter == '\0')
				{
					if (status == -1)
					{
						//������ʱ״̬,״̬0 ���ҽ���
						mIsOk = true;
					}
					break;
				}
				//��Ҫ��continue ����iter����ǰ�ƶ�
				switch(status)
				{
				case -1: //��ʼ������״̬
					if (*iter == '{')
					{
						status = 0;
						break;
					}
					else if(*iter == '}')
					{
						break;
					}
					else
					{
						//��ͷ���� {ʧ��
						return;
					}
				case 0:
					if (*iter != '\"') //���� {������ ����{��Ӧ����\"
					{
						//�������ſ�ͷ ʧ��
						return;
					}
					status = 1;//һ״̬����ʼ��ȡ����
					break;
				case 1:
					if (*iter == '\"')
					{
						status = 2;//��״̬����ȡ������ϣ�׼����':'����
					}
					else
					{
						key.push_back(*iter);
					}
					break;
				case 2:
					if (*iter != ':')
					{
						//���ֺ��û��':' ʧ��
						return;
					}
					status = 3; //':'У����� ��ʼ��ȡ����
					break;
				case 3:
					if (*iter == '[')
					{
						//��������
						++nestNum;//Ƕ�׼�1
					}
					else if (*iter == ']')
					{
						--nestNum;//Ƕ��-1
					}
					else if (*iter == ',' || *iter == '}')
					{
						if (nestNum == 0)
						{
							//���û�н���Ƕ��
							/*wstring keyStr, valStr;
							keyStr.assign(&key[0], key.size());
							valStr.assign(&val[0], val.size());
							mDatas.insert(make_pair(keyStr, valStr));*/
							key.push_back('\0');
							val.push_back('\0');
							mDatas.insert(make_pair(&key[0], &val[0]));
							key.clear();
							val.clear();
							if (*iter == ',')
							{
								status = 0;//�ص���ʼ״̬,��ȡ��һ��key��value
							}
							else
							{
								status = -1;
							}
							break;
						}
					}
					else if (*iter == '\\')
					{
						status = 4;
						break;
					}
					val.push_back(*iter);
					break;
				case 4:
					switch(*iter)
					{
					case 'b':
						val.push_back(' ');
						break;
					case 'f':
						val.push_back('\f');
						break;
					case 'n':
						val.push_back('\n');
						break;
					case 'r':
						val.push_back('\r');
						break;
					case 't':
						val.push_back('\t');
						break;
					case 'u':
						val.push_back('0x');//��߸���4λ16���� ��\uffff
						break;
					case '\\':
					case '/':
					case '"':
						val.push_back(*iter);
						break;
					default:
						return;//����
					}
					status = 3;
					break;
				}
				++iter;//����ƶ�һ���ַ�
			}
		}
		bool ContentsKey(const _string& key)
		{
			return static_cast<bool>(mDatas.count(key));
		}
		JsonArrayTemplatePtr GetArray(const _string& tab)
		{
			JsonArrayTemplatePtr arr(new JsonArrayTemplate(mDatas[tab]));
			return arr;
		}
		_string GetString(const _string& key)
		{
			_string str = mDatas[key];
			if (str.find('\"') == 0)
			{
				str = str.substr(1,str.length() - 2);
			}
			return str;
		}
		long long GetInt64(const _string& key)
		{
			return StringAddFuns::ToInt64(GetString(key));
		}
	};

	typedef JsonObjectTemplate<char> JsonObject;
	typedef JsonArrayTemplate<char> JsonArray;
	typedef boost::shared_ptr<JsonObject> JsonObjectPtr;
	typedef boost::shared_ptr<JsonArray> JsonArrayPtr;

	typedef JsonObjectTemplate<wchar_t> JsonObjectW;
	typedef JsonObjectTemplate<wchar_t> JsonArrayW;
	typedef boost::shared_ptr<JsonObjectW> JsonObjectPtrW;
	typedef boost::shared_ptr<JsonArrayW> JsonArrayPtrW;
}