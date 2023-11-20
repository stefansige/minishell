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

void	ft_child(t_shell *s, int pip[], int hdpip[])
{
	signal(SIGINT, SIG_DFL);
	signal(SIGQUIT, SIG_DFL);
	if (s->t[s->i].input == -5)
	{
		close(hdpip[1]);
		dup2(hdpip[0], STDIN_FILENO);
	}
	else if (s->t[s->i].input != -1)
		dup2(s->t[s->i].input, STDIN_FILENO);
	else
		dup2(s->import, STDIN_FILENO);
	if (s->t[s->i].output != -1)
		dup2(s->t[s->i].output, STDOUT_FILENO);
	else if (s->i != s->ln)
		dup2(pip[1], STDOUT_FILENO);
	close(pip[0]);
	if (ft_isbuiltin(s, 1))
		ft_exit(s, 1);
	if (execve(s->t[s->i].cmd, s->t[s->i].arg, s->env) == -1)
		s->exit = errno;
	else
		s->exit = 0;
	ft_exit(s, 1);
}

void	signal_fork(int signum)
{
	(void)signum;
	g_exit = 130;
	printf("\n");
}

int	ft_parent(t_shell *s, int pip[], int hdpip[])
{
	int	status;

	signal(SIGINT, signal_fork);
	signal(SIGQUIT, signal_fork);
	if (s->t[s->i].input == -5)
	{
		close (hdpip[0]);
		ft_writein(s, hdpip);
		close (hdpip[1]);
	}
	close(pip[1]);
	wait(&status);
	if (WIFEXITED(status))
		s->exit = WEXITSTATUS(status);
	else if (WIFSIGNALED(status))
		g_exit = 128 + (WTERMSIG(status));
	if (s->i != s->ln)
		dup2(pip[0], s->import);
	close(pip[0]);
	return (0);
}

int	ft_fork(t_shell *s)
{
	pid_t	pid;
	int		pip[2];
	int		hdpip[2];

	if (pipe(pip) == -1 || pipe(hdpip) == -1)
	{
		perror("pipe:");
		return (1);
	}
	pid = fork();
	if (pid == 0)
		ft_child(s, pip, hdpip);
	else
	{
		if (ft_parent(s, pip, hdpip))
			return (1);
	}
	return (0);
}

void	ft_exec(t_shell *s)
{
	ft_checkexit(s);
	s->i = 0;
	s->nb = 0;
	ft_lastcmd(s);
	while (s->t[s->i].tok && g_exit == 0)
	{
		if (s->t[s->i].type == 1)
		{
			if (ft_setcmd(s) == 1)
			{
				if (access(s->t[s->i].cmd, X_OK) != 0
					&& ft_isbuiltin(s, 0) == 0 && ft_isbuiltin2(s, 0) == 0)
					ft_permdenied(s);
				else
				{
					ft_setarg(s);
					if (ft_isbuiltin2(s, 1) == 1)
						;
					else if (ft_fork(s))
						return ;
				}
			}
		}
		s->i++;
	}
}
