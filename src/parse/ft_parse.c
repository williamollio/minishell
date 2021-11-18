/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parse.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wollio <wollio@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/18 16:42:01 by wollio            #+#    #+#             */
/*   Updated: 2021/11/18 18:51:49 by wollio           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	ft_parsing(char *line, t_parse **parse, t_env **env_head)
{
	*parse = NULL;
	if (ft_lexer(line, parse) < 0)
	{
		ft_putendl_fd("unclosed quotes or unspecified special characters", 2);
		return (EXIT_FAILURE);
	}
	ft_convert_dollar(parse, *env_head);
	ft_seperator(parse);
	ft_splitter(parse);
	ft_quotes(parse);
	return (EXIT_SUCCESS);
}
