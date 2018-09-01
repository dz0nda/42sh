/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   execute.c                                     .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: jecombe <marvin@le-101.fr>                 +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/08/01 01:52:13 by jecombe      #+#   ##    ##    #+#       */
/*   Updated: 2018/08/29 18:18:24 by gmadec      ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../../include/execute.h"

int				ft_exec(t_op *tmp_op, char *bin_cmd, int fd, pid_t pid)
{
	//pid_t		cpid;
	int			status;
	int			ret;
	t_redirect *redirect;

	redirect = NULL;
	ret = 0;
	if (tmp_op->redirect)
	{
		redirect = tmp_op->redirect;
	}
		//Gestion des multiples redirections
	if (pid == 0 || fd == -88)
	{
		//Gestion des multiples redirections
			if (ft_loop_redirect(redirect, bin_cmd, pid, 0, tmp_op->cmd, tmp_op, fd) == EXIT_SUCCESS)
		{
			;
		}
		else
			return(EXIT_FAILURE);
		//EXECVE
		if (execve(bin_cmd, tmp_op->cmd, g_env) == -1)
			exit(EXIT_FAILURE);
		else
			exit(EXIT_SUCCESS);
	}
	if (pid > 0 && fd != -88)
	{
		wait(&status);
		ret = WEXITSTATUS(status);
		binary_signal(status, pid, bin_cmd);
	}
	return (ret > 0 ? EXIT_FAILURE : EXIT_SUCCESS);
}
