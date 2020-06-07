
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

SVGAttribute* SVGAttributeList::get_head()
{
	return apHead;
}
SVGAttribute* SVGAttributeList::get_tail()
{
	return apTail;
}

void SVGAttributeList::AddSvgAttribute(SVGAttribute * pAttribute)
{

	if (aSize == 0)
	{
		apHead = pAttribute;
		apTail = pAttribute;
		pAttribute->set_prenode(NULL);
		pAttribute->set_nextnode(NULL);
		// 처음 들어온 Object를 첫 주소로 하고, 들어온 object의 next node를 초기화

		aSize++; // node 갯수 증가
	}
	else
	{
		pAttribute->set_prenode(apTail); // tail을 object의 prenode로 연결
		apTail->set_nextnode(pAttribute); // tail의 next node를 object로 연결
		apTail = pAttribute; // tail을 최근에 들어온 object로 변경
		pAttribute->set_nextnode(NULL);
		aSize++; // node 갯수 증가
	}
}