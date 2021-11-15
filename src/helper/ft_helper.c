#include "../../includes/minishell.h"

void	ft_print_list(t_env_list *head)
{
	while (head != NULL)
	{
		printf("%s\n", head->full);
		head = head->next;
	}
}

void	ft_print_list_parse_2(t_parse **head)
{
	t_parse	*tmp;

	tmp = *head;
	while (tmp != NULL)
	{
		printf("------------------\n");
		printf("str : %s\n", tmp->str);
		printf("op : %d\n", tmp->op);
		printf("pipe_flag : %d\n", tmp->pipe_flag);
		if (tmp->cmd)
		{

			if (tmp->cmd[0])
				printf("cmd : %s\n", tmp->cmd[0]);
		}
		tmp = tmp->next;
	}
}

void	ft_print_list_parse(t_parse **head)
{
	t_parse	*tmp;

	tmp = *head;
	while (tmp != NULL)
	{
		printf("------------------\n");
		// printf("str : %s\n", tmp->str);
		printf("op : %d\n", tmp->op);
		printf("pipe_flag : %d\n", tmp->pipe_flag);
		int i = 0;
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
		ft_free2(tmp->cmd);
		free(tmp);
	}
}

void	ft_init_parse(t_parse **head)
{
	(* head)->str = "";
	(* head)->op = 0;
	(* head)->pipe_flag = 0;
	(* head)->cmd = NULL;
}

void	ft_addback_parse(t_parse **head_ref, char *str, int nbr, int *pipe_flag)
{
	t_parse	*newNode;
	t_parse	*last;

	last = *head_ref;
	newNode = malloc(sizeof(t_parse));
	ft_init_parse(&newNode);
	newNode->str = str;
	newNode->op = nbr;
	if (pipe_flag)
	{
		newNode->pipe_flag = *pipe_flag;
		*pipe_flag = 0;
	}
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

int	ft_is_builtin_new(char *line)
{
	if (ft_strncmp(line, "echo", ft_strlen(line)) == 0 && (ft_strlen(line) == 4))
		return (EXIT_SUCCESS);
	else if (ft_strncmp(line, "pwd", ft_strlen(line)) == 0 && (ft_strlen(line) == 3))
		return (EXIT_SUCCESS);
	else if (ft_strncmp(line, "cd", ft_strlen(line)) == 0 && (ft_strlen(line) == 2))
		return (EXIT_SUCCESS);
	else if (ft_strncmp(line, "export", ft_strlen(line)) == 0 && (ft_strlen(line) == 6))
		return (EXIT_SUCCESS);
	else if (ft_strncmp(line, "unset", ft_strlen(line)) == 0 && (ft_strlen(line) == 5))
		return (EXIT_SUCCESS);
	else if (ft_strncmp(line, "env", ft_strlen(line)) == 0 && (ft_strlen(line) == 3))
		return (EXIT_SUCCESS);
	else if (ft_strncmp(line, "exit", ft_strlen(line)) == 0 && (ft_strlen(line) == 4))
		return (EXIT_SUCCESS);
	else
		return (EXIT_FAILURE);
}
