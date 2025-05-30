#include "../minishell.h"

void	*memlist_alloc(t_manager **head, size_t size)
{
	t_manager	*node;
	void		*ptr;

	if (!head)
		return (NULL);
	ptr = malloc(size);
	if (!ptr)
		return (NULL);
	node = (t_manager *)malloc(sizeof(t_manager));
	if (!node)
	{
		free(ptr);
		return (NULL);
	}
	node->ptr = ptr;
	node->next = *head;
	*head = node;
	return (ptr);
}

void	*memlist_add(t_manager **head, void *ptr)
{
	t_manager	*node;

	if (!head)
		return (NULL);
	if (!ptr)
		return (NULL);
	node = (t_manager *)malloc(sizeof(t_manager));
	if (!node)
	{
		free(ptr);
		return (NULL);
	}
	node->ptr = ptr;
	node->next = *head;
	*head = node;
	return (ptr);
}

int	memlist_free_ptr(t_manager **head, void *ptr) //TODO: Make shorter for norminette
{
	t_manager	*current;
	t_manager	*prev;

	if (!head || !ptr || !*head)
		return (0);
	if ((*head)->ptr == ptr)
	{
		current = *head;
		*head = (*head)->next;
		free(current->ptr);
		free(current);
		return (1);
	}
	prev = *head;
	current = (*head)->next;
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

int	memlist_free_all(t_manager **head)
{
	t_manager	*current;
	t_manager	*next;
	int			i;

	i = 0;
	if (!head || !*head)
		return (0);
	current = *head;
	while (current)
	{
		next = current->next;
		free(current->ptr);
		free(current);
		i++;
		current = next;
	}
	*head = NULL;
	return (i);
}
