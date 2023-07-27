#include <stdio.h>
#include "token.h"

int main()	//test main for token
{
	t_tk_list	*tk_list;
	t_tk		*tk;

	tk_list = tokenize("echo >>>        \"aa\'aaaa\""); //modify here
	tk = tk_list->head;
	while (tk != NULL)
	{
		printf("%s\n", tk->str);
		tk = tk->next;
	}
	return (0);
}
