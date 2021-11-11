#include "../../includes/minishell.h"

void	ft_print_list(t_env_list *head)
{
	while (head != NULL)
	{
		printf("%s\n", head->full);
		head = head->next;
	}
}

void	ft_print_list_parse(t_parse **head)
{
	t_parse	*tmp;
	int i;

	tmp = *head;
	while (tmp != NULL)
	{
		printf("------------------\n");
		printf("str : %s\n", tmp->str);
		printf("op : %d\n", tmp->op);
		i = 0;
		while (tmp->cmd[i])
		{
			printf("cmd i%d: %s\n",i, tmp->cmd[i]);
			i++;
		}
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
	(* head)->str = "";
	(* head)->op = 0;
	// init cmd
}

void	ft_addback_parse(t_parse **head_ref, char *str, int nbr)
{
	t_parse	*newNode;
	t_parse	*last;

	last = *head_ref;
	newNode = malloc(sizeof(t_parse));
	ft_init_parse(&newNode);
	newNode->str = str;
	newNode->op = nbr;
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