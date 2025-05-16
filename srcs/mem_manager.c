#include "../minishell.h"

void	*memlist_alloc(t_manager **memlist, size_t size)
{
	t_manager	*node;
	void		*ptr;

	if (!memlist)
		return (NULL);
	ptr = malloc(size);
	if (!ptr)
		return (NULL);
	node = (t_manager *)malloc(sizeof(t_manager));
	if (!node)
	{
		free(ptr);
		memlist_free_all(memlist);
		return (NULL);
	}
	node->ptr = ptr;
	node->next = *memlist;
	*memlist = node;
	return (ptr);
}

void	*memlist_add(t_manager **memlist, void *ptr)
{
	t_manager	*node;

	if (!memlist)
		return (NULL);
	if (!ptr)
		return (NULL);
	node = (t_manager *)malloc(sizeof(t_manager));
	if (!node)
	{
		free(ptr);
		memlist_free_all(memlist);
		return (NULL);
	}
	node->ptr = ptr;
	node->next = *memlist;
	*memlist = node;
	return (ptr);
}

int	memlist_free_ptr(t_manager **memlist, void *ptr) //TODO: Make shorter for norminette
{
	t_manager	*current;
	t_manager	*prev;

	if (!memlist || !ptr || !*memlist)
		return (0);
	if ((*memlist)->ptr == ptr)
	{
		current = *memlist;
		*memlist = (*memlist)->next;
		free(current->ptr);
		free(current);
		return (1);
	}
	prev = *memlist;
	current = (*memlist)->next;
	while (current)
	{
		if (current->ptr == ptr)
		{
			prev->next = current->next;
			free(current->ptr);
			free(current);
			return (1);
		}
		prev = current;
		current = current->next;
	}
	return (1);
}

int	memlist_free_all(t_manager **memlist)
{
	t_manager	*current;
	t_manager	*next;
	int			i;

	i = 0;
	if (!memlist || !*memlist)
		return (0);
	current = *memlist;
	while (current)
	{
		next = current->next;
		free(current->ptr);
		free(current);
		i++;
		current = next;
	}
	*memlist = NULL;
	return (i);
}
