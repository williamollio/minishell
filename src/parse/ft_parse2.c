#include "../../includes/minishell.h"

int ft_operator_tool(char *str, int *x)
{
	if (str[*x] == '|')
	{
		*x += 1;
		return (1);
	}
	else if (ft_strnstr(&str[*x], "<<", 2) != NULL)
	{
		*x += 2;
		return (4);
	}
	else if (ft_strnstr(&str[*x], ">>", 2) != NULL)
	{
		*x += 2;
		return (5);
	}
	else if (str[*x] == '>')
	{
		*x += 1;
		return (2);
	}
	else if (str[*x] == '<')
	{
		*x += 1;
		return (3);
	}
	else
		return (0);
}
int ft_operator_tool2(char *str, int *x)
{
	if (str[*x] == '|')
		return (1);
	else if (ft_strnstr(&str[*x], "<<", 2) != NULL)
	{

		return (4);
	}
	else if (ft_strnstr(&str[*x], ">>", 2) != NULL)
	{
		return (5);
	}
	else if (str[*x] == '>')
		return (2);
	else if (str[*x] == '<')
		return (3);
	else
		return (0);
}

void ft_skip_space(char *line, int *x)
{
	while (line[*x] && line[*x] == ' ')
		*x+=1;
}

int	countrows(char **paths)
{
	int	i;

	i = 0;
	while (paths[i] != NULL)
		i++;
	return (i);
}

void	ft_add_next(t_parse **head_ref, t_parse *old, char **str, int nbr)
{
	t_parse	*newNode;

	newNode = malloc(sizeof(t_parse));
	ft_init_parse(&newNode);
	newNode->op = nbr;
	newNode->cmd = str;
	newNode->next = old->next;
	if (old->next != NULL)
		old->next->prev = newNode;
	old->next = newNode;
	if (*head_ref == NULL)
	{
		*head_ref = newNode;
		newNode->prev = NULL;
		return ;
	}
	newNode->prev = old;

	return ;
}