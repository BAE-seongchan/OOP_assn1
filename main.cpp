
////////////
/////////////

#include <iostream>
#include <cstring>
#include <string>
#include <fstream>
#include "Selection.h"
#include "SelectionList.h"
#include "SVGAttribute.h"
#include "SVGAttributeList.h"
#include "SVGObject.h"
#include "SVGObjectList.h"
#include "help.h"
#include "helplist.h"

using namespace std;

int if_in_sellist(SVGObject * object, SelectionList * list)
// seletionlist�� object�� �ִ��� Ȯ���ϴ� �Լ�
{
	int n=0;
	Selection * selection = list->get_head(); // list�� head�� �޾� �����Ѵ�.
	SVGObject* obj_in_list;
	for (; selection!= NULL;)
	{
		obj_in_list = selection->get_abSVGObject(); 
		// ���� �����ǿ� ����� ��ü�� �޴´�.
		if (object == obj_in_list)
		{
			n++; // �����ǿ� �ش��ϴ� ������Ʈ�� ������ ���� ���δ�.
		}
		selection = selection->get_nextnode();
		
	}
	return n;
} 

void cout_html_code(int ifin, SVGObject * object, int generation, SelectionList *selectionlist)
//svgƮ���� ǥ��������ִ� �Լ�
{

	for (int i = 0; i < generation; i++)
	{
		cout << "\t";
	}
	if (ifin == 1)
	{
		cout << "*";
	}
	cout << "<" << object->get_name();

	SVGAttribute * temp; // object ���� attribute�� ����
	if (object->get_atrlist() != NULL) //attribute�� �ִ� ��� ����Ѵ�.
	{
		temp = object->get_atrlist()->get_head();
		if (temp != NULL)
		{

			while (temp != NULL)
			{
				cout << " ";
				if (temp->get_aName() != NULL)
				{
					cout << temp->get_aName();
				}
				if (temp->get_aValue().compare("")!=0)
				{
					cout << "=" << '"' << temp->get_aValue() << '"';
				}
				if (!strcmp(temp->get_aName(), "transform"))
				{
					cout << fixed;
					cout.precision(6);
					
					cout << "=translate(" << temp->get_x() <<","<< temp->get_y() << ')' << '"';
				}
				temp = temp->get_nextnode();
			}

		}
	}
	cout << ">";

	if (object->get_apChildList() != NULL)// child�� �ִ°�� child�� ȣ���Ѵ�.
	{
		cout << "\n";
		generation++; // child�� �Ѿ���Ƿ� ���뿡 1�� ���Ѵ�.
		cout_html_code(if_in_sellist(object->get_apChildList()->get_Head(), selectionlist), object->get_apChildList()->get_Head(), generation, selectionlist);
		// ���� ��ü�� �ڽļ��� �� ���� �տ� �ִ� ��ü�� �Ű��������Ͽ� ����Լ��� ȣ���Ѵ�.
		generation--;
		// �ڽļ����� ȣ���� �������Ƿ�, ���븦 ������.
	}

	if (object->get_apChildList() == NULL) 
	// child�� ����, ������������ ��� html code�� �ݴ´�. 
	{
		cout << "</" << object->get_name() << ">";
		if (object->get_nextnode() == NULL)
		{
			cout << "\n";
		}
	}

	if (object->get_apChildList() != NULL)
	// �θ𼼴�� ȣ���� �Ѿ����, svg ��ü�� �ݴ´�.
	{
		for (int i = 0; i < generation; i++)
		{
			cout << "\t";
		}
		cout << "</" << object->get_name() << ">"; //</��ü�̸�>�� ���
		if (object->get_nextnode() == NULL) // �������뿡�� �������� ��� ���͸� ħ
		{
			cout << "\n";
		}
	}

	if (object->get_nextnode() != NULL) // ���� ���뿡 ���� ��尡 �ִ� ��� �������� �Լ� ȣ��
	{

		cout << "\n";
		cout_html_code(if_in_sellist(object->get_nextnode(), selectionlist), object->get_nextnode(), generation, selectionlist);
	
	}
	
	
	
}
void cout_html_nostar(int ifin, SVGObject * object, int generation, SelectionList *selectionlist)
//svgƮ���� ǥ��������ִ� �Լ�, ���� ǥ�� ����
{

	for (int i = 0; i < generation; i++)
	{
		cout << "\t";
	}
	
	cout << "<" << object->get_name();

	SVGAttribute * temp; // object ���� attribute�� ����
	if (object->get_atrlist() != NULL) //attribute�� �ִ� ��� ����Ѵ�.
	{
		temp = object->get_atrlist()->get_head();
		if (temp != NULL)
		{

			while (temp != NULL)
			{
				cout << " ";
				if (temp->get_aName() != NULL)
				{
					cout << temp->get_aName();
				}
				if (temp->get_aValue().compare("") != 0)
				{
					cout << "=" << '"' << temp->get_aValue() << '"';
				}
				if (!strcmp(temp->get_aName(), "transform"))
				{
					cout << fixed;
					cout.precision(6);

					cout << "=translate(" << temp->get_x() << "," << temp->get_y() << ')' << '"';
				}
				temp = temp->get_nextnode();
			}

		}
	}
	cout << ">";

	if (object->get_apChildList() != NULL)// child�� �ִ°�� child�� ȣ���Ѵ�.
	{
		cout << "\n";
		generation++;
		cout_html_nostar(if_in_sellist(object->get_apChildList()->get_Head(), selectionlist), object->get_apChildList()->get_Head(), generation, selectionlist);
		generation--;
	}

	if (object->get_apChildList() == NULL) // child�� ����, ������������ ��� html code�� �ݴ´�.
	{
		cout << "</" << object->get_name() << ">";
		if (object->get_nextnode() == NULL)
		{
			cout << "\n";
		}
	}

	if (object->get_apChildList() != NULL)
	{
		for (int i = 0; i < generation; i++)
		{
			cout << "\t";
		}
		cout << "</" << object->get_name() << ">";
		if (object->get_nextnode() == NULL)
		{
			cout << "\n";
		}
	}

	if (object->get_nextnode() != NULL)
	{

		cout << "\n";
		cout_html_nostar(if_in_sellist(object->get_nextnode(), selectionlist), object->get_nextnode(), generation, selectionlist);

	}



}

