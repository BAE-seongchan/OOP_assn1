
////////////
/////////////


#include "Selection.h"
#include "SelectionList.h"
#include "SVGAttribute.h"
#include "SVGAttributeList.h"
#include "SVGObject.h"
#include "SVGObjectList.h"
#include <cstring>
#include <string>

#include <iostream>
void SVGObject::set_atagname(char * a)
{
	aTagName = new char[strlen(a)+1];
	strcpy(aTagName, a);
	in_name++;
}
void SVGObject :: set_apParrent(SVGObject *parent)
{
	apParent = parent;
}
void SVGObject :: set_apChildList(SVGObjectList *list)
{
	apChildList = list;
}
SVGObject * SVGObject:: get_nextnode() const // nextnode를 반환
{
	return nextnode;
}
SVGAttributeList * SVGObject::get_atrlist()
{
	return apAttributeList;
}

void SVGObject::set_nextnode(SVGObject * pobj) // nextnode에 대입
{
	nextnode = pobj;
}
SVGObject * SVGObject::get_prenode() const // prenode의 주소를 반환
{
	return prenode;
}
void SVGObject::set_prenode(SVGObject * pobj) // prenode의 주소를 대입
{
	prenode = pobj;
}

SVGObject * SVGObject:: get_apParent()
{
	return apParent;
}

void SVGObject::AppendChild(SVGObject* pChild)
{
	apChildList->AddSvgObject(pChild); // apChildList에 pChild 대입
}
SVGObjectList * SVGObject::get_apChildList()
{
	return apChildList;
}
char* SVGObject::get_name()

{
	return aTagName;
}

void SVGObject::AddAttribute(SVGAttribute * pAttribute)
{
	apAttributeList->AddSvgAttribute(pAttribute);
}

void SVGObject::set_atrlist(SVGAttributeList* LIST)
{
	apAttributeList = LIST;
}