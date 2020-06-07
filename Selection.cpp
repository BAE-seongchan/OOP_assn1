
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


void Selection::set_selction(SVGObject * input)
{
	apSVGObject = input;
}
Selection* Selection::get_prenode()
{
	return prenode;
}
Selection * Selection::get_nextnode()
{
	return nextnode;
}

SVGObject* Selection::get_abSVGObject()
{
	return apSVGObject;
}

void Selection::set_prenode(Selection * psel)
{
	prenode = psel;
}
void Selection::set_nextnode(Selection * psel)
{
	nextnode = psel;
}