int remove(SVGObject* object_remove, SVGObject * root) // �ڽ� ����(child)�� ��(next node)�� �ִ� object ��� �����ϴ� �Լ�, list->head()
{

	SVGObject * temp;

	if (object_remove == root) // li
	{
		//root �̹Ƿ� ����
		return 0;
	}

	else
	{
		if (object_remove->get_apChildList() != NULL) // child�� �ִ� ���
		{
			temp = object_remove->get_apChildList()->get_Head();
			remove(temp, root); // child list�� head�� remove ȣ��
		}
		if (object_remove->get_apChildList() == NULL)// child�� ���°��
		{
			if (object_remove->get_nextnode() != NULL) //next node�� �ִ� ���
			{
				remove(object_remove->get_nextnode(), root); // ���� ���� remove ȣ��
			}
			if(object_remove->get_nextnode() == NULL) //child��, next node�� ���� ���
			{
				object_remove->get_apParent()->get_apChildList()->RemoveSvgObject(object_remove);
				//parent�� apChildlist�� �����Ͽ� object�� �����Ѵ�.
				if (object_remove->get_apParent()->get_apChildList()->get_aSize() == 0)
				//apChildlist�� �ƹ��͵� ���� ���, apChildlist�� �����Ѵ�.
				{
					object_remove->get_apParent()->set_apChildList(NULL);
				}
			}
		}
	}
}
void add_attribute(Selection* current_selection, char* new_tagname, string value, float x = 0, float y = 0)
// attribute ������ ���޹޾� �����ϴ� �Լ�
		{

			SVGObject * current_object;
			SVGAttributeList * new_attributelist;
			SVGAttribute * current_attribute;
			SVGAttribute * new_attribute;

			current_object = current_selection->get_abSVGObject();

			if (current_object->get_atrlist() == NULL)
			{
				new_attributelist = new SVGAttributeList; // attributelist �Ҵ�
				current_object->set_atrlist(new_attributelist); // attribute list�� objet ���� apattributelist�� ����
																// current_object �ȿ� attribute list�� ���� ��� �̸� �Ҵ��� �ش�.
				current_attribute = new SVGAttribute; //�׸��� current_attribute�� �Ҵ��� �ش�.
				current_attribute->set_aName(new_tagname);
				if (!strcmp(new_tagname, "transform"))
				{
					current_attribute->set_x(x);
					current_attribute->set_y(y);
				}
				else
				{
					current_attribute->set_aValue(value);
				}
				current_object->AddAttribute(current_attribute); // current_attribute�� �������ְ�, apAttributelist�� �����Ѵ�.

			}
			else //current_object �ȿ� attribute list�� �ִ� ���
			{
				current_attribute = current_object->get_atrlist()->get_head();
				if (current_attribute != NULL) // attribute list �ȿ� atribute �׸��� �ִ� ���
				{
					int count = 0;
					while (current_attribute != NULL)
					{
						if (!strcmp(current_attribute->get_aName(), new_tagname)) // attribute �׸� �� �ش��ϴ� ���� ������ ���� ���� �ִ°��
						{
							if (!strcmp(new_tagname, "transform"))
							{
								current_attribute->set_x(x);
								current_attribute->set_y(y);
							}
							else
							{
								current_attribute->set_aValue(value);
							}
							count++;
						}


						current_attribute = current_attribute->get_nextnode();
					}
					if (count == 0) // ���� �̸��� ���� attribute�� ���� ���, attrubute�� �Ҵ����ش�.
					{
						current_attribute = new SVGAttribute; //�׸��� current_attribute�� �Ҵ��� �ش�.
						current_attribute->set_aName(new_tagname);
						if (!strcmp(new_tagname, "transform"))
						{
							current_attribute->set_x(x);
							current_attribute->set_y(y);
						}
						else
						{
							current_attribute->set_aValue(value);
						}
						current_object->AddAttribute(current_attribute);// current_attribute�� �������ְ�, apAttributelist�� �����Ѵ�.
					}
				}
				else // attributelist�� ������ attribute �׸��� ���� ���
				{

					current_attribute = new SVGAttribute; //�׸��� current_attribute�� �Ҵ��� �ش�.
					current_attribute->set_aName(new_tagname);
					if (!strcmp(new_tagname, "transform"))
					{
						current_attribute->set_x(x);
						current_attribute->set_y(y);
					}
					else
					{
						current_attribute->set_aValue(value);
					}
					current_object->AddAttribute(current_attribute);// current_attribute�� �������ְ�, apAttributelist�� �����Ѵ�.
				}

			}
		}


