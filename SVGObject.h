
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
	char* aTagName; //SVG 객체의 태그명
	int in_name;
	SVGObject * apParent; //부모 svg 객체 포인터
	SVGObjectList * apChildList; // 자식 SVG 객체들이 담긴 리스트 포인터
	SVGAttributeList * apAttributeList; // 객체의 정보를 담고 있는 Attribuet들의 리스트 포인터
	SVGObject * prenode;//같은 세대 SVGObject list 구현
	SVGObject * nextnode; //같은 세대 SVGObject list 구현을 위해
public:
	
	SVGObject() : in_name(0), apParent(NULL), apChildList(NULL), apAttributeList(NULL), prenode(NULL), nextnode(NULL)
	{}

	void set_atagname(char * a); // 깊은 복사 위한 함수, 단순

	void set_apParrent(SVGObject *parent);

	void set_apChildList(SVGObjectList *list);

	void set_nextnode(SVGObject * pobj); // nextnode에 대입
	
	void set_atrlist(SVGAttributeList*);

	SVGAttributeList * get_atrlist();


	char* get_name();

	SVGObject *get_apParent();

	SVGObject * get_nextnode() const;

	SVGObject * get_prenode() const; // prenode의 주소를 반환
	
	void set_prenode(SVGObject * pobj); // prenode의 주소를 대입

	SVGObjectList * get_apChildList();

	void AppendChild(SVGObject* pChild); // 자녀 object를 추가하는 함수

	void AddAttribute(SVGAttribute * pAttribute); // attribute를 추가하는 함수

	~SVGObject() // 깊은 복사시에 동적 할당된 이름을 해제한다.
	{
		if (in_name != 0)
		{
			delete[]aTagName;
		}

	}
};
