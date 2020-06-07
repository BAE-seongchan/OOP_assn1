
////////////
/////////////


#pragma once

#include <iostream>
#include <cstring>
#include <string>

class Selection;

class SelectionList
{
private:
	Selection* apHead ; // list에서 가장 앞에있는 객체의 주소
	Selection * apTail; // 가장 뒤에 있는 객체의 주소
	int aSize;

public:
	SelectionList() : aSize(0), apHead(NULL),apTail(NULL)
	{
	}
	void AddSelection(Selection* pSelection); // 리스트에 해당 selection을 추가

	void RemoveSelection(Selection* pSelection); // 리스트에서 해당 셀렉션을 제거

	int get_aSize();

	Selection *get_head();

	Selection *get_tail();

	void Clear(); // 리스트에 저장된 셀렉션 모두 제거
	void Clear_all(); // 셀렉션과 함께, 셀렉션 안의 객체도 제거
	~SelectionList()
	{
		Selection* temp;
		if (apHead != NULL)
		{
			temp = apHead;
			while (apHead != apTail)
			{
				apHead = apHead->get_nextnode();
				delete temp;
				temp = apHead;
			}
			
		}

	}
	

};

