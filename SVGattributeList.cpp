
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
		// ó�� ���� Object�� ù �ּҷ� �ϰ�, ���� object�� next node�� �ʱ�ȭ

		aSize++; // node ���� ����
	}
	else
	{
		pAttribute->set_prenode(apTail); // tail�� object�� prenode�� ����
		apTail->set_nextnode(pAttribute); // tail�� next node�� object�� ����
		apTail = pAttribute; // tail�� �ֱٿ� ���� object�� ����
		pAttribute->set_nextnode(NULL);
		aSize++; // node ���� ����
	}
}