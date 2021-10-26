#include "../../includes/minishell.h"


t_parse	*ft_get_last(t_parse **head)
{
	t_parse *tmp;

	tmp = (* head);
	while (tmp->next != NULL)
		tmp = tmp->next;
	return (tmp);
}

void ft_print_node(t_parse *tmp)
{
	printf("cmd : %s\n", tmp->cmd);
	printf("flag : %d\n", tmp->flag);
	printf("file : %s\n", tmp->file);
	printf("arg : %s\n", tmp->arg);
	printf("str : %s\n", tmp->str);
	printf("op : %d\n", tmp->op);
}