
////////////
/////////////
#pragma once
#include <iostream>
#include <cstring>
#include <string>

class SVGAttributeList;
class SVGObjectList;

class SVGObject
{
private:
	char* aTagName; //SVG ��ü�� �±׸�
	int in_name;
	SVGObject * apParent; //�θ� svg ��ü ������
	SVGObjectList * apChildList; // �ڽ� SVG ��ü���� ��� ����Ʈ ������
	SVGAttributeList * apAttributeList; // ��ü�� ������ ��� �ִ� Attribuet���� ����Ʈ ������
	SVGObject * prenode;//���� ���� SVGObject list ����
	SVGObject * nextnode; //���� ���� SVGObject list ������ ����
public:
	
	SVGObject() : in_name(0), apParent(NULL), apChildList(NULL), apAttributeList(NULL), prenode(NULL), nextnode(NULL)
	{}

	void set_atagname(char * a); // ���� ���� ���� �Լ�, �ܼ�

	void set_apParrent(SVGObject *parent);

	void set_apChildList(SVGObjectList *list);

	void set_nextnode(SVGObject * pobj); // nextnode�� ����
	
	void set_atrlist(SVGAttributeList*);

	SVGAttributeList * get_atrlist();


	char* get_name();

	SVGObject *get_apParent();

	SVGObject * get_nextnode() const;

	SVGObject * get_prenode() const; // prenode�� �ּҸ� ��ȯ
	
	void set_prenode(SVGObject * pobj); // prenode�� �ּҸ� ����

	SVGObjectList * get_apChildList();

	void AppendChild(SVGObject* pChild); // �ڳ� object�� �߰��ϴ� �Լ�

	void AddAttribute(SVGAttribute * pAttribute); // attribute�� �߰��ϴ� �Լ�

	~SVGObject() // ���� ����ÿ� ���� �Ҵ�� �̸��� �����Ѵ�.
	{
		if (in_name != 0)
		{
			delete[]aTagName;
		}

	}
};
