/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: snovakov <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/18 16:10:43 by snovakov          #+#    #+#             */
/*   Updated: 2023/11/18 16:10:45 by snovakov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	ft_bzero(void *s, size_t n)
{
	size_t	i;
	char	*str;

	i = 0;
	str = (char *)s;
	if (n == 0)
		return ;
	while (i < n)
	{
		str[i] = '\0';
		i++;
	}
}

void	*ft_calloc(size_t size, size_t count)
{
	void	*ptr;

	ptr = malloc(count * size);
	if (ptr == NULL)
		return (ptr);
	ft_bzero(ptr, size * count);
	return (ptr);
}

unsigned int	ft_strlen(char *s)
{
	unsigned int	i;

	i = 0;
	while (s && s[i])
		i++;
	return (i);
}

unsigned int	ft_dolen(char *s, int start)
{
	unsigned int	i;

	i = 0;
	while (s && s[start] && ft_isvname(s[start]))
	{
		start++;
		i++;
	}
	return (i);
}

char	*ft_getenv(char **env, char *s)
{
	char				*ret;
	unsigned int		i;
	int					y;
	int					z;

	i = 0;
	y = 0;
	while (s && s[i] && env[y] && env[y][i])
	{
		if (env[y][i] != s[i])
		{
			i = 0;
			y++;
		}
		else
			i++;
	}
	if (!env[y] || !s || i != ft_strlen(s))
		return (NULL);
	ret = ft_calloc(sizeof(char), ft_strlen(env[y]) - i);
	z = 0;
	i++;
	while (env[y][i])
		ret[z++] = env[y][i++];
	return (ret);
}
