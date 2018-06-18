/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   ft_minishell.c                                   .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: dzonda <marvin@le-101.fr>                  +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/04/08 12:05:41 by dzonda       #+#   ##    ##    #+#       */
/*   Updated: 2018/06/06 15:26:17 by jecombe     ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "minishell.h"

void			ft_handle_signal(int signo)
{
	if (signo == SIGINT)
	{
		ft_putchar('\n');
		g_stat = 1;
		ft_putprompt();
	}
}
void			ft_handle_signal2(int signo)
{
	if (signo == SIGINT)
	{
		printf("ok saoooooooooooooope\n");
		ft_putchar('\n');
		g_stat = 1;
		ft_minishell();
	}
}


void			ft_putprompt(void)
{
	char		*tmp;
	char		*pwd;
	char		*log;

	pwd = NULL;
	g_stat == 0 ? ft_putstr("⚫️  ") : ft_putstr("🔴  ");
	if ((tmp = ft_getenv("PWD")))
		pwd = (ft_strrchr(tmp, '/') && ft_strcmp(tmp, "/") != 0) ?
			ft_strdup(ft_strrchr(tmp, '/') + 1) : ft_strdup(tmp);
	if (pwd)
	{
		ft_strdel(&tmp);
		ft_putstr(YELLOW);
		ft_putstr(BOLD);
		ft_putstr(pwd);
		ft_putstr(END);
		ft_putchar(' ');
		ft_strdel(&pwd);
	}
	if ((log = ft_getenv("USER")))
		ft_putstr(log);
	log ? ft_strdel(&log) : 0;
	ft_putstr(PURPLE);
	ft_putstr("$> ");
	ft_putstr(END);
}

void			ft_minishell(void)
{
	char		buff[PATH_MAX];
	int			i;
	t_token		*tokenlst;

	i = 0;
	while (101)
	{
		ft_putchar('\r');
		ft_putprompt();
		g_stat = 0;
		ft_bzero(buff, PATH_MAX);
		if (!(i = read(0, buff, PATH_MAX)))
			break ;
		tokenlst = ft_init(tokenlst, buff);
		g_stat = ft_solver(tokenlst);
		ft_token_del(tokenlst);
	}
}

int				main(void)
{
	extern char	**environ;

	ft_env_new((const char **)environ);
	signal(SIGINT, ft_handle_signal);
	ft_minishell();
	ft_env_del();
	exit(EXIT_SUCCESS);
}
