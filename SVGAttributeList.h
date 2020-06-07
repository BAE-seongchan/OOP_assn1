
////////////
/////////////
#pragma once


#include <iostream>
#include <cstring>
#include <string>

class SVGAttribute;

class SVGAttributeList
{
private:
	SVGAttribute* apHead; // list의 head를 가리키는 포인터
	SVGAttribute* apTail; // list의 tail을 가리키는 포인터
	int aSize; // list의 크기를 나타내는 변수

public:

	SVGAttributeList() : aSize(0),apHead(NULL),apTail(NULL) // 생성자로 초기화
	{
	}
	SVGAttribute* get_head();
	SVGAttribute* get_tail();

	void AddSvgAttribute(SVGAttribute * pAttribute);

	~SVGAttributeList() // 소멸자에서 멤버 변수들의 동적할당해제
	{
		
		SVGAttribute * temp;
		while (apHead != apTail)
		{
			temp = apHead;
			apHead = apHead->get_nextnode();
			delete temp;
		}
		delete apHead;		
	}

};

