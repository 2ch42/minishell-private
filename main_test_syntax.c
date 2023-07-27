#include <stdio.h>
#include "token.h"

int main()	//test main for syntax
{
	t_tk_list	*tk_list;
	t_tk		*tk;

	//tk_list = check_syntax("echo >>>>>>>>>        \"aa\'aaaa\"");
	tk_list = check_syntax("echo \"asdfasdf\'\"\'");
	if (tk_list)
	{
		tk = tk_list->head;
		while (tk != NULL)
		{
			printf("%s\n", tk->str);
			tk = tk->next;
		}
	}
	return (0);
}
