/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: snovakov <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/18 19:28:20 by snovakov          #+#    #+#             */
/*   Updated: 2023/11/18 19:28:22 by snovakov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_echo(char **arg)
{
	bool	flag;
	int		i;

	flag = true;
	i = 1;
	if (ft_compare(arg[i], "-n"))
	{
		flag = false;
		i++;
	}
	while (arg[i])
	{
		if (arg[i + 1])
			printf("%s ", arg[i]);
		else
			printf("%s", arg[i]);
		i++;
	}
	if (flag)
		printf("\n");
	return (0);
}

int	ft_export_forth(char **env)
{
	int	i;

	i = -1;
	while (env[++i])
		printf("declare -x %s\n", env[i]);
	return (0);
}

int	ft_pwd(char **arg, char **env)
{
	char	*pwd;

	(void)arg;
	(void)env;
	pwd = NULL;
	pwd = getcwd(NULL, 0);
	getcwd(pwd, sizeof(pwd));
	printf("%s\n", pwd);
	if (pwd)
		free(pwd);
	return (0);
}

int	ft_getenv_n(char **env, char *s)
{
	unsigned int	i;
	int	j;

	i = 0;
	j = 0;
	while (env && s && env[i] && env[i][j])
	{
		if (env[i][j] != s[j])
		{
			j = 0;
			i++;
		}
		else
			i++;
	}
	if (!env[j] || !s || i != ft_strlen(s))
		return (0);
	return (j);
}

char	*ft_rereset(char *varn, char *varc)
{
	char	*re;
	int		i;
	int		j;

	i = 0;
	j = 0;
	re = NULL;
	re = (char *)ft_calloc(sizeof(char), (ft_strlen(varn) + ft_strlen(varc) + 2));
	while (varn && varn[i])
	{
		re[i] = varn[i];
		i++;
	}
	re[i++] = '=';
	while (varc && varc[j])
	{
		re[i] = varc[j];
		i++;
		j++;
	}
	re[i] = '\0';
	return (re);
}

void	ft_reset(char **env, char *varn, char *varc)
{
	int		p;

	p = ft_getenv_n(env, varn);
	free(env[p]);
	env[p] = ft_rereset(varn, varc);
}

void	ft_unset_real(t_shell *s, char *arg)
{
	char	**new_env;
	int		i;
	int		p;

	i = 0;
	while (s->env[i])
		i++;
	p = ft_getenv_n(s->env, arg);
	new_env = ft_calloc(sizeof(char *), i);
	i = 0;
	while (i < p)
	{
		new_env[i] = s->env[i];
		i++;
	}
	free(s->env[i]);
	i++;
	while (s->env[i])
	{
		new_env[i - 1] = s->env[i];
		i++;
	}
	free(s->env);
	s->env = new_env;
}

void	ft_set_cd(t_shell *s)
{
	char	*oldpwd;
	char	*newpwd;
	char	*tmp;

	oldpwd = ft_getenv(s->env, "PWD");
	newpwd = getcwd(NULL, 0);
	tmp = ft_getenv(s->env, "OLDPWD");
	if (tmp)
	{
		free(tmp);
		if (oldpwd)
			ft_reset(s->env, "OLDPWD", oldpwd);
		else
			ft_unset_real(s, "OLDPWD");
	}
	if (oldpwd)
		ft_reset(s->env, "PWD", newpwd);
	if (oldpwd)
		free(oldpwd);
	if (newpwd)
		free(newpwd);
}

void	ft_emptycd(t_shell *s)
{
	char	*tmp2;

	tmp2 = ft_getenv(s->env, "HOME");
	if (tmp2)
	{
		chdir(tmp2);
		ft_set_cd(s);
	}
	if (tmp2)
		free(tmp2);
}

void	ft_cd(t_shell *s)
{
	s->exit = 0;
	if (!s->t[s->i].arg[1])
		ft_emptycd(s);
	else if (!s->t[s->i].arg[1][0])
		return ;
	else if (s->t[s->i].arg[2])
	{
		printf("cd: too many arguments");
		s->exit = 1;
	}
	else
	{
		if (ft_isdir(s->t[s->i].arg[1]))
		{
			chdir(s->t[s->i].arg[1]);
			ft_set_cd(s);
		}
		else
		{
			printf("cd: %s: No such file or directory\n", s->t[s->i].arg[1]);
			s->exit = 1;
		}
	}
}

bool	ft_env_check(char *var)
{
	int	i;

	i = 0;
	while (var && var[i])
	{
		if (var[i] == '=')
			return (true);
		i++;
	}
	return (false);
}

int	ft_env(char **arg, char **env)
{
	int	i;

	(void)arg;
	i = -1;
	while (env[++i])
	{
		if (ft_env_check(env[i]))
			printf("%s\n", env[i]);
	}
	return (0);
}

bool	ft_has_equal(char *arg)
{
	int	i;

	i = -1;
	while (arg[++i])
	{
		if (arg[i] == '=')
			return (true);
	}
	return (false);
}

bool	ft_isvarn(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (!((str[i] >= '0' && str[i] <= '9')
			|| (str[i] >= 'a' && str[i] <= 'z')
			|| (str[i] >= 'A' && str[i] <= 'Z')
			|| (str[i] == '_') || (str[i] == '=')))
			return (false);
		else
			i++;
	}
	return (true);
}

void	ft_unset(t_shell *s)
{
	int	i;
	char	*tmp;

	s->exit = 0;
	i = 0;
	while (s->t[s->i].arg[++i])
	{
		if (ft_isvarn(s->t[s->i].arg[i]) && !(ft_has_equal(s->t[s->i].arg[i])))
		{
			tmp = ft_getenv(s->env, s->t[s->i].arg[i]);
			if (tmp)
			{
				free (tmp);
				ft_unset_real(s, s->t[s->i].arg[i]);
			}
		}
		else
		{
			printf("unset: `%s': not a valid identifier\n", s->t[s->i].arg[i]);
			s->exit = 1;
		}
	}
}

void	ft_export_arg_len(char *arg, int *nlen, int *clen)
{
	int	i;

	i = 0;
	while (arg[i] && arg[i] != '=')
		i++;
	nlen[0] = i;
	while (arg[i])
		i++;
	clen[0] = i - nlen[0] - 1;
}

void	ft_read_export_arg(char *arg, char **varn, char **varc)
{
	int	i;
	int	nlen;
	int	clen;

	i = 0;
	ft_export_arg_len(arg, &nlen, &clen);
	if (nlen > 0)
		(*varn) = (char *)ft_calloc(sizeof(char), nlen + 1);
	if (clen > 0)
		(*varc) = (char *)ft_calloc(sizeof(char), clen + 1);
	while (i < nlen)
	{
		(*varn)[i] = arg[i];
		i++;
	}
	i = 0;
	while (i < clen)
	{
		(*varc)[i] = arg[i + nlen + 1];
		i++;
	}
}

char	*ft_strdup(char *src)
{
	int		i;
	char	*dst;

	i = 0;
	while (src[i] != '\0')
		i++;
	dst = malloc(sizeof(char) * i + 1);
	if (!dst)
		return (NULL);
	i = 0;
	while (src[i] != '\0')
	{
		dst[i] = src[i];
		i++;
	}
	dst[i] = '\0';
	return (dst);
}

void	ft_set(t_shell *s, char *varn, char *varc)
{
	char	**new_env;
	int		i;
	int		len;

	i = 0;
	len = 0;
	while (s->env[len] != NULL)
		len++;
	new_env = ft_calloc(sizeof(char *), len + 2);
	while (s->env[i] != NULL)
	{
		new_env[i] = s->env[i];
		i++;
	}
	if (varc)
		new_env[i] = ft_rereset(varn, varc);
	else
		new_env[i] = ft_strdup(varn);
	free(s->env);
	s->env = new_env;
}

void	ft_export(t_shell *s)
{
	int		i;
	char	*varn;
	char	*varc;
	char	*tmp;

	s->exit = 0;
	i = 0;
	while (s->t[s->i].arg[++i])
	{
		if (ft_isvarn(s->t[s->i].arg[i]) && s->t[s->i].arg[i][0] != '=' && s->t[s->i].arg[1][0])
		{
			varn = NULL;
			varc = NULL;
			ft_read_export_arg(s->t[s->i].arg[i], &varn, &varc);
			tmp = ft_getenv(s->env, varn);
			if (tmp)
			{
				ft_reset(s->env, varn, varc);
				free(tmp);
			}
			else if (!tmp)
				ft_set(s, varn, varc);
			if (varc)
				free(varc);
			if (varn)
				free(varn);
		}
		else
		{
			printf("export: `%s': not a valid identifier\n", s->t[s->i].arg[i]);
			s->exit = 1;
		}
	}
}