
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
		// 처음 들어온 Object를 첫 주소로 하고, 들어온 object의 next node를 초기화

		aSize++; // node 갯수 증가
	}
	else
	{
		pSelection->set_prenode(apTail); // tail을 object의 prenode로 연결
		apTail->set_nextnode(pSelection); // tail의 next node를 object로 연결
		apTail = pSelection; // tail을 최근에 들어온 object로 변경
		pSelection->set_nextnode(NULL);
		aSize++; // node 갯수 증가
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
		apTail = pSelection->get_prenode(); // tail을 앞의 걸로 바꿔줌
		apTail->set_nextnode(NULL); // 새로운 TAIL의 NEXT NODE를 초기화해줌
		pSelection->set_prenode(NULL); // pObject의 pre node를 초기화 해줌
		aSize--;
	}
	else if (pSelection != apHead && pSelection != apTail && pSelection->get_nextnode() != NULL && pSelection->get_prenode() != NULL)
		//HEAD와 TAIL이 아니면서, LINK 되어 있는 경우
	{
		pSelection->get_prenode()->set_nextnode(pSelection->get_nextnode()); // object의 prenode의 nextnode를 object의 nextnode로 연결
		pSelection->get_nextnode()->set_prenode(pSelection->get_prenode()); // object의 nextnode의 prenode를 object의 prenode로 연결

		pSelection->set_prenode(NULL);
		pSelection->set_nextnode(NULL); // pObject의 연결을 모두 끊음
		aSize--;
	}
	delete pSelection; // SELECTION 동적할당 해제
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