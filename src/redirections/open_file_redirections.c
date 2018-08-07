/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   open_file_redirections.c                         .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: jecombe <marvin@le-101.fr>                 +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/08/02 15:37:51 by jecombe      #+#   ##    ##    #+#       */
/*   Updated: 2018/08/07 19:57:50 by jecombe     ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../../include/execute.h"

void			ft_open_redirect(char *file, int flag, int flag2)
{
	int ret2;

	if (flag2 == O_WRONLY)
				ret2 = open(file, O_WRONLY | flag | O_CREAT, S_IRUSR | S_IRGRP | S_IWGRP | S_IWUSR);
			if (flag2 == O_RDONLY)
				ret2 = open(file, O_RDONLY);
			if (flag2 == O_RDONLY)
				dup2(ret2, 0);
			else
				dup2(ret2, 1);
}