void fout_html_code(int ifin, SVGObject * object, int generation, SelectionList *selectionlist, ofstream *WriteFile)
//svg Ʈ���� ������ִ� �Լ�
{

	for (int i = 0; i < generation ;i++)
	{
		(*WriteFile) << "\t";
	}
	if (ifin == 1)
	{
	
	}
	(*WriteFile) << "<" << object->get_name();

	SVGAttribute * temp; // object ����attribute������
	if (object->get_atrlist() != NULL)
	{
		temp = object->get_atrlist()->get_head();
		if (temp != NULL)
		{

			while (temp != NULL)
			{
				(*WriteFile) << " ";
					if (temp->get_aName() != NULL)
					{
						(*WriteFile) << temp->get_aName();
					}
				if (temp->get_aValue().compare("")!=0)
				{
					(*WriteFile) << "=" << '"' << temp->get_aValue() << '"';
				}
				if (!strcmp(temp->get_aName(), "transform"))
				{
					(*WriteFile) << fixed;
					(*WriteFile).precision(6);

					(*WriteFile) << "=translate(" << temp->get_x() << "," << temp->get_y() << ')' << '"';
				}
				temp = temp->get_nextnode();
			}

		}
	}
	(*WriteFile) << ">";

		if (object->get_apChildList() != NULL)
		{
			(*WriteFile) << "\n";
				generation++;
			fout_html_code(if_in_sellist(object->get_apChildList()->get_Head(), selectionlist), object->get_apChildList()->get_Head(), generation, selectionlist,WriteFile);
			generation--;
		}
	if (object->get_apChildList() == NULL)
	{
		(*WriteFile) << "</" << object->get_name() << ">";
			if (object->get_nextnode() == NULL)
			{
				(*WriteFile) << "\n";
			}
	}


	if (object->get_apChildList() != NULL)
	{
		for (int i = 0; i < generation ;i++)
		{
			(*WriteFile) << "\t";
		}
		(*WriteFile) << "</" << object->get_name() << ">";
			if (object->get_nextnode() == NULL)
			{
				(*WriteFile) << "\n";
			}
	}
	if (object->get_nextnode() != NULL)
	{

		(*WriteFile) << "\n";
		fout_html_code(if_in_sellist(object->get_nextnode(), selectionlist), object->get_nextnode(), generation, selectionlist, WriteFile);

	}

}

