
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
	SVGAttribute* apHead; // list�� head�� ����Ű�� ������
	SVGAttribute* apTail; // list�� tail�� ����Ű�� ������
	int aSize; // list�� ũ�⸦ ��Ÿ���� ����

public:

	SVGAttributeList() : aSize(0),apHead(NULL),apTail(NULL) // �����ڷ� �ʱ�ȭ
	{
	}
	SVGAttribute* get_head();
	SVGAttribute* get_tail();

	void AddSvgAttribute(SVGAttribute * pAttribute);

	~SVGAttributeList() // �Ҹ��ڿ��� ��� �������� �����Ҵ�����
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

