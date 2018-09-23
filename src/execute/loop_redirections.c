/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   loop_redirections.c                              .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: jecombe <marvin@le-101.fr>                 +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/09/23 20:31:56 by jecombe      #+#   ##    ##    #+#       */
/*   Updated: 2018/09/23 20:50:55 by jecombe     ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "heart.h"

int		ft_loop_redirect(t_redirect *redirect,  int fd2, int fd_one, t_loop *loop)
{
	int file;
	int flag;
	int nb;

	flag = 0;
	file = -1;
	if (fd2 > 1)
	{

		loop->fd_out = ft_open_redirect(".tmp_file", O_TRUNC, O_WRONLY);
		dup2(loop->fd_out, 1);
	}
	while (redirect)
	{
		if (redirect->redirect == DLESS)
			loop->fd_in = ft_redirect_heredoc(redirect, 0);
		if (redirect->redirect == GREAT || redirect->redirect == DGREAT)
		{
			if ((nb = ft_check_file_is_directory(redirect->file)) == -1)
			{
				ft_print_message(redirect->file, nb);
				return (EXIT_FAILURE);
			}
			flag = ft_return_flag(redirect);
			loop->fd_out = ft_open_redirect(redirect->file ,flag, O_WRONLY);
			if (loop->fd_out < 0)
			{
				ft_print_message(redirect->file, -2);
				return (EXIT_FAILURE);
			}
			dup2(loop->fd_out, redirect->fd);
		}
		if (redirect->redirect == LESS)
		{
			if ((nb = ft_check_source(redirect->file)) == -3)
			{
				ft_print_message(redirect->file, nb);
				return (EXIT_FAILURE);
			}
			loop->fd_in = ft_open_redirect(redirect->file, O_RDONLY, 0);
			if (loop->fd_in < 0)
			{
				ft_print_message(redirect->file, -2);
				return (EXIT_FAILURE);
			}
		}
		if (redirect->redirect == GREATAND || redirect->redirect == LESSAND)
		{
			if (ft_strcmp("-", redirect->file) == 0)
			{
				close(redirect->fd);
			}
			if (ft_strcmp("1", redirect->file) == 0)
				dup2(1, STDERR_FILENO);
			if (ft_strcmp("2", redirect->file) == 0)
				dup2(STDERR_FILENO, fd_one);
		}
		redirect = redirect->next;
	}
	return (EXIT_SUCCESS);
}
