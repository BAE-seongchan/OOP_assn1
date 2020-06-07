
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
	SVGObject * apHead;// list�� head�� ����Ű�� ������
	SVGObject * apTail; // list�� tai�� ����Ű�� ������
	int aSize; //����Ʈ�� ũ��
public:
	SVGObjectList(): aSize(0)
	{
	}
	SVGObject* get_Head();
	SVGObject* get_Tail();
	int get_aSize();
	void AddSvgObject(SVGObject*); // ����Ʈ�� object�� �߰�
	
	void RemoveSvgObject(SVGObject *); // ����Ʈ���� �ش��ϴ� object�� ����

	void Clear(); // ����Ʈ�� ������ ��� ���� �Լ�

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

