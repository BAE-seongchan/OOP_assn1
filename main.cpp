
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
// seletionlist에 object가 있는지 확인하는 함수
{
	int n=0;
	Selection * selection = list->get_head(); // list의 head를 받아 저장한다.
	SVGObject* obj_in_list;
	for (; selection!= NULL;)
	{
		obj_in_list = selection->get_abSVGObject(); 
		// 현재 셀렉션에 저장된 객체를 받는다.
		if (object == obj_in_list)
		{
			n++; // 셀렉션에 해당하는 오브젝트가 있으면 글을 높인다.
		}
		selection = selection->get_nextnode();
		
	}
	return n;
} 

void cout_html_code(int ifin, SVGObject * object, int generation, SelectionList *selectionlist)
//svg트리를 표준출력해주는 함수
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

	SVGAttribute * temp; // object 내의 attribute를 본다
	if (object->get_atrlist() != NULL) //attribute가 있는 경우 출력한다.
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

	if (object->get_apChildList() != NULL)// child가 있는경우 child를 호출한다.
	{
		cout << "\n";
		generation++; // child로 넘어갔으므로 세대에 1을 더한다.
		cout_html_code(if_in_sellist(object->get_apChildList()->get_Head(), selectionlist), object->get_apChildList()->get_Head(), generation, selectionlist);
		// 현재 객체의 자식세대 중 가장 앞에 있는 객체를 매개변수로하여 재귀함수를 호출한다.
		generation--;
		// 자식세대의 호출이 끝났으므로, 세대를 내린다.
	}

	if (object->get_apChildList() == NULL) 
	// child가 없는, 마지막세대인 경우 html code를 닫는다. 
	{
		cout << "</" << object->get_name() << ">";
		if (object->get_nextnode() == NULL)
		{
			cout << "\n";
		}
	}

	if (object->get_apChildList() != NULL)
	// 부모세대로 호출이 넘어오면, svg 객체를 닫는다.
	{
		for (int i = 0; i < generation; i++)
		{
			cout << "\t";
		}
		cout << "</" << object->get_name() << ">"; //</객체이름>을 출력
		if (object->get_nextnode() == NULL) // 같은세대에서 마지막인 경우 엔터를 침
		{
			cout << "\n";
		}
	}

	if (object->get_nextnode() != NULL) // 같은 세대에 다음 노드가 있는 경우 다음노드로 함수 호출
	{

		cout << "\n";
		cout_html_code(if_in_sellist(object->get_nextnode(), selectionlist), object->get_nextnode(), generation, selectionlist);
	
	}
	
	
	
}
void cout_html_nostar(int ifin, SVGObject * object, int generation, SelectionList *selectionlist)
//svg트리를 표준출력해주는 함수, 선택 표시 제외
{

	for (int i = 0; i < generation; i++)
	{
		cout << "\t";
	}
	
	cout << "<" << object->get_name();

	SVGAttribute * temp; // object 내의 attribute를 본다
	if (object->get_atrlist() != NULL) //attribute가 있는 경우 출력한다.
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

	if (object->get_apChildList() != NULL)// child가 있는경우 child를 호출한다.
	{
		cout << "\n";
		generation++;
		cout_html_nostar(if_in_sellist(object->get_apChildList()->get_Head(), selectionlist), object->get_apChildList()->get_Head(), generation, selectionlist);
		generation--;
	}

	if (object->get_apChildList() == NULL) // child가 없고, 마지막세대인 경우 html code를 닫는다.
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

int remove(SVGObject* object_remove, SVGObject * root) // 자신 하위(child)와 뒤(next node)에 있는 object 모두 제거하는 함수, list->head()
{

	SVGObject * temp;

	if (object_remove == root) // li
	{
		//root 이므로 오류
		return 0;
	}

	else
	{
		if (object_remove->get_apChildList() != NULL) // child가 있는 경우
		{
			temp = object_remove->get_apChildList()->get_Head();
			remove(temp, root); // child list의 head로 remove 호출
		}
		if (object_remove->get_apChildList() == NULL)// child가 없는경우
		{
			if (object_remove->get_nextnode() != NULL) //next node가 있는 경우
			{
				remove(object_remove->get_nextnode(), root); // 다음 노드로 remove 호출
			}
			if(object_remove->get_nextnode() == NULL) //child도, next node도 없는 경우
			{
				object_remove->get_apParent()->get_apChildList()->RemoveSvgObject(object_remove);
				//parent의 apChildlist로 접근하여 object를 제거한다.
				if (object_remove->get_apParent()->get_apChildList()->get_aSize() == 0)
				//apChildlist에 아무것도 없을 경우, apChildlist를 해제한다.
				{
					object_remove->get_apParent()->set_apChildList(NULL);
				}
			}
		}
	}
}
void add_attribute(Selection* current_selection, char* new_tagname, string value, float x = 0, float y = 0)
// attribute 정보를 전달받아 저장하는 함수
		{

			SVGObject * current_object;
			SVGAttributeList * new_attributelist;
			SVGAttribute * current_attribute;
			SVGAttribute * new_attribute;

			current_object = current_selection->get_abSVGObject();

			if (current_object->get_atrlist() == NULL)
			{
				new_attributelist = new SVGAttributeList; // attributelist 할당
				current_object->set_atrlist(new_attributelist); // attribute list를 objet 안의 apattributelist에 대입
																// current_object 안에 attribute list가 없는 경우 이를 할당해 준다.
				current_attribute = new SVGAttribute; //그리고 current_attribute를 할당해 준다.
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
				current_object->AddAttribute(current_attribute); // current_attribute를 생성해주고, apAttributelist에 대입한다.

			}
			else //current_object 안에 attribute list가 있는 경우
			{
				current_attribute = current_object->get_atrlist()->get_head();
				if (current_attribute != NULL) // attribute list 안에 atribute 항목이 있는 경우
				{
					int count = 0;
					while (current_attribute != NULL)
					{
						if (!strcmp(current_attribute->get_aName(), new_tagname)) // attribute 항목 중 해당하는 값의 종류를 가진 값이 있는경우
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
					if (count == 0) // 같은 이름을 가진 attribute가 없는 경우, attrubute를 할당해준다.
					{
						current_attribute = new SVGAttribute; //그리고 current_attribute를 할당해 준다.
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
						current_object->AddAttribute(current_attribute);// current_attribute를 생성해주고, apAttributelist에 대입한다.
					}
				}
				else // attributelist는 있지만 attribute 항목은 없는 경우
				{

					current_attribute = new SVGAttribute; //그리고 current_attribute를 할당해 준다.
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
					current_object->AddAttribute(current_attribute);// current_attribute를 생성해주고, apAttributelist에 대입한다.
				}

			}
		}


void fout_html_code(int ifin, SVGObject * object, int generation, SelectionList *selectionlist, ofstream *WriteFile)
//svg 트리를 출력해주는 함수
{

	for (int i = 0; i < generation ;i++)
	{
		(*WriteFile) << "\t";
	}
	if (ifin == 1)
	{
	
	}
	(*WriteFile) << "<" << object->get_name();

	SVGAttribute * temp; // object 내의attribute를본다
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
				// CSV 파일을 읽는 부분이다.
				// 문장을 받아 한 글자씩 읽으면서, ,가 나오면 내용을 \0으로 바꾼다.
				// 그러면 , 단위로 string이 나뉘게 되는데 이때 , 의 위치를 저장한다.
				// ,부터 ,까지 문자열을 나눠서 저장한다.
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
					// 새로운 헬프 객체를 만든다.

					helplist->AddHelp(new_help);
					// 새로운 헬프 객체를 리스트에 저장한다.
					count = 0;
					delete[]command;
					delete[]usage;
					delete[]condition;
					delete[]description; // 각 순간 할당했던 문장들을 해제한다.
				}
			}
			delete[]sentence;
		}

	}
	
}
//helplist에 들어간 명령어의 모든 자료들을 출력한다

