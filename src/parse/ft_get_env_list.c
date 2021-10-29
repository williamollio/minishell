#include "../../includes/minishell.h"

char	*ft_get_var(char *full)
{
	int		x;
	char	*var;

	x = 0;
	while (full[x] != '=')
	x++;
	var = ft_substr(full, 0, x);
	return (var);
}

char	*ft_get_content(char *full)
{
	int		x;
	char	*con;

	x = 0;
	while (full[x] != '=')
	x++;
	con = ft_substr(full, x + 1, ft_strlen(full) - x);
	return (con);
}

void	ft_addback(t_env_list **head_ref, char *str)
{
	t_env_list	*newNode;
	t_env_list	*last;

	last = *head_ref;
	newNode = (t_env_list *) malloc(sizeof(t_env_list));
	newNode->full = str;
	newNode->var = ft_get_var(str);
	newNode->content = ft_get_content(str);
	newNode->next = NULL;
	if (*head_ref == NULL)
	{
		*head_ref = newNode;
		return ;
	}
	while (last->next != NULL)
		last = last->next;
	last->next = newNode;
	return ;
}

void	ft_get_env_list(char **envp, t_env_list **env_head)
{
	int	x;

	x = 0;
	while (envp[x])
	{
		ft_addback(env_head, envp[x]);
		x++;
	}
	return ;
}