void get_helpfile(helplist* helplist)
{
	helplist->Clear();
	ifstream ReadFile("help.csv");
	string line;
	help* new_help;
	char * sentence;
	char * command;
	char * usage;
	char * condition;
	char* description;
	int len_sentence;


	getline(ReadFile, line);


	while (ReadFile.peek() != EOF)
	{

		getline(ReadFile, line);
		const char * x = line.c_str();
		int f = strlen(x);
		sentence = new char[f + 1];
		strcpy(sentence, line.c_str());
		int j = 0;

		//while (1)
		{
			int count = 0;
			int length = strlen(sentence) + 1;
			for (int i = 0; i < length; i++) 
				// CSV ������ �д� �κ��̴�.
				// ������ �޾� �� ���ھ� �����鼭, ,�� ������ ������ \0���� �ٲ۴�.
				// �׷��� , ������ string�� ������ �Ǵµ� �̶� , �� ��ġ�� �����Ѵ�.
				// ,���� ,���� ���ڿ��� ������ �����Ѵ�.
			{
				if (sentence[i] == ',' && count == 0)
				{
					sentence[i] = '\0';
					command = new char[i - j + 1];
					strcpy(command, &sentence[j]);
					j = i + 1;
					count++;
				}
				if (sentence[i] == ',' && count == 1)
				{
					sentence[i] = '\0';
					usage = new char[i - j + 1];
					strcpy(usage, &sentence[j]);
					j = i + 1;
					count++;
				}
				if (sentence[i] == ',' && count == 2)
				{
					sentence[i] = '\0';
					condition = new char[i - j + 1];
					strcpy(condition, &sentence[j]);
					j = i + 1;
					count++;
				}
				if (count == 3)
				{
					description = new char[length + 1 - j];
					strcpy(description, &sentence[j]);
					new_help = new help(command, usage, condition, description);
					// ���ο� ���� ��ü�� �����.

					helplist->AddHelp(new_help);
					// ���ο� ���� ��ü�� ����Ʈ�� �����Ѵ�.
					count = 0;
					delete[]command;
					delete[]usage;
					delete[]condition;
					delete[]description; // �� ���� �Ҵ��ߴ� ������� �����Ѵ�.
				}
			}
			delete[]sentence;
		}

	}
	
}
//helplist�� �� ��ɾ��� ��� �ڷ���� ����Ѵ�

int select_help(helplist* helplist, char* command)
//Ư���� ��ɾ ���� �ڷ���� ����Ѵ�.
{
	int count = 0;
	help * current_help = helplist->get_head();
		while (current_help != NULL)
		{
			if (!strcmp(current_help->get_command(), command))
			{
				count++;
				cout << "[COMMAND]" << current_help->get_command() << '\n';
				cout << "[USAGE]" << current_help->get_usage() << '\n';
				cout << "[CONDITION]" << current_help->get_conditon() << '\n';
				cout << "[DESCRIPTION]" << current_help->get_description() << '\n';
			}
			current_help = current_help->get_nextnode();
		}
		return count;
}

