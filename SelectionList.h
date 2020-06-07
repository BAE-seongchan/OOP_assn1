
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
	Selection* apHead ; // list���� ���� �տ��ִ� ��ü�� �ּ�
	Selection * apTail; // ���� �ڿ� �ִ� ��ü�� �ּ�
	int aSize;

public:
	SelectionList() : aSize(0), apHead(NULL),apTail(NULL)
	{
	}
	void AddSelection(Selection* pSelection); // ����Ʈ�� �ش� selection�� �߰�

	void RemoveSelection(Selection* pSelection); // ����Ʈ���� �ش� �������� ����

	int get_aSize();

	Selection *get_head();

	Selection *get_tail();

	void Clear(); // ����Ʈ�� ����� ������ ��� ����
	void Clear_all(); // �����ǰ� �Բ�, ������ ���� ��ü�� ����
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

