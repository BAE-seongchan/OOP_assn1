
////////////
/////////////
#include <iostream>
#include <cstring>
#include <string>

#include "help.h"

char* help::get_command()
{
	return command;
}
char* help::get_usage()
{
	return usage;
}
char* help::get_conditon()
{
	return condition;
}
char* help::get_description()
{
	return description;
}

help  * help::get_prenode()
{
	return prenode;
}

help * help::get_nextnode()
{
	return nextnode;
}
void help::set_prenode(help* help)
{
	prenode = help;
}

void help::set_nextnode(help* help)
{
	nextnode = help;
}