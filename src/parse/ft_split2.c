/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wollio <wollio@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/18 16:42:01 by wollio            #+#    #+#             */
/*   Updated: 2021/11/18 18:57:34 by wollio           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static size_t	ft_count2(char const *s, char c, int *flag)
{
	size_t	i;
	size_t	row;

	i = 0;
	row = 1;
	if (!s)
		return (0);
	while (s[i])
	{
		if (s[i] == '"' || ft_strncmp(&s[i], "'", 1) == 0)
			(*flag) *= (-1);
		if (s[i] == c && s[i - 1] != c && flag > 0)
			row++;
		i++;
	}
	if (s[i - 1] == c)
		row--;
	return (row);
}

char	**ft_snake2(char const *s, char c, size_t count, t_split *sp)
{
	sp->i = 0;
	sp->h = 0;
	sp->t = 0;
	while (sp->i < count)
	{
		while (s[sp->h] && s[sp->h] == c)
			sp->h++;
		sp->t = sp->h;
		while ((s[sp->t] && s[sp->t] != c) || sp->flag == -1)
		{
			if (s[sp->t] == '"' || ft_strncmp(&s[sp->t], "'", 1) == 0)
				(sp->flag) *= (-1);
			sp->t++;
		}
		if (s[sp->h] == '\0')
			break ;
		sp->mat[sp->i] = (char *)malloc(sizeof(char) * (sp->t - sp->h + 1));
		ft_memcpy(sp->mat[sp->i], &((char *)s)[sp->h], (sp->t - sp->h));
		sp->mat[sp->i][sp->t - sp->h] = '\0';
		sp->i++;
		sp->h = sp->t;
	}
	sp->mat[sp->i] = NULL;
	return (sp->mat);
}

char	**ft_split2(char const *s, char c, int *count)
{
	t_split	sp;

	sp.flag = 1;
	if (!s)
		return (NULL);
	*count = ft_count2(s, c, &sp.flag);
	sp.mat = (char **)malloc((sizeof(char *) * (*count)) + 1);
	if (!sp.mat)
		return (NULL);
	return (ft_snake2(s, c, *count, &sp));
}
