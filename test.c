#include "minishell.h"

//cc test.c srcs/minishell_*.c libft/*.c -lreadline libft/libft.a
int main(int ac, char **av, char **env){
	t_var bruh;

	bruh.varlist = create_var_list(&bruh, env);
	for (t_varlist *head = bruh.varlist; head != NULL; head = head->next)
	{
		printf("variable: %s\n", head->var_name);
		printf("content: %s\n", head->content);
	}
	memlist_free_all(&bruh.memlist);
}
