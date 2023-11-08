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
		else
			i++;
	}
}
