/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: azennari <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/26 17:53:27 by azennari          #+#    #+#             */
/*   Updated: 2023/11/18 20:08:45 by azennari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_pwd(char **arg, char **env)
{
	char	*pwd;

	void(arg);
	void(env);
	pwd = getcwd(NULL, 0);
	getcwd(pwd, sizeof(pwd));
	printf("%s\n", pwd);
}

int	ft_getenv_n(char **env, char *s)
{
	int	i;
	int	j;

	while (s && s[i] && env[j] && env[j][i])
	{
		if (env[j][i] != s[i])
		{
			i = 0;
			j++;
		}
		else
			i++;
	}
	if (!env[j] || !s || i != ft_strlen(s))
		return (NULL);
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
	int	p;

	p = ft_getenv_n(env, varn);
	free(env[p]);
	env[p] = ft_rereset(varn, varc);
}

void	ft_set_cd(char **env)
{
	char	*oldpwd;

	oldpwd = ft_getenv(env, "PWD");
	if (ft_getenv(env, "OLDPWD"))
	{
		if (oldpwd)
			ft_reset(env, "OLDPWD", oldpwd);
		else
			ft_unset_real(oldpwd, env);
	}
	if (oldpwd)
		ft_reset(env, "PWD", getcwd(NULL, 0));
}

void	ft_cd(char **arg, char **env)
{
	if (arg[2])
		printf("cd: too many arguments");
	else
	{
		if (ft_isdir(arg[i]))
		{
			chdir(arg[i]);
			ft_set_cd(env);
		}
		else
			printf("cd: %s: No such file or directory", *arg[0]);
	}
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

void	ft_read_export_arg(char *arg, char *varn, char *varc)
{
	int	i;
	int	nlen;
	int	clen;

	i = 0;
	ft_export_arg_len(arg, &nlen, &clen);
	varn = (char *)ft_calloc(sizeof(char), nlen + 1);
	varc = (char *)ft_calloc(sizeof(char), clen + 1);
	while (i <= nlen)
	{
		varn[i] = arg[i];
		i++;
	}
	i = 0;
	while ((i + nlen + 1) <= clen)
	{
		varc[i] = arg[i + nlen + 1];
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

void	ft_set(char **env, char *varn, char *varc)
{
	char	**new_env;
	int		i;
	int		len;

	i = 0;
	len = 0;
	while (env[len])
		len++;
	new_env = ft_calloc(sizeof(char *), len + 1);
	while (env[++i])
		new_env[i] = env[i];
	if (varc)
		new_env[i] = ft_rereset(varn, varc);
	else
		new_env[i] = ft_strdup(varn);
	free(env);
	env = new_env;
}

void	ft_export(char **arg, char **env)
{
	int		i;
	char	*varn;
	char	*varc;

	i = 0;
	while (arg[++i])
	{
		if (ft_isvarn(arg[i]))
		{
			ft_read_export_arg(arg[i], varn, varc);
			if (ft_getenv(env, varn))
				ft_reset(env, varn, varc);
			else if (varc)
				ft_set(env, varn, varc);
			free(varn);
			free(varc);
		}
		else
			printf("export: `%s': not a valid identifier", arg[i]);
	}
}

void	ft_export_forth(char **env)
{
	int	i;

	i = -1;
	while (env[++i])
		printf("declare -x %s\n", env[i]);
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

void	ft_unset_real(char *arg, char **env)
{
	char	**new_env;
	int		i;
	int		p;

	i = 0;
	while (env[i])
		i++;
	p = ft_getenv_n(env, arg);
	free(env[p]);
	new_env = ft_calloc(sizeof(char *), i);
	i = 0;
	while (++i < p)
		new_env[i] = env[i];
	while (env[++i])
		new_env[i - 1] = env[i];
	free(env);
	env = new_env;
}

void	ft_unset(char **arg, char **env)
{
	int	i;

	i = 0;
	while (arg[++i])
	{
		if (ft_isvarn(arg[i]) && !(ft_has_equal(arg[i])))
		{
			if (ft_getenv_n(env, arg[i]))
				ft_unset_real(arg[i], env);
		}
		else
			printf("unset: `%s': not a valid identifier", arg[i]);
	}
}

bool	ft_env_check(char *var)
{
	int	i;

	i = 0;
	while (var[i] && var[i] != '=')
		i++;
	if (var[i])
		return (true);
	else
		return (false);
}

void	ft_env(char **arg, char **env)
{
	int	i;

	(void)arg;
	i = -1;
	while (env[++i])
	{
		if (ft_env_check(env[i]))
			printf("%s\n", env[i]);
	}
}
