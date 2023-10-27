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

char	*ft_strjoin(char *a, char *b)
{
	char		*strjoin;
	size_t		i;
	size_t		y;

	if (!a || !b)
		return (NULL);
	strjoin = ft_calloc(ft_strlen(a) + ft_strlen(b) + 1, sizeof(char));
	if (!strjoin)
		return (NULL);
	i = -1;
	y = 0;
	if (a)
		while (a && a[++i])
			strjoin[i] = a[i];
	while (b && b[y])
		strjoin[i++] = b[y++];
	free(a);
	return (strjoin);
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
	}
	return (cpy);
}

void	ft_berror(t_shell *s)
{
	free(s->env);
	printf("Bash error");
}

void	ft_perror(t_shell *s)
{
	free(s->env);
	perror("peror");
}

void	ft_free(char **s)
{
	int	i;

	i = 0;
	while (s[i])
		free(s[i++]);
	free(s);
}