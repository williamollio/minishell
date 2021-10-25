#include "../../includes/minishell.h"

void	ft_print_list(t_env_list *head)
{
	while (head != NULL)
	{
		printf("%s\n", head->full);
		head = head->next;
	}
}

void	ft_print_list_parse(t_parse *head)
{
	t_parse *tmp;

	tmp = head;
	while (tmp != NULL)
	{
		printf("%s\n", tmp->cmd);
		tmp = tmp->next;
	}
}