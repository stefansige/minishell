#include "minishell.h"

static void ft_bzero(void *s, size_t n)
{
	size_t i;
	unsigned char *l;

	l = (unsigned char *)s;
	i = 0;
	while (i < n)
	{
		*(l + i) = 0;
		i++;
	}
}


void	*ft_calloc(size_t size, size_t count)
{
	void	*ptr;

	if (count == 0)
		return (NULL);
	ptr = (void*)malloc(count * size);
	if (!ptr)
		return (NULL);
	ft_bzero(ptr, count);
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

char	*ft_join(char *str1, char *str2)
{
	char	*res;
	int		i;
	int		k;

	i = 0;
	k = 0;
	res = ft_calloc(sizeof(char), (ft_strlen(str1) + ft_strlen(str2) + 2));
	while (str1 && str1[i])
	{
		res[i] = str1[i];
		i++;
	}
	res[i] = '/';
	i++;
	while (str2 && str2[k])
	{
		res[i] = str2[k];
		i++;
		k++;
	}
	return (res);
}

char	*ft_strjoin(char *str1, char *str2)
{
	char	*join;
	int		i;
	int		k;

	i = 0;
	k = 0;
	join = NULL;
	join = ft_calloc(sizeof(char), (ft_strlen(str1) + ft_strlen(str2) + 2));
	while (str1 && str1[i])
	{
		join[i] = str1[i];
		i++;
	}
	while (str2 && str2[k])
	{
		join[i] = str2[k];
		i++;
		k++;
	}
	join[i] = '\n';
	return (join);
}

char	*ft_strcpy(char *s)
{
	char	*cpy;
	int	i;

	if (!s)
		return (NULL);
	cpy = ft_calloc(sizeof(char), ft_strlen(s) + 1);
	i = 0;
	while (s[i])
	{
		cpy[i] = s[i];
		i++;
	}
	return (cpy);
}

void	ft_free(char **s)
{
	int	i;

	if (s == NULL)
		return;
	i = 0;
	while (s[i])
	{
		free(s[i]);
		i++;
	}
	free(s[i]);
	free(s);
}

static int	ft_isspace(const char c)
{
	if (c == 32 || (c >= '\t' && c <= '\r'))
		return (1);
	return (0);
}

int	ft_atoi(const char *nptr)
{
	int	n;
	int	sign;

	n = 0;
	sign = 1;
	while (ft_isspace(*nptr) == 1)
		nptr++;
	if (*nptr == '-')
	{
		sign = -1;
		nptr++;
	}
	else if (*nptr == '+')
		nptr++;
	while (*nptr)
	{
		if (!(*nptr >= '0' && *nptr <= '9'))
			return (-1010101);
		n *= 10;
		n += (*nptr - 48);
		nptr++;
	}
	return (n * sign);
}