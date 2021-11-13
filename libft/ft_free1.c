/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_free1.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akurz <akurz@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/06 12:43:25 by wollio            #+#    #+#             */
/*   Updated: 2021/11/13 20:34:35 by akurz            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_free1(char *str) // change to double pointer to keep track of the pointing to NULL
{
	if (!str)
		return ;
	free(str);
	str = NULL;
}
