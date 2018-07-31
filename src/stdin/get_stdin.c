/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   get_stdin.c                                      .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: dewalter <marvin@le-101.fr>                +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/05/12 00:01:33 by dewalter     #+#   ##    ##    #+#       */
/*   Updated: 2018/07/31 23:43:04 by dzonda      ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../../include/stdin.h"

int		term_reinit(struct termios *raw_mode)
{
	static struct termios term_default;
	static int state = 0;

	if (state == 0)
	{
		tcgetattr(STDIN_FILENO, &term_default);
		state = 1;
	}
	*raw_mode = term_default;
	return (0);
}

int		get_term_raw_mode(int mode)
{
	struct termios raw_mode;

	term_reinit(&raw_mode);
	if (mode)
	{
		raw_mode.c_lflag &= ~(ECHO | ICANON | ISIG);
		raw_mode.c_cflag &= ~(CSIZE | PARENB);
		raw_mode.c_cflag |= CS8;
		raw_mode.c_cc[VMIN] = 1;
		raw_mode.c_cc[VTIME] = 1;
		tcsetattr(STDIN_FILENO, TCSANOW, &raw_mode);
	}
	else
		tcsetattr(STDIN_FILENO, TCSANOW, &raw_mode);
	return (0);
}

int		get_keyboard_key(int *ret, char **line, t_editor *ed, e_prompt prompt)
{
	ioctl(0, TIOCGWINSZ, &sz);
	if (CTRL_D)
		*ret = 0;
	else if (CTRL_C)
		end_of_text(line, ed);
	else if (UP_KEY || DOWN_KEY)
		return (0);
	else if (!ft_strcmp(SHIFT_UP, ed->key) || !ft_strcmp(SHIFT_DOWN, ed->key))
		!ft_strcmp(SHIFT_UP, ed->key) ? move_cursor_up(ed) : move_cursor_down(*line, ed);
	else if (HOME_KEY || END_KEY)
		HOME_KEY ? go_to_begin_of_line(ed) : go_to_end_of_line(ed, *line);
	else if (BACKSPACE && line && ed->cursor_str_pos)
		return (backspace(ed, line));
	else if (LEFT_KEY || RIGHT_KEY)
		LEFT_KEY ? move_cursor_left(ed) : move_cursor_right(ed, *line);
	else if (CTRL_L)
		return (clear_window(*line, ed, prompt));
	else if ((!ft_strcmp(SHIFT_RIGHT, ed->key) || !ft_strcmp(SHIFT_LEFT, ed->key)) && line)
		!ft_strcmp(SHIFT_LEFT, ed->key) ? move_word_left(*line, ed) : move_word_right(*line, ed);
	else if (ed->cursor_str_pos == ft_strlen(*line) && ft_strlen(ed->key) == 1 && ft_isprint(ed->key[0]))
		return (add_char_to_line(ed->key[0], ed));
	else if (ed->cursor_str_pos != ft_strlen(*line) && ft_strlen(ed->key) == 1 && ft_isprint(ed->key[0]))
		return (add_char_into_line(ed->key[0], line, ed));
	else if (CTRL_K && ft_strlen(*line + ed->cursor_str_pos))
		delete_from_cursor_to_end(line, ed);
	else if (CTRL_P)
		paste_clipboard(line, ed);
	return (0);
}

int		line_editor_init(t_editor **ed)
{
	if (!(*ed = (t_editor*)malloc(sizeof(t_editor))))
		return (0);
	(*ed)->clipboard = NULL;
	(*ed)->cursor_str_pos = 0;
	(*ed)->first_row = get_cursor_position(1);
	(*ed)->last_row = (*ed)->first_row;
	return (1);
}

int		get_stdin(char **line, e_prompt prompt)
{
	int ret;
	t_editor *ed;

	get_term_raw_mode(1);
	line_editor_init(&ed);
	display_prompt(prompt == 0 ? find_var_string(g_env, "HOME", 0) : NULL, prompt);
	ed->prompt_size = get_cursor_position(0);
	signal(SIGWINCH, myhandler_winsize_change);
	while ((ret = read(STDIN_FILENO, ed->key, BUFF_SIZE)) > 0)
	{
		tputs(tgetstr("vi", NULL), 1, ft_putchar);
		ed->key[ret] = '\0';
		if (get_keyboard_key(&ret, line, ed, prompt))
			*line = ft_strjoin_free(*line, ed->key);
		tputs(tgetstr("ve", NULL), 1, ft_putchar);
		if (ft_strchr(ed->key, '\n') || (!ret && !(*line)))
			break ;
	}
	if ((ed->last_row - get_cursor_position(1)) != 0)
		tputs(tgoto(tgetstr("DO", NULL), 0,
		ed->last_row - get_cursor_position(1)), 1, ft_putchar);
	get_term_raw_mode(0);
	ft_putchar('\n');
	free(ed);
	return (ret);
}
