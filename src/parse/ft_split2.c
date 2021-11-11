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

char	**ft_snake2(char const *s, char c, size_t count, char **mat, int flag)
{
	size_t	i;
	size_t	tail;
	size_t	head;

	i = 0;
	head = 0;
	tail = 0;
	while (i < count)
	{
		while (s[head] && s[head] == c)
			head++;
		tail = head;
		while ((s[tail] && s[tail] != c) || flag == -1)
		{
			if (s[tail] == '"' || ft_strncmp(&s[tail], "'", 1) == 0)
				(flag) *= (-1);
			tail++;
		}
		if (s[head] == '\0')
			break ;
		mat[i] = (char *)malloc(sizeof(char) * (tail - head + 1));
		ft_memcpy(mat[i], &((char *)s)[head], (tail - head));
		mat[i][tail - head] = '\0';
		i++;
		head = tail;
	}
	mat[i] = NULL;
	return (mat);
}

char	**ft_split2(char const *s, char c, int *count)
{
	char	**mat;
	int		flag;

	flag = 1;
	if (!s)
		return (NULL);
	*count = ft_count2(s, c, &flag);
	mat = (char **)malloc((sizeof(char *) * (*count)) + 1);
	if (!mat)
		return (NULL);
	return (ft_snake2(s, c, *count, mat, flag));
}