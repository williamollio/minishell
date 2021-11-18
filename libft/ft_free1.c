/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_free1.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wollio <wollio@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/06 12:43:25 by wollio            #+#    #+#             */
/*   Updated: 2021/11/18 15:29:03 by wollio           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/* change to double pointer to keep track of the pointing to NULL */
void	ft_free1(char *str)
{
	if (!str)
		return ;
	free(str);
	str = NULL;
}
