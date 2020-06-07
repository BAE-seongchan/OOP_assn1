
////////////
/////////////

#pragma once
#include <cstring>
#include <string>


#include <iostream>

class SVGObject;

class Selection
{
private:
	SVGObject* apSVGObject; // 선택된 객체
	Selection * prenode; // 리스트에서 이전 셀렉션
	Selection * nextnode; // 리스트에서 다음 셀렉션
public:
	Selection() : apSVGObject(NULL),prenode(NULL),nextnode(NULL) // 생성자
	{}
	void set_selction(SVGObject * input); 
	Selection* get_prenode();
	Selection * get_nextnode();
	SVGObject* get_abSVGObject();
	void set_prenode(Selection * psel);
	void set_nextnode(Selection * psel);
};
