
////////////
/////////////


#pragma warning
#pragma once
#include <cstring>
#include <string>

class SVGObject;

class SVGObjectList
{
private:
	SVGObject * apHead;// list의 head를 가리키는 포인터
	SVGObject * apTail; // list의 tai을 가리키는 포인터
	int aSize; //리스트의 크기
public:
	SVGObjectList(): aSize(0)
	{
	}
	SVGObject* get_Head();
	SVGObject* get_Tail();
	int get_aSize();
	void AddSvgObject(SVGObject*); // 리스트에 object를 추가
	
	void RemoveSvgObject(SVGObject *); // 리스트에서 해당하는 object를 제거

	void Clear(); // 리스트의 연결을 모두 끊는 함수

	~SVGObjectList() 
	{
		if (apHead != NULL)
		{
			while (apHead != apTail)
			{
				SVGObject* temp = apHead;
				apHead = apHead->get_nextnode();
				delete temp;
			}
		}
		
	}

};

