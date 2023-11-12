#include "minishell.h"

int	ft_isvname(char c)
{
	if (c && ((c >= '0' && c <= '9') || (c >= 'a' && c <= 'z') ||
			(c >= 'A' && c <= 'Z') || (c == '_')))
		return (1);
	else
		return (0);
}

char	*ft_adddol(char *l, int i, char *env)
{
	int	y;
	int	k;
	char *ret;

	y = 0;
	while (env[y] != '=')
		y++;
	ret = ft_calloc((ft_strlen(env) - y) + (ft_strlen(l) - ft_dolen(l, i) - 1), sizeof(char));
	y++;
	k = 0;
	while (k < (i - 1))
	{
		ret[k] = l[k];
		k++;
	}
	i = i + ft_dolen(l, i);
	while (env[y])
		ret[k++] = env[y++];
	while (l[i])
		ret[k++] = l[i++];
	return (ret);
}

char	*ft_rmdol(char *l, int i)
{
	char *new;
	int	y;
	int	z;

	y = 0;
	z = 0;
	new = ft_calloc(((ft_strlen(l) - (ft_dolen(l, i + 1) + 1)) + 1), sizeof(char));
	while (l[y] && new)
	{
		if (y == i)
		{
			y++;
			while (ft_isvname(l[y]))
				y++;
		}
		else
		{
			new[z] = l[y];
			y++;
			z++;
		}
	}
	free(l);
	l = NULL;
	return (new);
}

char	*ft_find(char *l, int i, char **env)
{
	int	y;
	int	z;
	int j;

	i++;
	y = i;
	z = 0;
	j = 0;
	while (env[z] && env[z][j] && ft_isvname(l[y]))
	{
		if (env[z][j] != l[y])
		{
			z++;
			y = i;
		}
		else
		{
			j++;
			y++;
		}
	}
	if (env[z] && env[z][j])
		return (l = ft_adddol(l, i, env[z]));
	else
		return (l = ft_rmdol(l, i - 1));
}

static size_t	get_digits(int n)
{
	size_t	i;

	i = 1;
	while (n /= 10)
		i++;
	return (i);
}

char	*ft_itoa(int n)
{
	char		*str_num;
	size_t		digits;
	long int	num;

	num = n;
	digits = get_digits(n);
	if (n < 0)
	{
		num *= -1;
		digits++;
	}
	if (!(str_num = (char *)malloc(sizeof(char) * (digits + 1))))
		return (NULL);
	*(str_num + digits) = 0;
	while (digits--)
	{
		*(str_num + digits) = num % 10 + '0';
		num = num / 10;
	}
	if (n < 0)
		*(str_num + 0) = '-';
	return (str_num);
}

void	ft_exitdol(t_shell *s, int i)
{
	char	*exit;
	char	*ret;
	int	y;
	int	k;

	exit = ft_itoa(s->exit);
	ret = ft_calloc(sizeof(char), (ft_strlen(s->l) + ft_strlen(exit) - 1));
	y = 0;
	while (s->l[y] && y != i)
	{
		ret[y] = s->l[y];
		y++;
	}
	k = 0;
	while (exit[k])
		ret[y++] = exit[k++];
	k = i + 2;
	while (s->l[k])
		ret[y++] = s->l[k++];
	free(s->l);
	s->l = ret;
}

void	ft_dollar(t_shell *s)
{
	int	i;

	i = 0;
	while (s->l && s->l[i])
	{
		if (s->l[i] == '\'')
		{
			i++;
			while (s->l[i] && s->l[i] != '\'')
				i++;
		}
		if (s->l[i] == '$' && ft_isvname(s->l[i + 1]))
		{
			s->l = ft_find(s->l, i, s->env);
			i = 0;
		}
		else if (s->l[i] == '$' && s->l[i + 1] == '?')
			ft_exitdol(s, i);
		else
			i++;
	}
}
