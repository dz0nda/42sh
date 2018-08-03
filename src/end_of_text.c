/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   end_of_text.c                                    .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: dewalter <marvin@le-101.fr>                +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/06/19 08:32:55 by dewalter     #+#   ##    ##    #+#       */
/*   Updated: 2018/08/02 21:41:41 by dewalter    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "stdin.h"

void	end_of_text(t_editor *ed)
{
	char buf[4096];

	if ((ed->last_row - get_cursor_position(1)) > 0)
		tputs(tgoto(tgetstr("DO", NULL), 0, ed->last_row - get_cursor_position(1)), 1, ft_putchar);
	ft_putchar('\n');
	getcwd(buf, sizeof(buf));
	display_prompt(find_var_string(g_env, "HOME", 0), PROMPT);
	ed->last_row = get_cursor_position(1);
	ed->first_row = ed->last_row;
	ed->prompt = 0;
	if (ed->line)
		ft_strdel(&(ed->line));
//	ft_putchar(7);
	ed->cursor_str_pos = 0;
}
