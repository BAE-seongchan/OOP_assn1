
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
		// 처음 들어온 Object를 첫 주소로 하고, 들어온 object의 next node를 초기화

		aSize++; // node 갯수 증가
	}
	else
	{
		pObject->set_prenode(apTail); // tail을 object의 prenode로 연결
		apTail->set_nextnode(pObject); // tail의 next node를 object로 연결
		apTail = pObject; // tail을 최근에 들어온 object로 변경
		pObject->set_nextnode(NULL);
		aSize++; // node 갯수 증가
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
			//head를 제거하는 경우에 리스트 안에 객체가 하나만 있으면, apTail=apHead이므로 tail도 초기화
		}

		aSize--;
		
	}
	else if (pObject == apTail)
	{
		apTail = pObject->get_prenode(); // tail을 앞의 걸로 바꿔줌
		apTail->set_nextnode(NULL); // 새로운 TAIL의 NEXT NODE를 초기화해줌
		pObject->set_prenode(NULL); // pObject의 pre node를 초기화 해줌
		aSize--;
	}
	else if (pObject != apHead && pObject != apTail && pObject->get_nextnode() != NULL && pObject->get_prenode() != NULL)
		//HEAD와 TAIL이 아니면서, LINK 되어 있는 경우
	{
		pObject->get_prenode()->set_nextnode(pObject->get_nextnode()); 
		// object의 prenode의 nextnode를 object의 nextnode로 연결
		pObject->get_nextnode()->set_prenode(pObject->get_prenode()); 
		// object의 nextnode의 prenode를 object의 prenode로 연결

		pObject->set_prenode(NULL);
		pObject->set_nextnode(NULL); // pObject의 연결을 모두 끊음
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
