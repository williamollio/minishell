/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_helper.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akurz <akurz@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/25 15:47:31 by akurz             #+#    #+#             */
/*   Updated: 2021/10/25 15:49:08 by akurz            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	ft_print_list(t_env_list *head)
{
	while (head != NULL)
	{
		printf("%s\n", head->full);
		head = head->next;
	}
}