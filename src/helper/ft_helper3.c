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

int	ft_variable_pid(int pid)
{
	static int	pid_2 = 0;

	if (pid == -2)
		return (-1);
	if (pid != -1)
		pid_2 = pid;
	return (pid_2);
}

void	sigfunc_child(int signal)
{
	if (signal == SIGINT || signal == SIGQUIT)
	{
		kill(ft_variable_pid(-1), signal);
		write(1, "\n", 1);
		rl_replace_line("", 0);
		rl_redisplay();
		return ;
	}
}