int main()
{
	SVGObject root;
	{
		root.set_atagname("html");
	}//root object ����

	Selection* sel1;
	{
		sel1 = new Selection;

		sel1->set_selction(&root);
	}//selection �ʱ�ȭ 

	SelectionList s_list;
	{
		s_list.AddSelection(sel1);
	}//selection list �ʱ�ȭ

	SVGObjectList Generation;
	{
		Generation.AddSvgObject(&root); // generation ������ root�� ����
	}

	SelectionList selectionlist;
	{
		selectionlist.AddSelection(sel1);
	}
	helplist helplist;

	while (1)
	{
		char command[100];
		int a = 1;
		char c;
		char new_tagname[100]; //tagname�� �޾Ƽ� ������ ����
		int num = 0;
		string value;
	

		rewind(stdin);
		cout << "<SVGMaker> ";
		c=getchar();
		if(c=='\n') // ���͸� ġ�� ��� ó������ ���ư���.
		{
			continue;
		}
		else {
			command[0] = c; 
			cin>> &command[1];
			// ó�� ���� ���ڸ� ù ���ڷ� �ϰ�, ���� ���ڸ� �޴´�.
		}
				
		if (!strcmp(command,"append"))
		{
			
			 // child ������ ������ ����

			if (selectionlist.get_aSize() != 1)
			{
				get_helpfile(&helplist);
				select_help(&helplist, command);
				continue;
			}
			SVGObject* current_generation;
			
			cin >> new_tagname;
			if (getchar() == ' ')
			// ��ɾ� ���Ŀ� ������ �´ٸ� ������ ��ɾ� ���� ���ڴ� �����̽��� �Ǿ�� �Ѵ�,
			{

				cin >> value;
				num = atoi(value.c_str()); 
				if (num==0) 
				// string�� int�� ��ȯ���� ���� ���(���ڰ� �ƴ� ���� ���� ���) ���ܸ� ����Ѵ�.
				{
					get_helpfile(&helplist);
					select_help(&helplist, command);
					continue;
				}
				
			}
			else {
				
			}

			Selection * s_parent = selectionlist.get_tail(); // �θ𼼴� selection
			SVGObject * parent = (*s_parent).get_abSVGObject(); // parent object�� �ּ�
			char * name = parent->get_name();
			Selection * s_child=new Selection; // �ڳ༼�� selection

			SVGObject *child = new SVGObject; // �ڳ༼�� object �����Ҵ�
			(*child).set_atagname(new_tagname); //object �̸� ����
			(*child).set_apParrent(parent);//�ڳ༼�� object�� parent�� ����

			//int asize = ((*parent).get_apChildList()->get_aSize());
			if (parent->get_apChildList() == NULL)
			{
				(*parent).set_apChildList(new SVGObjectList); // childlist �����Ҵ�.
			}
			
			(*parent).AppendChild(child);//�Ҵ��� object�� parent�� apChildList�� ����.

			selectionlist.Clear();// selection list clear

			(*s_child).set_selction(child);//child selection ����
			
			selectionlist.AddSelection(s_child); //slelctionlist�� s_child �߰�

			for (int j = 0; j < num-1; j++)
			{
				s_child = new Selection;// �ڳ༼�� selection �����Ҵ�
				child = new SVGObject;
				// �ڳ༼�� object �����Ҵ�
				(*child).set_atagname(new_tagname); //object �̸� ����
				
				(*child).set_apParrent(parent);//�ڳ༼�� object�� parent�� ����
				(*parent).AppendChild(child); //ob parent�� apChildList������
				(*s_child).set_selction(child);//child selection ����

				selectionlist.AddSelection(s_child); //slelctionlist�� s_child �߰�			
			}
		
		
		}
		else if (!strcmp(command, "select"))
		{
			
			if (getchar() == '\n')
			{
				SVGObject * temp = &root;
				SVGObject * temp2 = &root;
				int generation = 0;
				int count = 0;
				
				while (temp2->get_apChildList() != NULL) // ���������� ������ �ݺ��Ѵ�.
				{
					temp2 = temp2->get_apChildList()->get_Head(); // 
					if(temp2 == NULL)
					{
						break;
					}
					count++;
				}
				cout_html_code(if_in_sellist(temp, &selectionlist), temp, generation, &selectionlist);
						
			}
			else
			{
				cin >> new_tagname;
				num = -1;
				if (getchar() != '\n')
				{
					cin >> value;
					num = atoi(value.c_str());

					if (num == 0)
					{
						get_helpfile(&helplist);
						select_help(&helplist, command);
						continue;
					}
				}

				
					Selection* current_selection = selectionlist.get_tail();
					SVGObject* temp = current_selection->get_abSVGObject();
					Selection* new_selection; // �����Ҵ��� selection
					
					if (temp->get_apChildList() == NULL)
					{
						get_helpfile(&helplist);
						select_help(&helplist, command);
						continue;
					}
					
					temp = temp->get_apChildList()->get_Head();

					int count = 0;
				if (num == -1) // num�� �״��, �� ���ڸ� �Է¹��� ���� ��� ��� �����Ѵ�.
				{
					
					while ( temp!=NULL)
					{	
						if (!strcmp(temp->get_name(), new_tagname)) 
							// ���� ������ ���� object�� �ڽ� object�� �̸��� ��ġ�ϴ� object�� �������� ����Ʈ�� �߰��Ѵ�.
						{
							new_selection = new Selection;
							new_selection->set_selction(temp);
							selectionlist.AddSelection(new_selection);
							count++; // ���õ� ������ ����ϱ� ���� count�� ����.
						} 
						temp = temp->get_nextnode();
					}

					if (count > 0) 
					{
						selectionlist.RemoveSelection(selectionlist.get_head());
						cout << count << " item(s) is selected.\n";
					} // �̸��� ������ object�� �ִ� ���
					else // �ش��ϴ� �̸��� ���� �� ���� ��� ������ ����Ѵ�.
					{
						get_helpfile(&helplist);
						select_help(&helplist, command);
						continue;
					}
				}
				else if (num !=0 && num!=-1) // ��°�� �Է¹��� ���
				{
					count = 0;
					int count2 = 0;
					while (temp != NULL)
					{
						if (!strcmp(temp->get_name(), new_tagname))
							//�̸��� ���� object���� ���ʷ� �� ���� ����.
						{
							count++;
						}
						if (count == num) // �ش������� �����ϴ� ��� ������ ����Ʈ�� �߰��Ѵ�.
						{
							new_selection = new Selection;
							new_selection->set_selction(temp);
							selectionlist.AddSelection(new_selection);
							count2++; // �ִ��� ������ Ȯ���Ѵ�.
						}
						else { temp = temp->get_nextnode(); }
					}
					
					if (count2 == 1) //�־����� �θ� �������� �����Ѵ�,
					{ selectionlist.RemoveSelection(selectionlist.get_head());
					cout << 1 << " item(s) is selected.\n";
					}
					else {
						get_helpfile(&helplist);
						select_help(&helplist, command);
					}
				}

			}

		}
		else if (!strcmp(command, "remove"))
		{
			Selection * temp;
			SVGObject * parent;
			Selection * selection;
			
			temp = selectionlist.get_head();
			if (selectionlist.get_head()->get_abSVGObject() == &root) // root�� ������� ���
			{
				get_helpfile(&helplist);
				select_help(&helplist, command);
				continue;
			}
			parent = temp->get_abSVGObject()->get_apParent();
			
			while (temp!=NULL)
			{
				if (temp->get_abSVGObject()->get_apChildList() != NULL)
				{
					remove(temp->get_abSVGObject()->get_apChildList()->get_Head(), &root);
				} // ���� ��� ����
				temp = temp->get_nextnode();
			}
			selectionlist.Clear_all();
			if (parent->get_apChildList()->get_Head() == NULL)
			//Child�� ��� ���ŵ� ��� apChildList�� �ʱ�ȭ�Ѵ�.
			{
				parent->set_apChildList(NULL);
			}
			selection = new Selection; 
			selection->set_selction(parent); //�������� �Ҵ��Ͽ�, parent�� �����Ѵ�.
			selectionlist.AddSelection(selection); // �������� �����Ǹ���Ʈ�� �߰��Ѵ�.
			
		}
		else if (!strcmp(command, "end"))
		{
			Selection * new_selection;
			SVGObject * parent = selectionlist.get_head()->get_abSVGObject()->get_apParent();
			// ���� �������� parent�� �����صд�.
			Selection * temp = selectionlist.get_head();
			Selection * temp_remove;
			if (temp->get_abSVGObject() == &root)
			{
				get_helpfile(&helplist);
				select_help(&helplist, command);
				continue;
			}
			while (temp != NULL)
			{
				temp_remove = temp;
				temp = temp->get_nextnode();
				selectionlist.RemoveSelection(temp_remove); 
			} //���� �������� ��� �����Ѵ�.
			new_selection = new Selection;
			new_selection->set_selction(parent);
			selectionlist.AddSelection(new_selection);
			//�θ𼿷����� �Ҵ��ϰ�, ����Ʈ�� �����Ѵ�.
		}
		else if (!strcmp(command,"exit"))
		{
			return 0;
		}
		else if (!strcmp(command, "cattr"))
		{
			Selection * current_selection = selectionlist.get_head();
			
			cin >> new_tagname;
			cin >> value;
			while (current_selection != NULL)
			{
				add_attribute(current_selection, new_tagname, value);
				current_selection = current_selection->get_nextnode();
			}
		}
		else if (!strcmp(command, "tattr"))
		{
			string x, y;
			float xin, yin;
			float count = 0;
			Selection * current_selection = selectionlist.get_head();
			SVGAttribute * current_attribute;
			cin >> x;
			cin >> y;
			xin = atof(x.c_str());
			yin = atof(x.c_str());

			if (xin == 0 || yin == 0)
			{
				get_helpfile(&helplist);
				select_help(&helplist, command);
				continue; // ����ó��
			}
			while (current_selection != NULL)
			{
				
				add_attribute(current_selection, "transform", "", xin*count, yin*count);
				current_selection = current_selection->get_nextnode();
				count++;
			}
			
		}
		else if (!strcmp(command, "print"))
		{	
			if (getchar() == '\n')
			{
				//print�� �Էµ� ��� �ۼ��� list�� ǥ�� ����Ѵ�.
				cout_html_nostar(if_in_sellist(&root, &selectionlist), &root, 0, &selectionlist); 
			}
			else {//print�� ���ϸ���� �Էµ� ��� �ۼ��� list�� ���Ϸ� ����Ѵ�.
				cin >> new_tagname;
				ofstream WriteFile;
				WriteFile.open(new_tagname, ios_base::out);
				fout_html_code(if_in_sellist(&root, &selectionlist), &root, 0, &selectionlist, &WriteFile);
				WriteFile.close();

				cout << '"' << new_tagname << '"' << " is created \n";
			}
			
		}
		else if (!strcmp(command, "help"))
		{
			
			get_helpfile(&helplist);

			if (getchar() == '\n') // help�� ģ ��� usage�� �� ����Ѵ�. 
			{
				help * current_help = helplist.get_head();
				
				while (current_help != NULL) 
				{
					cout << current_help->get_usage() << "\n";
					current_help = current_help->get_nextnode();
				}
			}
			else // ����̸��� �Է��� ��� �ش��ϴ� ��ɿ� ���� ������ ��� ����Ѵ�. 
			{
				cin >> new_tagname;
				if (select_help(&helplist, new_tagname) == 0) // �ش��ϴ� ����� ���°�� ����ó��
				{
					get_helpfile(&helplist);
					select_help(&helplist, command);
					continue;
				}

			}
		}
		else //���� ��ɾ� �Է½� �������
		{
			get_helpfile(&helplist);
			help * current_help = helplist.get_head();

			while (current_help != NULL)
			{
				cout << current_help->get_usage() << "\n";
				current_help = current_help->get_nextnode();
			}
		}
		}

	}
	
	
	
