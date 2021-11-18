#include "../../includes/minishell.h"

void	ft_addfront(t_env **head, char *str)
{
	t_env	*newNode;
	t_env	*temp;

	temp = *head;
	newNode = malloc(sizeof(t_env));
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

void	ft_init_order(t_order *order, char *str, t_env **head)
{
	order->temp1 = *head;
	order->temp2 = *head;
	order->newNode = malloc(sizeof(t_env));
	order->newNode->full = ft_strdup(str);
	order->newNode->next = NULL;
}

int	ft_ft_compare(t_order *order, char *str, t_env **head)
{
	if (ft_compare(order->temp1->full, str) >= 1)
	{
		if (order->temp1 == *head)
		{
			free(order->newNode->full);
			free(order->newNode);
			ft_addfront(head, str);
		}
		else
		{
			order->temp2->next = order->newNode;
			order->newNode->next = order->temp1;
		}
		return (1);
	}
	return (0);
}

void	ft_addorder(t_env **head, char *str)
{
	t_order	order;

	ft_init_order(&order, str, head);
	if (*head == NULL)
	{
		*head = order.newNode;
		return ;
	}
	while (order.temp1 != NULL)
	{
		if (ft_ft_compare(&order, str, head))
			return ;
		order.temp2 = order.temp1;
		order.temp1 = order.temp1->next;
	}
	free(order.newNode->full);
	free(order.newNode);
	ft_addback_sorted(head, str);
	return ;
}
