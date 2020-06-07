
////////////
/////////////


#pragma once

#include <iostream>
#include <string>
#include <cstring>

using std::string;


class SVGAttribute
{
private :
	char * aName; // ��ü�� �� �������� �̸�
	string aValue; // �������� ��
	float x; // tattr�� ���� ���� transform�� x��
	float y; //tattr�� ���� ���� transform�� y��
	SVGAttribute * prenode;
	SVGAttribute * nextnode;

public:
	SVGAttribute() : aName(NULL), prenode(NULL), nextnode(NULL), x(0), y(0)
	{
		aValue = "";
	};
	SVGAttribute(char * myname, string myvalue) :aName(myname), aValue(myvalue), prenode(NULL), nextnode(NULL), x(0),y(0) // �̸��� ���� �Բ� ȣ��� ���� ������
	{};


	void set_attribute(char * myname, string myvalue) ;
	char* get_aName();

	float get_x();
	float get_y();
	void set_x(float);
	void set_y(float);
	
	string get_aValue();
	void set_aName(char *);
	void set_aValue(string);
	SVGAttribute* get_prenode();
	SVGAttribute * get_nextnode();
	void set_prenode(SVGAttribute * psel);
	void set_nextnode(SVGAttribute * psel);
	~SVGAttribute()
	{
		delete aName;
		
		
	}
};

