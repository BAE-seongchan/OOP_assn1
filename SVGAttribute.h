
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
	char * aName; // 객체에 들어갈 데이터의 이름
	string aValue; // 데이터의 값
	float x; // tattr을 통해 들어올 transform의 x값
	float y; //tattr을 통해 들어올 transform의 y값
	SVGAttribute * prenode;
	SVGAttribute * nextnode;

public:
	SVGAttribute() : aName(NULL), prenode(NULL), nextnode(NULL), x(0), y(0)
	{
		aValue = "";
	};
	SVGAttribute(char * myname, string myvalue) :aName(myname), aValue(myvalue), prenode(NULL), nextnode(NULL), x(0),y(0) // 이름과 값과 함께 호출될 때의 생성자
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

