/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   historic.c                                       .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: dewalter <marvin@le-101.fr>                +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/08/01 10:01:52 by dewalter     #+#   ##    ##    #+#       */
/*   Updated: 2018/08/01 15:27:56 by dewalter    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "stdin.h"

void	historic(t_editor *ed)
{
	(void)ed;
	int fd;

		printf("OK\n");
	if (!(fd = open("../history", O_RDONLY)))
		printf("OK\n");
}

void	fill_hist_list(t_hist *hist, char *line)
{
	t_hist *now;
	t_hist *new;

	(void)hist;
	(void)line;
	now = NULL;
	new = NULL;
/*	while (hist)
	{
		hist 
	}
	new = (t_hist*)malloc(sizeof(t_hist));*/
}
