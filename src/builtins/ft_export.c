#include "../../includes/minishell.h"

void	ft_replace_var(t_env **temp, char **str_var, char *str)
{
	free((*temp)->content);
	(*temp)->content = ft_get_content(str);
	free((*temp)->full);
	(*temp)->full = ft_strdup(str);
	free((*temp)->var);
	(*temp)->var = ft_get_var(str);
	free(*str_var);
}

void	ft_add_var(t_env **t, t_env **prev, t_env **env, char *s)
{
	t_env	*temp_2;
	t_env	*newNode;

	(*t) = (*prev);
	temp_2 = (*t)->next;
	newNode = malloc(sizeof(t_env));
	newNode->full = ft_strdup(s);
	newNode->var = ft_get_var(s);
	newNode->content = ft_get_content(s);
	(*t)->next = newNode;
	newNode->next = temp_2;
	if (*env == NULL)
	{
		*env = newNode;
		return ;
	}
}

void	ft_add_export(t_env **env_head, char *str)
{
	t_env	*temp;
	t_env	*prev;
	char		*str_var;

	temp = *env_head;
	prev = *env_head;
	if (ft_export_edgecase(str) == 1)
		return ;
	str_var = ft_get_var(str);
	while (temp != NULL)
	{
		if (ft_strncmp(temp->var, str_var, ft_strlen(temp->var)) == 0
			&& ft_strlen(temp->var) == ft_strlen(str_var))
		{
			ft_replace_var(&temp, &str_var, str);
			return ;
		}
		if (ft_strncmp(temp->var, "_", ft_strlen(temp->var)) == 0)
			break ;
		prev = temp;
		temp = temp->next;
	}
	free(str_var);
	ft_add_var(&temp, &prev, env_head, str);
}

void	ft_sort_env(t_env *env_head)
{
	t_env	*sorted;

	sorted = NULL;
	while (env_head != NULL)
	{
		ft_addorder(&sorted, env_head->full);
		env_head = env_head->next;
	}
	ft_print_list(sorted);
	ft_free_list(&sorted);
	return ;
}

void	ft_export_node(t_env **env_head, char **cmd)
{
	int		i;

	exit_status = 0;
	if (cmd[1] == NULL)
	{
		ft_sort_env(*env_head);
		return ;
	}
	i = 1;
	while (cmd[i])
	{
		ft_add_export(env_head, cmd[i]);
		i++;
	}
	return ;
}
