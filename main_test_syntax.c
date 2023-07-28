#include <stdio.h>
#include <readline/readline.h>
#include "token.h"

int main()	//test main for syntax
{
	t_tk_list	*tk_list;
	t_tk		*tk;

	char *str = readline("prompt: ");
	tk_list = check_syntax(str);
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
