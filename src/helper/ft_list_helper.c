#include "../../includes/minishell.h"

void	ft_addback_sorted(t_env_list **head, char *str)
{
	t_env_list	*newNode;
	t_env_list	*last;

	last = *head;
	newNode = malloc(sizeof(t_env_list));
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

void	ft_addfront(t_env_list **head, char *str)
{
	t_env_list	*newNode;
	t_env_list	*temp;

	temp = *head;
	newNode = malloc(sizeof(t_env_list));
	newNode->full = ft_strdup(str);
	newNode->next = NULL;
	*head = newNode;
	newNode->next = temp;
	return ;
}

int	ft_compare(char	*s1, char *s2)
{
	int	ret;
	int	x;

	x = 0;
	ret = 0;
	while (ret == 0)
	{
		if (s1[x] == '\0')
			return (-1);
		if (s2[x] == '\0')
			return (1);
		ret = s1[x] - s2[x];
		x++;
	}
	return (ret);
}

void	ft_addorder(t_env_list **head, char *str)
{
	t_env_list	*newNode;
	t_env_list	*temp1;
	t_env_list	*temp2;

	temp1 = *head;
	temp2 = *head;
	newNode = malloc(sizeof(t_env_list));
	newNode->full = ft_strdup(str);
	newNode->next = NULL;
	if (*head == NULL)
	{
		*head = newNode;
		return ;
	}
	while (temp1 != NULL)
	{
		if (ft_compare(temp1->full, str) >= 1)
		{
			if (temp1 == *head)
				ft_addfront(head, str);
			else
			{
				temp2->next = newNode;
				newNode->next = temp1;
			}
			return ;
		}
		temp2 = temp1;
		temp1 = temp1->next;
	}
	ft_addback_sorted(head, str);
	return ;
}

void	ft_free_list(t_env_list **head_a)
{
	t_env_list	*tmp;

	while ((* head_a) != NULL)
	{
		tmp = (* head_a);
		(* head_a) = (* head_a)->next;
		free(tmp->full);
		free(tmp);
	}
}