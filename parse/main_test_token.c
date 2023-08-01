#include <stdio.h>
#include <readline/readline.h>
#include "token.h"

int main()	//test main for token
{
	t_tk_list	*tk_list;
	t_tk		*tk;

	char *str = readline("prompt: ");
	if (!str)
		return (0);
	tk_list = tokenize(str);
	if (!tk_list)
		return (0);
	tk = tk_list->head;
	if (!tk)
		return (0);
	while (tk != NULL)
	{
		if (tk->str == NULL)
			printf("tk->str : NULL\n");
		printf("%s\n", tk->str);
		printf("redirect_l : %d\n", tk->redirect_l);
		printf("redirect_r : %d\n", tk->redirect_r);
		printf("single_q : %d\n", tk->single_q);
		printf("double_q : %d\n", tk->double_q);
		tk = tk->next;
	}
	tk_clear(tk_list);
	return (0);
}
