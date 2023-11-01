/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: snovakov <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/25 18:23:22 by snovakov          #+#    #+#             */
/*   Updated: 2023/10/25 18:23:24 by snovakov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_setcmd(t_shell *s)
{
	char	**paths;
	char	*pth;
	int	i;

	if (access(s->t[s->i].tok, F_OK) != 0)
	{
		pth = ft_getenv(s->env, "PATH");
		paths = ft_split(pth, ':');
		free(pth);
		pth = NULL;
		i = 0;
		while (paths && paths[i])
		{
			pth = ft_join(paths[i], s->t[s->i].tok);
			if (access(pth, F_OK) == 0)
			{
				s->t[s->i].cmd = pth;
				ft_free(paths);
				return ;
			}
			i++;
			free(pth);
		}
		ft_free(paths);
	}
	else
		s->t[s->i].cmd = ft_strcpy(s->t[s->i].tok);
}

void	ft_setarg(t_shell *s)
{
	int	i;
	int	k;

	i = s->i + 1;
	k = 0;
	while (s->t[i].type == 2)
	{
		k++;
		i++;
	}
	s->t[s->i].arg = ft_calloc(k + 2, sizeof(char *));
	s->t[s->i].arg[0] = ft_strcpy(s->t[s->i].cmd);
	if (k == 0)
		return;
	k = 1;
	i = s->i + 1;
	while (s->t[i].type == 2)
		s->t[s->i].arg[k++] = s->t[i++].tok;
}

void	ft_child(t_shell *s)
{
	if (s->t[s->i].input != -1)
		dup2(s->t[s->i].input, STDIN_FILENO);
	else
		dup2(s->import, STDIN_FILENO);
	dup2(STDOUT_FILENO, s->pip[1]);
	close(s->pip[0]);
	if (execve(s->t[s->i].cmd, s->t[s->i].arg, s->env) == -1)
		exit(1);
	else
		exit(0);
}

int	ft_fork(t_shell *s)
{
	pid_t pid;
	int	status;

	if (pipe(s->pip) == -1)
		return (ft_perror(s));
	pid = fork();
	if (pid == 0)
		ft_child(s);
	else
	{
		close(s->pip[1]);
		wait(&status);
		if (WEXITSTATUS(status) == 1)
			ft_perror(s);
		close(s->import);
		dup2(s->pip[0], s->import);
		close(s->pip[0]);
	}
	return (0);
}

void	ft_flush(t_shell *s)
{
	pid_t	pid;

	pid = fork();
	if (pid == 0)
	{
		dup2(STDOUT_FILENO, s->import);
		exit(0);
	}
	else
	{
		wait(NULL);
	}
}


void	ft_exec(t_shell *s)
{
	s->i = 0;
	s->nb = 0;
	while (s->t[s->i].tok)
	{
		if (s->t[s->i].type == 1)
		{
			ft_setcmd(s);
			ft_setarg(s);
			if (ft_fork(s))
				return ;
		}
		s->i++;
	}
	ft_flush(s);
}
