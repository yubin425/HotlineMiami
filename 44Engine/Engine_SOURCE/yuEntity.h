#pragma once
#include "yuEngine.h"


//#define GETSET(__TYPE__, __TARGET__, __METHODNAME__) \
//__TYPE__ get##__METHODNAME__() \
//{ \
//return __TARGET__; \
//} \
//void set##__METHODNAME__(__TYPE__ value) \
//{ \
//__TARGET__ = value; \
//}
//
//// get ������Ƽ ��ũ��
//#define GET(__TYPE__, __TARGET__, __METHODNAME__) \
//__TYPE__ get##__METHODNAME__() \
//{ \
//return __TARGET__; \
//}
//
//// set ������Ƽ ��ũ��
//#define SET(__TYPE__, __TARGET__, __METHODNAME__) \
//void set##__METHODNAME__(__TYPE__ value) \
//{ \
//__TARGET__ = value; \
//}

namespace yu
{
	class Entity
	{
	public:
		Entity();
		Entity(const Entity& other);
		virtual ~Entity();

		void SetName(const std::wstring& name) { mName = name; }
		const std::wstring& GetName() { return mName; }
		UINT32 GetID() { return mID; }

	private:
		std::wstring mName;
		const UINT32 mID;
		
	};
}


