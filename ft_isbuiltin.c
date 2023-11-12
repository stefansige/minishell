#include "minishell.h"

int	ft_compare(char *s1, char *s2)
{
	unsigned int	i;

	i = 0;
	if (!s1 || !s2 || (!s1[0] && !s2[0]))
		return (0);
	while (s1[i] && s2[i] && s1[i] == s2[i])
		i++;
	if (s1[i] || s2[i])
		return (0);
	return (1);
}

int	ft_isbuiltin3(t_shell *s, int ver)
{
	if (ft_compare(s->t[s->i].tok, "exit"))
	{
		if (ver == 1)
			//ft_exit(s->arg, s->env);
		return (1);
	}
	return (0);
}

int	ft_isbuiltin2(t_shell *s, int ver)
{
	if (ft_compare(s->t[s->i].tok, "export"))
	{
		if (ver == 1)
			//ft_export(s->arg, s->env);
		return (1);
	}
	else if (ft_compare(s->t[s->i].tok, "unset"))
	{
		if (ver == 1)
			//ft_unset(s->arg, s->env)
		return (1);
	}
	else if (ft_compare(s->t[s->i].tok, "env"))
	{
		if (ver == 1)
		//	ft_env(s->arg, s->env)
		return (1);
	}
	else
		return (ft_isbuiltin3(s, ver));
	return (0);
}

int	ft_isbuiltin(t_shell *s, int ver)
{
	if (ft_compare(s->t[s->i].tok, "echo"))
	{
		if (ver == 1)
			//ft_echo(s->arg, s->env);
		return (1);
	}
	else if (ft_compare(s->t[s->i].tok, "cd"))
	{
		if (ver == 1)
			//ft_cd(s->arg, s->env);
		return (1);
	}
	else if (ft_compare(s->t[s->i].tok, "pwd"))
	{
		if (ver == 1)
			//ft_pwd(s->arg, s->env);
		return (1);
	}
	else
		return (ft_isbuiltin2(s, ver));
	return (0);
}
