/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: snovakov <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/04 16:59:58 by snovakov          #+#    #+#             */
/*   Updated: 2023/10/04 17:00:00 by snovakov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <sys/types.h>
# include <sys/stat.h>
# include <sys/wait.h>
# include <fcntl.h>
# include <errno.h>
# include <dirent.h>
# include <stddef.h>
# include <stdbool.h>
# include <signal.h>

extern int	g_exit;

typedef struct s_token
{
	char	*tok;
	char	*cmd;
	char	**arg;
	char	*here;
	int		input;
	int		output;
	int		type;
}	t_token;
// 1-cmd, 2-arg, 3-pipe, 4-rred, 5-lred, 6-rapp, 7-lapp, 10-file
typedef struct s_shell
{
	char			**env;
	t_token			*t;
	int				tnb;
	int				i;
	unsigned int	exit;
	int				nb;
	int				ln;
	int				k;
	int				y;
	int				flag;
	int				import;
	char			*l;
	char			*prompt;
}	t_shell;

void			*ft_calloc(size_t size, size_t count);
unsigned int	ft_strlen(char *s);
void			ft_dollar(t_shell *s);
int				ft_isvname(char c);
unsigned int	ft_dolen(char *s, int start);
char			*ft_getenv(char **env, char *s);
int				ft_token(t_shell *s);
char			*ft_join(char *str1, char *str2);
int				ft_perror(t_shell *s);
int				ft_berror(t_shell *s);
char			*ft_strcpy(char *s);
char			**ft_split(char *s, char c);
void			ft_exec(t_shell *s);
void			ft_free(char **s);
int				ft_isbuiltin(t_shell *s, int ver);
int				ft_compare(char *s1, char *s2);
void			ft_heredoc(t_shell *s);
char			*ft_strjoin(char *s1, char *s2);
int				ft_isarg(int i);
int				ft_atoi(const char *nptr);
int				ft_isdir(char *s);
int				ft_echo(char **arg);
int				ft_pwd(char **arg, char **env);
int				ft_env(char **arg, char **env);
int				ft_isbuiltin2(t_shell *s, int ver);
int				ft_strcmp(char *s1, char *s2);
int				ft_export_forth(char **env);
void			ft_cd(t_shell *s);
void			ft_reset(char **env, char *varn, char *varc);
void			ft_unset(t_shell *s);
char			**ft_dpcpy(char **s);
void			ft_export(t_shell *s);
void			ft_exit(t_shell *s, int ver);
void			ft_restart(t_shell *s);
void			ft_restart2(t_shell *s);
int				ft_valid(char *line);
void			signal_ctrlc(int signum);
int				ft_lexor(t_shell *s);
int				ft_dpstrlen(char **s);
char			*ft_adddol(char *l, int i, char *env);
char			*ft_rmdol(char *l, int i);
void			ft_disable(t_shell *s);
int				ft_checkinput(t_shell *s);
int				ft_isact(int n);
int				ft_setinput(t_shell *s);
int				ft_checkoutput(t_shell *s);
void			ft_writein(t_shell *s, int hdpip[]);
void			ft_checkexit(t_shell *s);
void			ft_lastcmd(t_shell *s);
int				ft_setcmd(t_shell *s);
void			ft_permdenied(t_shell *s);
void			ft_setarg(t_shell *s);
void			ft_unset_real(t_shell *s, char *arg);
int				ft_islash(char *s);
int				ft_getenv_n(char **env, char *s);
char			*ft_rereset(char *varn, char *varc);
void			ft_export_arg_len(char *arg, int *nlen, int *clen);
bool			ft_isvarn(char *str);
int				ft_iss(char c);
int				ft_ism(char c);
int				ft_qplus(t_shell *s, char c);
void			ft_iplus(t_shell *s, int ver);
void			ft_lalloc(t_shell *s, int fun, int ver);
void			ft_lset(t_shell *s, int fun, int ver);

#endif
