

////////////
/////////////
#pragma once
#include <iostream>
#include <cstring>
#include <string>

class help
{
private:
	char * command; // ���
	char * usage; // �뵵
	char * condition; //��� ��밡���� ����
	char * description; // ��ɿ� ���� ���
	help * prenode;
	help * nextnode;

public:
	help(char * mycommand, char * myusage, char* mycondition, char * mydescription) : prenode(NULL),nextnode(NULL) // ���� ���� �˰���
	{
		command = new char[strlen(mycommand) + 1];
		strcpy(command, mycommand);
		usage = new char[strlen(myusage) + 1];
		strcpy(usage, myusage);
		condition = new char[strlen(mycondition) + 1];
		strcpy(condition, mycondition);
		description = new char[strlen(mydescription) + 1];
		strcpy(description, mydescription);
	}
	char* get_command();
	char* get_usage();
	char* get_conditon();
	char* get_description();
	help  * get_prenode();
	help * get_nextnode();
	void set_prenode(help *);
	void set_nextnode(help *);

	~help()
	{
		if (command != NULL)
		{
			delete []command;
			delete []usage;
			delete []condition;
			delete []description;
		}
		
	}
};