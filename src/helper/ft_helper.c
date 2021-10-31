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
	t_parse	*tmp;

	tmp = head;
	while (tmp != NULL)
	{
		printf("---------\n");
		printf("cmd : %s\n", tmp->cmd);
		printf("flag : %d\n", tmp->flag);
		printf("arg : %s\n", tmp->arg);
		printf("str : %s\n", tmp->str);
		printf("op : %d\n", tmp->op);
		tmp = tmp->next;
	}
}

void	ft_free_list_parse(t_parse **head_a)
{
	t_parse	*tmp;

	while ((* head_a) != NULL)
	{
		tmp = (* head_a);
		(* head_a) = (* head_a)->next;
		free(tmp);
	}
}

void	ft_init_parse(t_parse **head)
{
	(* head)->cmd = NULL;
	(* head)->arg = NULL;
	(* head)->str = NULL;
	(* head)->op = 0;
	(* head)->flag = 0;
}

void	ft_addback_parse(t_parse **head_ref, char *str, int nbr)
{
	t_parse	*newNode;
	t_parse	*last;

	last = *head_ref;
	newNode = malloc(sizeof(t_parse));
	ft_init_parse(&newNode);
	if (nbr == 8)
		newNode->str = str;
	else
		newNode->cmd = str;
	newNode->flag = nbr;
	newNode->next = NULL;
	if (*head_ref == NULL)
	{
		*head_ref = newNode;
		newNode->prev = NULL;
		return ;
	}
	while (last->next != NULL)
		last = last->next;
	newNode->prev = last;
	last->next = newNode;
	return ;
}