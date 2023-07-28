#include <stdio.h>
#include <readline/readline.h>
#include "token.h"

int main()	//test main for token
{
	t_tk_list	*tk_list;
	t_tk		*tk;

	char *str = readline("prompt: ");
	tk_list = tokenize(str);
	tk = tk_list->head;
	while (tk != NULL)
	{
		printf("%s\n", tk->str);
		printf("redirect_l : %d\n", tk->redirect_l);
		printf("redirect_r : %d\n", tk->redirect_r);
		printf("single_q : %d\n", tk->single_q);
		printf("double_q : %d\n", tk->double_q);
		printf("tktype: %d\n", tk->tktype);
		tk = tk->next;
	}
	return (0);
}
