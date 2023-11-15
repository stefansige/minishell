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

int	ft_isdir(char *s)
{
	DIR	*dir;

	dir = opendir(s);
	if (dir != NULL)
	{
		closedir(dir);
		return (1);
	}
	return (0);
}

int	ft_islash(char *s)
{
	int	i;

	i = 0;
	while (s && s[i])
	{
		if (s[i] == '/')
			return (1);
		i++;
	}
	return (0);
}

void	ft_setempty(t_shell *s)
{
	int	i;

	i = s->i + 1;
	while (s->t[i].tok)
	{
		if (s->t[i].type == 1)
		{
			if (s->t[i].input == -1)
			{
				s->t[i].input = -5;
				s->t[i].here = ft_calloc(sizeof(char), 1);
			}
			return ;
		}
		i++;
	}
}

int	ft_setcmd2(t_shell *s)
{
	char	**paths;
	char	*pth;

	pth = ft_getenv(s->env, "PATH");
	paths = ft_split(pth, ':');
	free(pth);
	s->nb = 0;
	while (paths && paths[s->nb])
	{
		pth = ft_join(paths[s->nb], s->t[s->i].tok);
		if (access(pth, F_OK) == 0)
		{
			s->t[s->i].cmd = pth;
			ft_free(paths);
			return (1);
		}
		s->nb++;
		free(pth);
	}
	ft_free(paths);
	printf("%s: command not found\n", s->t[s->i].tok);
	ft_setempty(s);
	s->exit = 127;
	return (0);
}

int	ft_setcmd(t_shell *s)
{
	if (ft_isdir(s->t[s->i].tok))
	{
		printf ("bash: %s: Is a directory\n", s->t[s->i].tok);
		s->exit = 126;
	}
	else if (ft_islash(s->t[s->i].tok) && access(s->t[s->i].tok, F_OK) != 0)
	{
		printf ("bash: %s: No such file or directory\n", s->t[s->i].tok);
		s->exit = 127;
	}
	else if (ft_isbuiltin(s, 0) == 1)
		return (1);
	else if (access(s->t[s->i].tok, F_OK) == 0)
	{
		s->t[s->i].cmd = ft_strcpy(s->t[s->i].tok);
		return (1);
	}
	else if (access(s->t[s->i].tok, F_OK) != 0)
		return (ft_setcmd2(s));
	return (0);
}

void	ft_setarg2(t_shell *s)
{
	int	i;
	int	k;

	k = 1;
	i = s->i + 1;
	while (s->t[i].tok && s->t[i].type != 3)
	{
		if (s->t[i].tok && s->t[i].type == 2)
			s->t[s->i].arg[k++] = ft_strcpy(s->t[i].tok);
		i++;
	}
	s->t[s->i].arg[k] = 0;
}

void	ft_setarg(t_shell *s)
{
	int	i;
	int	k;

	i = s->i + 1;
	k = 0;
	while (s->t[i].tok && s->t[i].type != 3)
	{
		if (s->t[i].tok && s->t[i].type == 2)
			k++;
		i++;
	}
	s->t[s->i].arg = ft_calloc(sizeof(char *), k + 2);
	s->t[s->i].arg[0] = ft_strcpy(s->t[s->i].cmd);
	if (k == 0)
	{
		s->t[s->i].arg[1] = 0;
		return ;
	}
	ft_setarg2(s);
}

void	ft_writein(t_shell *s, int hdpip[])
{
	int	i;

	i = 0;
	while (s->t[s->i].here && s->t[s->i].here[i])
	{
		write(hdpip[1], &s->t[s->i].here[i], 1);
		i++;
	}
	write(hdpip[1], &s->t[s->i].here[i], 1);
}

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
	//if (ft_isbuiltin(s, 1))
	//	exit(1);
	if (execve(s->t[s->i].cmd, s->t[s->i].arg, s->env) == -1)
		exit(errno);
	exit(0);
}

int	ft_parent(t_shell *s, int pip[], int hdpip[])
{
	int	status;

	if (s->t[s->i].input == -5)
	{
		close (hdpip[0]);
		ft_writein(s, hdpip);
		close (hdpip[1]);
	}
	close(pip[1]);
	wait(&status);
	s->exit = WEXITSTATUS(status);
	if (s->i != s->ln)
		dup2(pip[0], s->import);
	close(pip[0]);
	return (0);
}

int	ft_fork(t_shell *s)
{
	pid_t pid;
	int	pip[2];
	int	hdpip[2];

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

void	ft_lastcmd(t_shell *s)
{
	int	i;

	i = s->tnb - 1;
	while (i >= 0)
	{
		if (s->t[i].type == 1)
		{
			s->ln = i;
			return ;
		}
		i--;
	}
}

void	ft_exec(t_shell *s)
{
	s->i = 0;
	s->nb = 0;
	ft_lastcmd(s);
	while (s->t[s->i].tok)
	{
		if (s->t[s->i].type == 1)
		{
			if (ft_setcmd(s) == 1)
			{
				if (access(s->t[s->i].cmd, X_OK) != 0)
				{
					printf("bash: %s: Permission denied\n", s->t[s->i].tok);
					s->exit = 126;
				}
				else
				{
					ft_setarg(s);
					if (ft_fork(s))
						return ;
				}
			}
		}
		s->i++;
	}
}
