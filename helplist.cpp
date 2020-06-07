
////////////
/////////////

#include <iostream>
#include "help.h"
#include "helplist.h"
#include <cstring>
#include <string>


int helplist::get_aSize()
{
	return aSize;
}
help*  helplist::get_head()
{
	return apHead;
}
help *helplist::get_tail()
{
	return apTail;
}
void  helplist:: AddHelp(help* pSelection)
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
void  helplist::RemoveHelp(help* pSelection)
{
	if (pSelection == apHead)
	{
		apHead = apHead->get_nextnode();
		if (aSize == 1)
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
void helplist::Clear()
{
	help *temp;
	int i = aSize;
	for (; apTail != NULL;)
	{
		temp = apTail;
		RemoveHelp(temp);
		i = aSize;
	}
}