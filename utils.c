#include "minishell.h"

static void	ft_bzero(void *s, size_t n)
{
	size_t	i;

	if (!s)
		return ;
	i = 0;
	while (i < n)
	{
		*(char*)(s + i) = 0;
		i++;
	}
}

void	*ft_calloc(size_t count, size_t size)
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
	char	*ret;
	int		i;
	int		y;
	int		z;

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
	if (!env[y] || !s)
		return (NULL);
	i++;
	ret = ft_calloc(ft_strlen(env[y]) - i, sizeof(char));
	z = 0;
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
	while (str1[i])
	{
		res[i] = str1[i];
		i++;
	}
	res[i] = '/';
	i++;
	while (str2[k])
	{
		res[i] = str2[k];
		i++;
		k++;
	}
	return (res);
}

char	*ft_strcpy(char *s)
{
	char	*cpy;
	int	i;

	if (!s)
		return (NULL);
	cpy = ft_calloc(ft_strlen(s) + 1, sizeof(char));
	i = 0;
	while (s[i])
	{
		cpy[i] = s[i];
		i++;
	}
	return (cpy);
}

int	ft_berror(t_shell *s)
{
	free(s->env);
	printf("Bash error");
	return (1);
}

int	ft_perror(t_shell *s)
{
	free(s->env);
	perror("peror");
	return (1);
}

void	ft_free(char **s)
{
	int	i;

	i = 0;
	while (s[i])
		free(s[i++]);
	free(s);
}
