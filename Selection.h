
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
	SVGObject* apSVGObject; // ���õ� ��ü
	Selection * prenode; // ����Ʈ���� ���� ������
	Selection * nextnode; // ����Ʈ���� ���� ������
public:
	Selection() : apSVGObject(NULL),prenode(NULL),nextnode(NULL) // ������
	{}
	void set_selction(SVGObject * input); 
	Selection* get_prenode();
	Selection * get_nextnode();
	SVGObject* get_abSVGObject();
	void set_prenode(Selection * psel);
	void set_nextnode(Selection * psel);
};
