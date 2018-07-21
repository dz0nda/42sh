/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   main.c                                           .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: dzonda <marvin@le-101.fr>                  +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/07/18 03:53:04 by dzonda       #+#   ##    ##    #+#       */
/*   Updated: 2018/07/20 08:58:17 by gmadec      ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../include/lexer.h"
#include "../include/parsing.h"

int main(int ac, char *argv[])
{
	t_lex	lex;
	t_seq	*b_seq;
	t_cc	*n_cc;
	t_cc	*n_cc_in;
	int		cc0 = 2;
	int		cc1 = 2;
	int		i = -1;
	int		j = 0;

	(void)ac;
	lex = ft_lexer(argv[1]);
	while (lex.name[++i])
	{
		if (!ft_strcmp(lex.name[i], "if"))
			lex.token[i] = IF;
		if (!ft_strcmp(lex.name[i], "fi"))
			lex.token[i] = FI;
		if (!ft_strcmp(lex.name[i], "then"))
			lex.token[i] = THEN;
		if (!ft_strcmp(lex.name[i], "ELIF"))
			lex.token[i] = ELIF;
		printf(".%s. .%s.\n", lex.name[i], ft_convert_token_to_string(lex.token[i]));
	}
	b_seq = ft_manage_parsing(lex);
	ft_putstr("\x1b[32m");
	printf("-------------- PARSING -------------\n");
	i = 0;
	while (b_seq)
	{
		printf("SEQUENCE NUMBER %d, LIST TERMINATOR == %s\n", i, ft_convert_token_to_string(b_seq->token));
		while (b_seq->op)
		{
			printf("\t|--> OPERATEUR == %s\n", ft_convert_token_to_string(b_seq->op->token));
			if (b_seq->op->sc)
			{
				if (b_seq->op->sc->cmd)
				{
					j = 0;
					if (b_seq->op->sc->cmd[j])
					{
						while (b_seq->op->sc->cmd[j])
						{
							printf("\t\tSC ARG == %s NOT == %s\n", b_seq->op->sc->cmd[j], ft_convert_token_to_string(b_seq->op->sc->not_operator));
							j++;
						}
					}
					else
						printf("\t\tSC ARG == (NULL) NOT == %s\n", ft_convert_token_to_string(b_seq->op->sc->not_operator));
				}
			}
			else if (b_seq->op->cc)
			{
				n_cc = b_seq->op->cc;
				cc0 = 2;
				while (n_cc)
				{
					n_cc_in = n_cc;
					while (n_cc_in)
					{
						cc1 = cc0;
						while (cc0--)
							printf("\t");
						printf("CC TOKEN == %s NOT == %s OPEN == %d CLOSE == %d\n", ft_convert_token_to_string(n_cc_in->key), ft_convert_token_to_string(n_cc_in->not_operator), n_cc_in->open_key, n_cc_in->close_key);
						if (n_cc_in->sc)
						{
							j = -1;
							if (n_cc_in->sc->cmd)
							{
								while (n_cc_in->sc->cmd[++j])
								{
									cc1 = cc0;
									while (cc0-- + 1)
										printf("\t");
									printf("CC ARG == %s NOT == %s\n", n_cc_in->sc->cmd[j], ft_convert_token_to_string(n_cc_in->not_operator));
								}
							}
							else
								printf("CC ARG == (NULL) NOT == %s\n", ft_convert_token_to_string(n_cc_in->not_operator));
						}
						n_cc_in = n_cc_in->next_in;
					}
					n_cc = n_cc->next_out;
					cc0++;
				}
			}
			printf("\n");
			b_seq->op = b_seq->op->next;
		}
		i++;
		printf("\n\n");
		b_seq = b_seq->next;
	}
	ft_putstr("\x1b[0m");
	return (0);
}
