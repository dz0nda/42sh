/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   open_file_redirections.c                         .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: jecombe <marvin@le-101.fr>                 +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/08/02 15:37:51 by jecombe      #+#   ##    ##    #+#       */
/*   Updated: 2018/09/14 16:37:50 by jecombe     ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "heart.h"

int			ft_open_redirect(char *file, int flag, int flag2)
{
	int ret2;

	if (flag2 == O_WRONLY && flag != O_RDONLY)
		return (ret2 = open(file, O_WRONLY | flag | O_CREAT, S_IRUSR | S_IRGRP
					| S_IWGRP | S_IWUSR));
	if (flag == O_RDONLY)
		return (ret2 = open(file, flag, 0644));
	return (EXIT_FAILURE);
}
