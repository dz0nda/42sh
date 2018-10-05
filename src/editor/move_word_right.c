/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   move_word_right.c                                .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: dewalter <marvin@le-101.fr>                +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/06/19 04:56:50 by dewalter     #+#   ##    ##    #+#       */
/*   Updated: 2018/10/05 16:49:30 by dewalter    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "heart.h"

static int		check_if_next_word(char *line)
{
	int cursor_str_pos;

	cursor_str_pos = 0;
	while (line[cursor_str_pos])
	{
		if (cursor_str_pos && (line[cursor_str_pos - 1] == ' ' || line
		[cursor_str_pos - 1] == '\t') && line[cursor_str_pos] >= 33
		&& line[cursor_str_pos] <= 126)
			return (cursor_str_pos);
		cursor_str_pos++;
	}
	return (0);
}

void			move_word_right(t_editor *ed)
{
	size_t next_word_pos;

	next_word_pos = check_if_next_word(ed->line + ed->cursor_str_pos);
	if (next_word_pos)
	{
		next_word_pos += ed->cursor_str_pos;
		while (ed->cursor_str_pos != next_word_pos)
			move_cursor_right(ed);
	}
}
