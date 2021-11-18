/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_free2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wollio <williamollio@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/06 12:47:06 by wollio            #+#    #+#             */
/*   Updated: 2021/10/28 15:05:44 by wollio           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_free2(char **str)
{
	int	i;

	i = 0;
	if (!str)
		return ;
	while (str[i] != (void *)0)
	{
		free(str[i]);
		i++;
	}
	free(str);
	str = NULL;
}
