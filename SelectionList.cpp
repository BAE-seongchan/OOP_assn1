
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



int SelectionList::get_aSize()
{
	return aSize;
}
Selection* SelectionList:: get_head()
{
	return apHead;
}
Selection* SelectionList:: get_tail()
{
	return apTail;
}
void SelectionList::AddSelection(Selection* pSelection)
{

	if (aSize == 0)
	{
		apHead = pSelection;
		apTail = pSelection;
		pSelection->set_prenode(NULL);
		pSelection->set_nextnode(NULL);
		// ó�� ���� Object�� ù �ּҷ� �ϰ�, ���� object�� next node�� �ʱ�ȭ

		aSize++; // node ���� ����
	}
	else
	{
		pSelection->set_prenode(apTail); // tail�� object�� prenode�� ����
		apTail->set_nextnode(pSelection); // tail�� next node�� object�� ����
		apTail = pSelection; // tail�� �ֱٿ� ���� object�� ����
		pSelection->set_nextnode(NULL);
		aSize++; // node ���� ����
	}
}
void SelectionList::RemoveSelection(Selection* pSelection)
{
	if (pSelection == apHead)
	{
		apHead = apHead->get_nextnode();
		if(aSize==1)
		{
			apTail = NULL;
		}
		
		aSize--;
	}
	else if (pSelection == apTail)
	{
		apTail = pSelection->get_prenode(); // tail�� ���� �ɷ� �ٲ���
		apTail->set_nextnode(NULL); // ���ο� TAIL�� NEXT NODE�� �ʱ�ȭ����
		pSelection->set_prenode(NULL); // pObject�� pre node�� �ʱ�ȭ ����
		aSize--;
	}
	else if (pSelection != apHead && pSelection != apTail && pSelection->get_nextnode() != NULL && pSelection->get_prenode() != NULL)
		//HEAD�� TAIL�� �ƴϸ鼭, LINK �Ǿ� �ִ� ���
	{
		pSelection->get_prenode()->set_nextnode(pSelection->get_nextnode()); // object�� prenode�� nextnode�� object�� nextnode�� ����
		pSelection->get_nextnode()->set_prenode(pSelection->get_prenode()); // object�� nextnode�� prenode�� object�� prenode�� ����

		pSelection->set_prenode(NULL);
		pSelection->set_nextnode(NULL); // pObject�� ������ ��� ����
		aSize--;
	}
	delete pSelection; // SELECTION �����Ҵ� ����
}

void SelectionList::Clear()
{
	Selection *temp;
	int i = aSize;
	for (; apTail != NULL;)
	{
		temp = apTail;
		RemoveSelection(temp);
		i = aSize;
	}
}

void SelectionList::Clear_all()
{
	Selection *temp;
	int i = aSize;
	for (; apTail != NULL;)
	{
		temp = apTail; 
		temp->get_abSVGObject()->get_apParent()->get_apChildList()->RemoveSvgObject(temp->get_abSVGObject());
		// parent�� childlist�� �����Ͽ� ���밣 ���Ḯ��Ʈ�� ������ ���´�.
		delete temp->get_abSVGObject();
		RemoveSelection(temp);
		i = aSize;
	}
}
