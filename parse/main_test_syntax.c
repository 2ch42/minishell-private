#include <stdio.h>
#include <readline/readline.h>
#include "token.h"

int main()	//test main for syntax
{
	t_tk_list	*tk_list;
	t_tk		*tk;

	char *str = readline("prompt: ");
	if (!str)
	{
		printf("readline failed\n");
		return (0);
	}
	tk_list = check_syntax(str);
	if (!tk_list)
		return (0);
	if (tk_list)
	{
		tk = tk_list->head;
		if (!tk)
			return (0);
		while (tk != NULL)
		{
			if (tk->str == NULL)
				printf("tk->str == NULL\n");
			printf("%s\n", tk->str);
			printf("redirect_l : %d\n", tk->redirect_l);
			printf("redirect_r : %d\n", tk->redirect_r);
			printf("single_q : %d\n", tk->single_q);
			printf("double_q : %d\n", tk->double_q);
			printf("tktype: %d\n", tk->tktype);
			tk = tk->next;
		}
	}
	tk_clear(tk_list);
	return (0);
}
