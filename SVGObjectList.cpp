
////////////
/////////////


#include "Selection.h"
#include "SelectionList.h"
#include "SVGAttribute.h"
#include "SVGAttributeList.h"
#include "SVGObject.h"
#include "SVGObjectList.h"
#include <iostream>
#include <cstring>
#include <string>


SVGObject * SVGObjectList::get_Head()
{
	return apHead;
}
SVGObject * SVGObjectList::get_Tail()
{
	return apTail;
}

void SVGObjectList::AddSvgObject(SVGObject* pObject)
{

	if (aSize == 0)
	{
		apHead = pObject;
		apTail = pObject;
		pObject->set_prenode(NULL);
		pObject->set_nextnode(NULL);
		// ó�� ���� Object�� ù �ּҷ� �ϰ�, ���� object�� next node�� �ʱ�ȭ

		aSize++; // node ���� ����
	}
	else
	{
		pObject->set_prenode(apTail); // tail�� object�� prenode�� ����
		apTail->set_nextnode(pObject); // tail�� next node�� object�� ����
		apTail = pObject; // tail�� �ֱٿ� ���� object�� ����
		pObject->set_nextnode(NULL);
		aSize++; // node ���� ����
	}

}
int SVGObjectList::get_aSize()
{
	return aSize;
}
void SVGObjectList::RemoveSvgObject(SVGObject * pObject)
{
	if (pObject == apHead)
	{
		apHead = apHead->get_nextnode(); 
		if (aSize == 1)
		{
			apTail = NULL; 
			//head�� �����ϴ� ��쿡 ����Ʈ �ȿ� ��ü�� �ϳ��� ������, apTail=apHead�̹Ƿ� tail�� �ʱ�ȭ
		}

		aSize--;
		
	}
	else if (pObject == apTail)
	{
		apTail = pObject->get_prenode(); // tail�� ���� �ɷ� �ٲ���
		apTail->set_nextnode(NULL); // ���ο� TAIL�� NEXT NODE�� �ʱ�ȭ����
		pObject->set_prenode(NULL); // pObject�� pre node�� �ʱ�ȭ ����
		aSize--;
	}
	else if (pObject != apHead && pObject != apTail && pObject->get_nextnode() != NULL && pObject->get_prenode() != NULL)
		//HEAD�� TAIL�� �ƴϸ鼭, LINK �Ǿ� �ִ� ���
	{
		pObject->get_prenode()->set_nextnode(pObject->get_nextnode()); 
		// object�� prenode�� nextnode�� object�� nextnode�� ����
		pObject->get_nextnode()->set_prenode(pObject->get_prenode()); 
		// object�� nextnode�� prenode�� object�� prenode�� ����

		pObject->set_prenode(NULL);
		pObject->set_nextnode(NULL); // pObject�� ������ ��� ����
		aSize--;
	}

	
}
	void SVGObjectList::Clear()
	{
		SVGObject *temp;
		int i = aSize; 
		for (; apTail != NULL;)
		{
			temp = apTail;
			RemoveSvgObject(temp); 
			i = aSize;
		}
	}
