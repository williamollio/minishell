#include "../../includes/minishell.h"

void	ft_free_list_parse(t_parse **head_a)
{
	t_parse	*tmp;

	while ((*head_a) != NULL)
	{
		tmp = (*head_a);
		(*head_a) = (*head_a)->next;
		ft_free2(tmp->cmd);
		free(tmp);
	}
}

void	ft_addback_sorted(t_env **head, char *str)
{
	t_env	*newNode;
	t_env	*last;

	last = *head;
	newNode = malloc(sizeof(t_env));
	newNode->full = ft_strdup(str);
	newNode->next = NULL;
	if (*head == NULL)
	{
		*head = newNode;
		return ;
	}
	while (last->next != NULL)
		last = last->next;
	last->next = newNode;
	return ;
}
