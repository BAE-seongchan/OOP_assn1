
////////////
/////////////


#include <iostream>
#include "SVGAttribute.h"
#include <string>
#include <cstring>
#include "Selection.h"
#include "SelectionList.h"
#include "SVGAttribute.h"
#include "SVGAttributeList.h"
#include "SVGObject.h"
#include "SVGObjectList.h"

void SVGAttribute::set_attribute(char * myname, string myvalue)
{
	aName = new char[strlen(myname) + 1];
	strcpy(aName,myname);
	aValue = myvalue;
};
float SVGAttribute::get_x()
{
	return x;
}
float SVGAttribute::get_y()
{
	return y;
}
void SVGAttribute::set_x(float myx)
{
	x = myx;
}
void SVGAttribute::set_y(float myy)
{
	y = myy;
}
char* SVGAttribute::get_aName()
{
	return aName;
}
string SVGAttribute::get_aValue()
{
	return aValue;
}
void SVGAttribute::set_aName(char *myname)
{
	aName = new char[strlen(myname) + 1];
	strcpy(aName, myname);
}
void SVGAttribute::set_aValue(string myvalue)
{
	aValue =myvalue;
}
SVGAttribute*  SVGAttribute::get_prenode()
{
	return prenode;
};
SVGAttribute *  SVGAttribute::get_nextnode()
{
	return nextnode;
};
void  SVGAttribute::set_prenode(SVGAttribute * psel)
{
	prenode = psel;
}
void  SVGAttribute::set_nextnode(SVGAttribute * psel)
{
	nextnode = psel;
}
