/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   42sh.c                                           .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: dzonda <marvin@le-101.fr>                  +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/09/28 03:43:21 by dzonda       #+#   ##    ##    #+#       */
/*   Updated: 2018/10/07 08:18:18 by dzonda      ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "heart.h"

void	ft_watch_result(char *line, t_lex lex, t_seq *n_seq);

int					heart_of_101sh(char *line, int fd_base)
{
	t_lex			lex;
	t_seq			*seq;
	int				ret;

	ret = 0;
	ft_memset(&lex, 0, sizeof(t_lex));
	seq = NULL;
	lex = lexer(line);
	history_save((char ***)NULL, line, 1, (char *)NULL);
	if ((seq = ft_parsing(lex)))
	{
		if (!(ret = extension(&seq)))
			ft_sequence(seq, fd_base);
	//	int i =-1;
	//	while (seq->op->cmd[++i])
	//	printf("CMD[%d] == %s\n", i, seq->op->cmd[i]);
	//	i = 0;
	//	while(seq->op->redirect)
	//	{
	//		printf("FILE == %s\n", seq->op->redirect->file);
	//		seq->op->redirect = seq->op->redirect->next;
	//	}
		ft_free_b_seq(&seq);
//		ret != 1 ? ft_free_b_seq(&seq) : 0;
	}
	ft_lexer_del(&lex);
	ft_strdel(&line);
	return (EXIT_SUCCESS);
}

void        ft_print_logo(void)
{
	ft_putstr("\e[95m");
	ft_putendl (" _  _  ____      _		dewalter");
	ft_putendl ("| || ||___ \\ ___| |__		dzonda");
	ft_putendl ("| || |_ __) / __| '_ \\		gbarnay");
	ft_putendl ("|__   _/ __/\\__ \\ | | |		gmadec");
	ft_putendl ("   |_||_____|___/_| |_|		jecombe");
	ft_putstr("\e[39m");
	ft_putstr("\n");
}
static void			shell(void)
{
	e_prompt		prompt;
	char			*line;

	prompt = PROMPT;

	ft_print_logo();
	while (get_stdin(&line, &prompt) != -2)
	{
		if (line && (!(prompt = prelexer(line))))
			heart_of_101sh(line, 1);
		line = NULL;
	}
}

int			main(int ac, const char **av)
{
	if (!isatty(0))
		return (0);
	if (init_shell(ac, av))
		return (EXIT_FAILURE);
	signal_shell();
	shell();
	exit_shell();
	return (EXIT_SUCCESS);
}
