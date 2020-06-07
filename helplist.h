
////////////
/////////////

#pragma once
#include <cstring>
#include <string>

class help;

class helplist
{
private:
	help* apHead; // ����Ʈ�� ���� �տ� �ִ� ��ü
	help * apTail; //���� �ڿ� �ִ� ��ü
	int aSize; // ����Ʈ�� ũ��

public:
	helplist() : aSize(0), apHead(NULL), apTail(NULL)
	{
	}
	void AddHelp(help*); // ����Ʈ�� ��� ��ü�� �߰�

	void RemoveHelp(help*); // ����Ʈ���� ��ɰ�ü�� ����

	int get_aSize();

	help *get_head();

	help *get_tail();

	void Clear();

	~helplist() // ������ ����Ʈ ���� �����ǵ� �����Ҵ�����
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