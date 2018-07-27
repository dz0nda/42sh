/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   main.c                                           .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: dzonda <marvin@le-101.fr>                  +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/07/18 03:53:04 by dzonda       #+#   ##    ##    #+#       */
/*   Updated: 2018/07/26 07:02:06 by gmadec      ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../include/lexer.h"
#include "../include/parsing.h"

#define cv ft_convert_token_to_string

void		ft_print_cc(t_cc *n_cc, int cmp)
{
	int				pcmp = cmp;
	int				i = 0;

	while (pcmp-- + 2)
		write(1, "\t", 1);
	if (n_cc->key != TOKEN)
		printf("NOT == %s KEY == %s OPEN == %d CLOSE == %d\n", cv(n_cc->not_operator), cv(n_cc->key), n_cc->open_key, n_cc->close_key);
	else
		printf("NOT == %s KEY == %s\n", cv(n_cc->not_operator), cv(n_cc->key));
	if (n_cc->arg)
	{
		if (n_cc->arg->not_operator != TOKEN)
		{
			pcmp = cmp;
			while (pcmp-- + 3)
				write(1, "\t", 1);
			printf("SC NOT ==  %s\n", cv(n_cc->arg->not_operator));
		}
		if (n_cc->arg->cmd)
			while (n_cc->arg->cmd[i])
			{
				pcmp = cmp;
				while (pcmp-- + 3)
					write(1, "\t", 1);
				printf("CC ARG %s\n", n_cc->arg->cmd[i++]);
			}
	}
}

void		ft_parcour_ccfuck(t_cc *n_cc)
{
	static int		cmp = 0;
	int				pcmp = cmp;

	ft_print_cc(n_cc, cmp);
	if (n_cc->next_in)
	{
		printf("NEXT->IN\n");
		cmp++;
		ft_parcour_ccfuck(n_cc->next_in);
	}
	if (n_cc->next_out)
	{
		printf("NEXT->OUT\n");
		if (n_cc->next_in)
			cmp--;
		ft_parcour_ccfuck(n_cc->next_out);
	}
	else
		printf("BBBBUUUUGGG\n");
}

void		ft_parcour_op(t_op *n_op)
{
	int		j = 0;

	printf("\t|--> OPERATEUR[0] == %s OPERATEUR[1] == %s\n", cv(n_op->token[0]), cv(n_op->token[1]));
	if (n_op->sc)
	{
		printf("\t\tSC NOT == %s\n", ft_convert_token_to_string(n_op->sc->not_operator));
		if (n_op->sc->cmd)
		{
			j = 0;
			printf("\t\tNEW CMD\n");
			while (n_op->sc->cmd[j])
			{
				printf("\t\tSC ARG == %s\n", n_op->sc->cmd[j]);
				j++;
			}
		}
	}
	else if (n_op->cc)
		ft_parcour_ccfuck(n_op->cc);
	else
	printf("\n");
	if (n_op->next)
		ft_parcour_op(n_op->next);
}

int			 main(int ac, char *argv[])
{
	t_lex	lex;
	t_seq	*b_seq;
	int		i = -1;

	(void)ac;
	lex = ft_lexer(argv[1]);
	while (lex.name[++i])
		printf(".%s. .%s.\n", lex.name[i], ft_convert_token_to_string(lex.token[i]));
	b_seq = ft_manage_parsing(lex);
	ft_putstr("\x1b[32m");
	printf("-------------- PARSING -------------\n");
	i = 0;
	while (b_seq)
	{
		printf("SEQUENCE NUMBER %d, LIST TERMINATOR == %s\n", i, ft_convert_token_to_string(b_seq->token));
		if (b_seq->op)
			ft_parcour_op(b_seq->op);
		i++;
		if (b_seq->next)
		printf("\n");
		b_seq = b_seq->next;
	}
	ft_putstr("\x1b[0m");
	return (0);
}
