/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wollio <wollio@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/18 16:42:01 by wollio            #+#    #+#             */
/*   Updated: 2021/11/18 18:49:56 by wollio           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	ft_identifier_error(char *err, char *var)
{
	ft_putstr_fd("bash: export: `", 2);
	ft_putstr_fd(err, 2);
	ft_putendl_fd("': not a valid identifier", 2);
	free(var);
	g_exit_status = 1;
}

int	ft_export_errors(char *str, int i, char *var)
{
	if (str[0] == '=')
	{
		ft_identifier_error(str, var);
		return (1);
	}
	while (var[i])
	{
		if (var[i] == '-')
		{
			ft_identifier_error(str, var);
			return (1);
		}
		i++;
	}
	if (ft_strncmp(var, "_", ft_strlen(var)) == 0)
	{
		free(var);
		return (1);
	}
	if (!ft_isalpha(var[0]) && var[0] != '_')
	{
		ft_identifier_error(str, var);
		return (1);
	}
	return (0);
}

int	ft_export_edgecase(char *str)
{
	char	*var;
	int		i;

	i = 0;
	if (!ft_strchr(str, '='))
		return (1);
	var = ft_get_var(str);
	if (ft_export_errors(str, i, var) == 1)
		return (1);
	free(var);
	return (0);
}
