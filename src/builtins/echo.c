/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   echo.c                                           .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: jecombe <marvin@le-101.fr>                 +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/08/02 15:34:13 by jecombe      #+#   ##    ##    #+#       */
/*   Updated: 2018/08/29 18:32:49 by jecombe     ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../../include/execute.h"

int 		ft_echo_redirect(int fd_open, char **cmd, int ok, int slash_n)
{
	int i = 0;

	while (cmd[i])
	{
		ft_putstr_fd(cmd[i], fd_open);
		if (cmd[i + 1])
			ft_putchar_fd(' ', fd_open);
		i++;
	}
	if (slash_n == 0 && ok == 0)
		ft_putchar_fd('\n', fd_open);
	return (EXIT_SUCCESS);

}

int 		ft_echo_normal(t_op *t_exec, int i, int ok, int slash_n)
{	
	if (ok == 1)
	{
		ft_putchar('\n');
		return (EXIT_SUCCESS);
	}
	while (t_exec->cmd[i])
	{
		ft_putstr(t_exec->cmd[i]);
		if (t_exec->cmd[i + 1])
			ft_putchar(' ');
		i++;
	}
	if (slash_n == 0)
		ft_putchar('\n');
	return (EXIT_SUCCESS);

}
int 		ft_echo(t_op *t_exec, int flag)
{
	//printf("ECHO\n");
	int flag2;
	int fd_open;
	int i;
	int slash_n;
	int ok = 0;
	t_op *op = NULL;
	if (t_exec->cmd[1] == NULL)
	{
		ok = 1;
		t_exec->cmd[1] = "\n";
		t_exec->cmd[2] = NULL;
	}
	slash_n = 0;
	i = 1;
	if (ft_strcmp(t_exec->cmd[1], "-n") == 0)
	{
		slash_n = 1;
		i++;
	}
	if (t_exec->redirect)
	{
		//***********Gestion des mutliples redirections, pour bientot*********//
		pid_t pid;
		if ((fd_open = ft_loop_redirect(t_exec->redirect, NULL, pid, 1, t_exec->cmd + i, op, -1)) == EXIT_FAILURE)
			return (EXIT_FAILURE);
		else
		{
			if (t_exec->redirect->fd > 1)
			{
				printf("ttttttttt\n");
				fd_open = t_exec->redirect->fd;
			}
			//if (t_exec->redirect->redirect == DLESS)
				//ft_echo_normal(t_exec, i, ok, slash_n);
			//else
			if (fd_open ==  0)
				fd_open = 1;
			printf("fd<-open-> %d\n", fd_open);
				ft_echo_redirect(fd_open, t_exec->cmd + i, ok, slash_n);
		}
		/////**********************************************************////
	}
	else
	{
		printf("ET NONO\n");
		ft_echo_redirect(1, t_exec->cmd + i, ok, slash_n);
	}
		//ft_echo_normal(t_exec, i, ok, slash_n);
	return (EXIT_SUCCESS);
}
