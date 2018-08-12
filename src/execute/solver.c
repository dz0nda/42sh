/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   solver.c                                         .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: jecombe <marvin@le-101.fr>                 +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/08/01 01:18:16 by jecombe      #+#   ##    ##    #+#       */
/*   Updated: 2018/08/12 08:04:22 by jecombe     ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../../include/execute.h"
#include "../../include/stdin.h"

int		ft_solver(t_op *t_exec, int fd)
{
	ft_get_bin();
	char *tmp_bin;
	int ok;
	int flag;


	if ((ok = ft_check_command(t_exec->cmd[0])) != 0)
	{
		flag = ft_return_flag2(t_exec);
		if (ft_builtins(t_exec, ok, flag) == EXIT_SUCCESS)
			return (EXIT_SUCCESS);
		else
			return (EXIT_FAILURE);
	}
	else
	{
		tmp_bin = ft_search_bin(t_exec->cmd[0]);
		if (ft_exec(t_exec, tmp_bin) == EXIT_SUCCESS)
			return (EXIT_SUCCESS);
		else
			return (EXIT_FAILURE);
	}
	return (EXIT_FAILURE);
}
