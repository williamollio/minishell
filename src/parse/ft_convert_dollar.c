#include "../../includes/minishell.h"

void	ft_init_rep(t_replace *rep)
{
	rep->i = 0;
	rep->start = 0;
	rep->quote_flag = 1;
	rep->var = "";
	rep->content = "";
	rep->tofree = "";
}

char	*ft_replace_str(char *str, t_replace rep)
{
	char	*temp;
	char	*temp_2;
	char	*temp_3;
	char	*ret;

	temp = ft_substr(str, 0, rep.start - 1);
	temp_2 = ft_substr(str, rep.i, ft_strlen(str) - rep.i);
	temp_3 = ft_strjoin(temp, rep.content);
	ret = ft_strjoin(temp_3, temp_2);
	free(temp);
	free(temp_2);
	free(temp_3);
	free(rep.content);
	return (ret);
}

void	ft_replacer(char *str, t_replace *rep, t_parse *temp, t_env_list *env_head)
{
	rep->var = ft_substr(str, rep->start, rep->i - rep->start);
	rep->content = ft_extract_content(env_head, rep->var);
	rep->tofree = temp->str;
	temp->str = ft_replace_str(str, *rep);
	free(rep->var);
	free(rep->tofree);
	rep->i = 0;
	rep->quote_flag = 1;
}

void	ft_replace(char *str, t_parse *temp, t_env_list *env_head)
{
	t_replace	rep;

	ft_init_rep(&rep);
	while (str[rep.i])
	{
		if (ft_strncmp(&str[rep.i], "'", 1) == 0)
			rep.quote_flag *= (-1);
		if (str[rep.i] == '$' && rep.quote_flag > 0)
		{
			rep.i++;
			rep.start = rep.i;
			while (str[rep.i] && str[rep.i] != ' ' && !ft_operator_tool2(str, &rep.i))
				rep.i++;
			ft_replacer(str, &rep, temp, env_head);
			str = temp->str;
		}
		rep.i++;
	}
} 

void	ft_convert_dollar(t_parse **parse, t_env_list *env_head)
{
	t_parse	*temp;

	temp = *parse;
	while (temp != NULL)
	{
		if (ft_strchr(temp->str, '$'))
			ft_replace(temp->str, temp, env_head);
		temp = temp->next;
	}
}
