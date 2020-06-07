
////////////
/////////////
// um is alive


#include <iostream>
#include "help.h"
#include "helplist.h"
#include <cstring>
#include <string>


int helplist::get_aSize()
{
	return aSize;
}
help*  helplist::get_head()
{
	return apHead;
}
help *helplist::get_tail()
{
	return apTail;
}
void  helplist:: AddHelp(help* pSelection)
{

	if (aSize == 0)
	{
		apHead = pSelection;
		apTail = pSelection;
		pSelection->set_prenode(NULL);
		pSelection->set_nextnode(NULL);
		// Ã³À½ µé¾î¿Â Object¸¦ Ã¹ ÁÖ¼Ò·Î ÇÏ°í, µé¾î¿Â objectÀÇ next node¸¦ ÃÊ±âÈ­

		aSize++; // node °¹¼ö Áõ°¡
	}
	else
	{
		pSelection->set_prenode(apTail); // tailÀ» objectÀÇ prenode·Î ¿¬°á
		apTail->set_nextnode(pSelection); // tailÀÇ next node¸¦ object·Î ¿¬°á
		apTail = pSelection; // tailÀ» ÃÖ±Ù¿¡ µé¾î¿Â object·Î º¯°æ
		pSelection->set_nextnode(NULL);
		aSize++; // node °¹¼ö Áõ°¡
	}
}
void  helplist::RemoveHelp(help* pSelection)
{
	if (pSelection == apHead)
	{
		apHead = apHead->get_nextnode();
		if (aSize == 1)
		{
			apTail = NULL;
		}

		aSize--;
	}
	else if (pSelection == apTail)
	{
		apTail = pSelection->get_prenode(); // tailÀ» ¾ÕÀÇ °É·Î ¹Ù²ãÁÜ
		apTail->set_nextnode(NULL); // »õ·Î¿î TAILÀÇ NEXT NODE¸¦ ÃÊ±âÈ­ÇØÁÜ
		pSelection->set_prenode(NULL); // pObjectÀÇ pre node¸¦ ÃÊ±âÈ­ ÇØÁÜ
		aSize--;
	}
	else if (pSelection != apHead && pSelection != apTail && pSelection->get_nextnode() != NULL && pSelection->get_prenode() != NULL)
		//HEAD¿Í TAILÀÌ ¾Æ´Ï¸é¼­, LINK µÇ¾î ÀÖ´Â °æ¿ì
	{
		pSelection->get_prenode()->set_nextnode(pSelection->get_nextnode()); // objectÀÇ prenodeÀÇ nextnode¸¦ objectÀÇ nextnode·Î ¿¬°á
		pSelection->get_nextnode()->set_prenode(pSelection->get_prenode()); // objectÀÇ nextnodeÀÇ prenode¸¦ objectÀÇ prenode·Î ¿¬°á

		pSelection->set_prenode(NULL);
		pSelection->set_nextnode(NULL); // pObjectÀÇ ¿¬°áÀ» ¸ðµÎ ²÷À½
		aSize--;
	}
	delete pSelection; // SELECTION µ¿ÀûÇÒ´ç ÇØÁ¦
}
void helplist::Clear()
{
	help *temp;
	int i = aSize;
	for (; apTail != NULL;)
	{
		temp = apTail;
		RemoveHelp(temp);
		i = aSize;
	}
}