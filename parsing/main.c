/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   main.c                                           .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: gmadec <marvin@le-101.fr>                  +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/06/22 05:29:28 by gmadec       #+#   ##    ##    #+#       */
/*   Updated: 2018/07/14 20:22:51 by gmadec      ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "./parsing.h"

int main(int ac, char **av)
{
	t_lex lex;
	t_seq *b_seq;
	t_sc *sc;
	t_cc *cc_in;
	t_cc *cc_out;
	t_op *op;
	int	i = -1;
	int	j;
	int	k;
	int	l;

	lex = ft_lexer(av[1]);
	ft_putstr("\x1b[34m");
	printf("--------LEXING----------\n");
	while (lex.name[++i])
	{
		printf("NAME == %s\n", lex.name[i]);
		printf("TOKEN == %u\n", lex.token[i]);
	}
	ft_putstr("\x1b[36m");
	printf("--------PARSING----------\n");
	b_seq = ft_manage_parsing(lex);
	ft_putstr("\x1b[32m");
	printf("--------------BOUCLE B_SEQ-------------\n");
	i = 0;
//	printf("POINT-VIRGULE == %u\n", b_seq->close);
//	if (b_seq->next)
//	printf("IF == %u\n", b_seq->op->cc->key);
//	printf("POINT-VIRGULE == %u\n", b_seq->op->cc->sc->token);
	while (b_seq)
	{
		printf("B_SEQUENCE NUMBER %d\n", i);
		j = 0;
		if (b_seq->op)
		{
			printf("B_SEQ->OP TROUVE\n");
			op = b_seq->op;
			while (op)
			{
				printf("%dB_SEQ->OP->OP == %u\n", j, op->op);
				if (op->sc)
					while (op->sc)
					{
						printf("OP->SC->ARG == %s\n", op->sc->arg);
						printf("OP->SC->TOKEN == %u\n", op->sc->token);
						op->sc = op->sc->next;
					}
				else if (op->cc)
				{
					k = 0;
					printf("KEY == %u\n", op->cc->key);
					cc_out = op->cc;
					sc = op->cc->sc;
					while (sc)
					{
						printf("SC->ARG == %s\n", sc->arg);
						sc = sc->next;
					}
					while (cc_out)
					{
						cc_in = cc_out;
						sc = cc_out->sc;
							while (sc)
							{
								printf("OUT->SC->ARG == %s\n", sc->arg);
								printf("OUT->SC->TOKEN == %u\n", sc->token);
								sc = sc->next;
							}
						l = 0;
						while (cc_in)
						{
							sc = cc_in->sc;
								while (sc)
								{
									printf("IN->SC->ARG == %s\n", sc->arg);
									sc = sc->next;
								}
							printf("%dCC_IN->NEXT_IN == %u\n", l, cc_in->key);
						cc_in = cc_in->next_in;
							l++;
						}
						k++;
						cc_out = cc_out->next_out;
					}
				}
				else
					printf("ERROR: NI SIMPLE NI COMPOSE CMD !\n");
				op = op->next;
				j++;
			}
		}
		else printf("B_SEQ->OP NON TROUVE\n");
		i++;
		b_seq = b_seq->next;
	}
	ft_putstr("\x1b[0m");
	return (0);
}
