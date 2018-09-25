/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   ft_tabsplit.c                                    .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: gmadec <marvin@le-101.fr>                  +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/09/25 03:31:24 by gmadec       #+#   ##    ##    #+#       */
/*   Updated: 2018/09/25 12:30:44 by gmadec      ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../../include/heart.h"

static int			issep(const char *s, int i)
{
	if (ft_isseparator(s[i]) && (i == 0 || (i > 0 && s[i - 1] != '\\')))
		return (1);
	return (0);
}

static size_t		wordlen(const char *s, size_t index, int *cursor_pos)
{
	int i = index;
	size_t	count;
	char	c;

	c = s[i];
	count = 0;
	printf("\n000\n");
	if (ft_isseparator(c))
		while (s[i] == c)
		{
			printf("%c", s[i]);
			count++;
			i++;
		}
	else if (ft_isblank(c))
	{
//		while (ft_isblank(s[i]) && s[i] && !(i == *cursor_pos))
		while (ft_isblank(s[i]) && s[i])
		{
			printf("%c", s[i]);
			i++;
			count++;
		}
		*cursor_pos = i == *cursor_pos ? -1 : *cursor_pos;
	}
	else if (ft_isprint(c) && !ft_isblank(c))
		while (ft_isprint(s[i]) && !ft_isblank(s[i]) && s[i] && !issep(s, i))
		{
			printf("%c", s[i]);
			i++;
			count++;
		}
	printf("\n111\n");
	return (count);
}

char				**ft_tabsplit(const char *s, int cursor_pos)
{
	char	**tablo;
	size_t	i;
	char	*tmp;
	int		set_cursor[2];

	set_cursor[1] = cursor_pos;
	set_cursor[0] = cursor_pos;
	i = 0;
	tablo = NULL;
	if (s)
		while (s[i] != '\0')
		{
			tmp = ft_strsub(s, ((int)i), wordlen(s, i, &set_cursor[0]));
			ft_malloc_cmd(&tablo, tmp);
			ft_strdel(&tmp);
			i += wordlen(s, i, &set_cursor[1]);
		}
	return (tablo);
}
