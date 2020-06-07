
////////////
/////////////

#pragma once
#include <cstring>
#include <string>

class help;

class helplist
{
private:
	help* apHead; // 리스트의 가장 앞에 있는 객체
	help * apTail; //가장 뒤에 있는 객체
	int aSize; // 리스트의 크기

public:
	helplist() : aSize(0), apHead(NULL), apTail(NULL)
	{
	}
	void AddHelp(help*); // 리스트에 명령 객체를 추가

	void RemoveHelp(help*); // 리스트에서 명령객체를 제거

	int get_aSize();

	help *get_head();

	help *get_tail();

	void Clear();

	~helplist() // 삭제시 리스트 안의 셀렉션들 동적할당해제
	{
		if (apHead != NULL)
		{
			while (apHead != apTail)
			{
				help* temp = apHead;
				apHead = apHead->get_nextnode();
				delete temp;
			}
			delete apHead;
		}

	}
};