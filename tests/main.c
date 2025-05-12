#include "../minishell.h"

void	test_manager(t_manager **list)
{
	char *str;

	list = NULL;
	memlist_add(list, strdup("The allocator works \n"));
	printf("%s\n", str);
}

int	main()
{
	t_manager *list;

	test_manager();

	memlist_free_all(&list);
}
