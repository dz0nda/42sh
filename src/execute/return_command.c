/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   return_command.c                                 .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: dzonda <marvin@le-101.fr>                  +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/09/28 05:41:48 by dzonda       #+#   ##    ##    #+#       */
/*   Updated: 2018/11/02 16:15:22 by jecombe     ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "heart.h"

static int			ft_waiting(int result)
{
	int status;
	int ret;

	status = 0;
	wait(&status);
	while (wait(NULL) > 0)
		;
	ret = WEXITSTATUS(status);
	if (result != -1)
		return (result);
	if (ret > 0)
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}

int					ft_return_command(t_loop *loop)
{
	if (ft_waiting(loop->result) == EXIT_SUCCESS)
	{
		if (loop->bin == NULL && loop->result == -1)
		{
			add_to_set("?", "1");
			return (EXIT_FAILURE);
		}
		add_to_set("?", "0");
		ft_strdel(&loop->bin);
		return (EXIT_SUCCESS);
	}
	add_to_set("?", "1");
	ft_strdel(&loop->bin);
	return (EXIT_FAILURE);
}