int select_help(helplist* helplist, char* command)
//특정한 명령어에 대한 자료들을 출력한다.
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
	}//root object 생성

	Selection* sel1;
	{
		sel1 = new Selection;

		sel1->set_selction(&root);
	}//selection 초기화 

	SelectionList s_list;
	{
		s_list.AddSelection(sel1);
	}//selection list 초기화

	SVGObjectList Generation;
	{
		Generation.AddSvgObject(&root); // generation 시작을 root로 잡음
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
		char new_tagname[100]; //tagname을 받아서 저장할 변수
		int num = 0;
		string value;
	

		rewind(stdin);
		cout << "<SVGMaker> ";
		c=getchar();
		if(c=='\n') // 엔터를 치는 경우 처음으로 돌아간다.
		{
			continue;
		}
		else {
			command[0] = c; 
			cin>> &command[1];
			// 처음 받은 글자를 첫 글자로 하고, 남은 문자를 받는다.
		}
				
		if (!strcmp(command,"append"))
		{
			
			 // child 갯수를 저장할 변수

			if (selectionlist.get_aSize() != 1)
			{
				get_helpfile(&helplist);
				select_help(&helplist, command);
				continue;
			}
			SVGObject* current_generation;
			
			cin >> new_tagname;
			if (getchar() == ' ')
			// 명령어 이후에 조건이 온다면 무조건 명령어 다음 글자는 스페이스가 되어야 한다,
			{

				cin >> value;
				num = atoi(value.c_str()); 
				if (num==0) 
				// string을 int로 변환하지 못한 경우(숫자가 아닌 값을 받은 경우) 예외를 출력한다.
				{
					get_helpfile(&helplist);
					select_help(&helplist, command);
					continue;
				}
				
			}
			else {
				
			}

			Selection * s_parent = selectionlist.get_tail(); // 부모세대 selection
			SVGObject * parent = (*s_parent).get_abSVGObject(); // parent object의 주소
			char * name = parent->get_name();
			Selection * s_child=new Selection; // 자녀세대 selection

			SVGObject *child = new SVGObject; // 자녀세대 object 동적할당
			(*child).set_atagname(new_tagname); //object 이름 대입
			(*child).set_apParrent(parent);//자녀세대 object의 parent에 대입

			//int asize = ((*parent).get_apChildList()->get_aSize());
			if (parent->get_apChildList() == NULL)
			{
				(*parent).set_apChildList(new SVGObjectList); // childlist 동적할당.
			}
			
			(*parent).AppendChild(child);//할당한 object를 parent의 apChildList에 대입.

			selectionlist.Clear();// selection list clear

			(*s_child).set_selction(child);//child selection 형성
			
			selectionlist.AddSelection(s_child); //slelctionlist에 s_child 추가

			for (int j = 0; j < num-1; j++)
			{
				s_child = new Selection;// 자녀세대 selection 동적할당
				child = new SVGObject;
				// 자녀세대 object 동적할당
				(*child).set_atagname(new_tagname); //object 이름 대입
				
				(*child).set_apParrent(parent);//자녀세대 object의 parent에 대입
				(*parent).AppendChild(child); //ob parent의 apChildList에대입
				(*s_child).set_selction(child);//child selection 형성

				selectionlist.AddSelection(s_child); //slelctionlist에 s_child 추가			
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
				
				while (temp2->get_apChildList() != NULL) // 마지막세대 전까지 반복한다.
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
					Selection* new_selection; // 동적할당할 selection
					
					if (temp->get_apChildList() == NULL)
					{
						get_helpfile(&helplist);
						select_help(&helplist, command);
						continue;
					}
					
					temp = temp->get_apChildList()->get_Head();

					int count = 0;
				if (num == -1) // num이 그대로, 즉 숫자를 입력받지 않은 경우 모두 선택한다.
				{
					
					while ( temp!=NULL)
					{	
						if (!strcmp(temp->get_name(), new_tagname)) 
							// 현재 셀렉션 안의 object의 자식 object중 이름이 일치하는 object의 셀렉션을 리스트에 추가한다.
						{
							new_selection = new Selection;
							new_selection->set_selction(temp);
							selectionlist.AddSelection(new_selection);
							count++; // 선택된 개수를 출력하기 위해 count를 센다.
						} 
						temp = temp->get_nextnode();
					}

					if (count > 0) 
					{
						selectionlist.RemoveSelection(selectionlist.get_head());
						cout << count << " item(s) is selected.\n";
					} // 이름이 동일한 object가 있는 경우
					else // 해당하는 이름을 가진 게 없는 경우 오류를 출력한다.
					{
						get_helpfile(&helplist);
						select_help(&helplist, command);
						continue;
					}
				}
				else if (num !=0 && num!=-1) // 번째를 입력받은 경우
				{
					count = 0;
					int count2 = 0;
					while (temp != NULL)
					{
						if (!strcmp(temp->get_name(), new_tagname))
							//이름이 같은 object들을 차례로 세 나아 간다.
						{
							count++;
						}
						if (count == num) // 해당조건을 만족하는 경우 셀렉션 리스트에 추가한다.
						{
							new_selection = new Selection;
							new_selection->set_selction(temp);
							selectionlist.AddSelection(new_selection);
							count2++; // 있는지 없는지 확인한다.
						}
						else { temp = temp->get_nextnode(); }
					}
					
					if (count2 == 1) //있었으면 부모 셀렉션을 제거한다,
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
			if (selectionlist.get_head()->get_abSVGObject() == &root) // root가 들어있을 경우
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
				} // 하위 모두 제거
				temp = temp->get_nextnode();
			}
			selectionlist.Clear_all();
			if (parent->get_apChildList()->get_Head() == NULL)
			//Child가 모두 제거된 경우 apChildList를 초기화한다.
			{
				parent->set_apChildList(NULL);
			}
			selection = new Selection; 
			selection->set_selction(parent); //셀렉션을 할당하여, parent를 대입한다.
			selectionlist.AddSelection(selection); // 셀렉션을 셀렉션리스트에 추가한다.
			
		}
		else if (!strcmp(command, "end"))
		{
			Selection * new_selection;
			SVGObject * parent = selectionlist.get_head()->get_abSVGObject()->get_apParent();
			// 현재 셀렉션의 parent를 저장해둔다.
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
			} //현재 셀렉션을 모두 제거한다.
			new_selection = new Selection;
			new_selection->set_selction(parent);
			selectionlist.AddSelection(new_selection);
			//부모셀렉션을 할당하고, 리스트에 저장한다.
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
				continue; // 오류처리
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
				//print만 입력된 경우 작성된 list를 표준 출력한다.
				cout_html_nostar(if_in_sellist(&root, &selectionlist), &root, 0, &selectionlist); 
			}
			else {//print에 파일명까지 입력된 경우 작성된 list를 파일로 출력한다.
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

			if (getchar() == '\n') // help만 친 경우 usage를 다 출력한다. 
			{
				help * current_help = helplist.get_head();
				
				while (current_help != NULL) 
				{
					cout << current_help->get_usage() << "\n";
					current_help = current_help->get_nextnode();
				}
			}
			else // 명령이름을 입력한 경우 해당하는 명령에 대한 설명을 모두 출력한다. 
			{
				cin >> new_tagname;
				if (select_help(&helplist, new_tagname) == 0) // 해당하는 명령이 없는경우 예외처리
				{
					get_helpfile(&helplist);
					select_help(&helplist, command);
					continue;
				}

			}
		}
		else //없는 명령어 입력시 도움말출력
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
	
	
	
