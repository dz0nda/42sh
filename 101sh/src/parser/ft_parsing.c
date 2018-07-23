/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   ft_parsing.c                                     .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: gmadec <marvin@le-101.fr>                  +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/06/20 05:15:40 by gmadec       #+#   ##    ##    #+#       */
/*   Updated: 2018/07/20 11:36:54 by gmadec      ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../../include/parsing.h"

int			ft_tablen(char **tab)
{
	int		i;

	i = 0;
	while (tab[i])
		i++;
	return (i);
}

char		**ft_tabdup(char **tab)
{
	char		**ret;
	int			i;

	i = 0;
	ret = NULL;
	if (tab)
	{
		if (!(ret = malloc(sizeof(char**) * ft_tablen(tab) + 1)))
			return (NULL);
		while (tab[i])
		{
			ret[i] = tab[i];
			i++;
		}
		ret[i] = NULL;
	}
	return (ret);
}

int			ft_malloc_cmd(char ***cmd, char *new_arg)
{
	int		i;
	char	**tab;

	i = 0;
	if (!(*cmd))
	{
		if (!(tab = malloc(sizeof(char**) * 2)))
			return (1);
	}
	else
	{
		if (!(tab = malloc(sizeof(char**) * ft_tablen(*cmd) + 2)))
			return (1);
		while ((*cmd)[i])
		{
		printf("%s\n", ft_strdup((*cmd)[i]));
			tab[i] = ft_strdup((*cmd)[i]);
			i++;
		}
	}
	tab[i] = ft_strdup(new_arg);
	tab[i + 1] = NULL;
	*cmd = ft_tabdup(tab);
	return (0);
}

t_seq		*ft_malloc_seq(void)
{
	t_seq	*new;

	if (!(new = malloc(sizeof(t_seq))))
		return (NULL);
	new->token = TOKEN;
	new->op = NULL;
	new->next = NULL;
	new->prev = NULL;
	return (new);
}

t_op		*ft_malloc_op(void)
{
	t_op	*new;

	if (!(new = malloc(sizeof(t_op))))
		return (NULL);
	new->token = TOKEN;
	new->sc = NULL;
	new->cc = NULL;
	new->next = NULL;
	new->prev = NULL;
	return (new);
}

t_cc		*ft_malloc_cc(void)
{
	t_cc		*new;

	if (!(new = malloc(sizeof(t_cc))))
		return (NULL);
	new->key = TOKEN;
	new->not_operator = TOKEN;
	new->sc = NULL;
	new->open_key = 0;
	new->close_key = 0;
	new->next_in = NULL;
	new->next_out = NULL;
	new->parent = NULL;
	return (new);
}

t_sc		*ft_malloc_sc(void)
{
	t_sc		*new;

	if (!(new = malloc(sizeof(t_sc))))
		return (NULL);
	new->cmd = NULL;
	new->not_operator = TOKEN;
	new->close = 0;
	return (new);
}

int			ft_attrib_last_nseq(t_seq **b_seq, t_seq **n_seq)
{
//n_seq est egale au dernier maillon t_seq et si le token n'est pas NULL alors un nouveau maillon sera creer
	if (*b_seq)
	{
		*n_seq = *b_seq;
		while ((*n_seq)->next)
			*n_seq = (*n_seq)->next;
		if ((*n_seq)->token != TOKEN)
		{
			if (!((*n_seq)->next = ft_malloc_seq()))
				return (1);
			(*n_seq)->next->prev = *n_seq;
			(*n_seq) = (*n_seq)->next;
		}
	}
	else
	{
		if (!(*b_seq = ft_malloc_seq()))
			return (1);
		*n_seq = *b_seq;
	}
	return (0);
}

int			ft_manage_seq(t_seq **b_seq, e_token token)
{
//Attribut le token de fin de sequnce au dernier maillon dont le token  est egale a NULL
	t_seq			*n_seq;

	if (ft_attrib_last_nseq(&(*b_seq), &n_seq))
		return (1);
	n_seq->token = token;
	return (0);
}

int			ft_attrib_last_nop(t_seq **b_seq, t_op **n_op)
{
//n_op est egale au dernier maillon t_op et si le token n'est pas NULL alors un nouveau maillon sera creer
	t_seq			*n_seq;
	int				i = 0;

	if (ft_attrib_last_nseq(&(*b_seq), &n_seq))
		return (1);
	if (n_seq->op)
	{
		*n_op = n_seq->op;
		while ((*n_op)->next)
		{
			printf("N_OP->NEXT NUMBER %d\n", i);
			*n_op = (*n_op)->next;
		}
	}
	else
	{
		if (!(n_seq->op = ft_malloc_op()))
			return (1);
		*n_op = n_seq->op;
	}
	if ((*n_op)->token != TOKEN)
	{
		if (!((*n_op)->next = ft_malloc_op()))
			return (1);
		(*n_op)->next->prev = *n_op;
		(*n_op) = (*n_op)->next;
	}
	return (0);
}

int			ft_manage_op(t_seq **b_seq, e_token token)
{
//Attribut le token de redirection/pipe au dernier maillon dont le token  est egale a NULL
	t_op			*n_op;

	if (ft_attrib_last_nop(&(*b_seq), &n_op))
		return (1);
	n_op->token = token;
	return (0);
}

int			ft_attrib_last_sc_in_cc(t_cc **n_cc)
{
//ATTRIBUT A n_cc le dernier maillon pour une simple commande, en creer un si la commande est open et retourne une erreur de syntaxe si close_key est actif
	if ((*n_cc)->next_out)
	{
		if (ft_attrib_last_sc_in_cc(&(*n_cc)->next_out))
			return (1);
	}
	else if ((*n_cc)->next_in)
	{
		if (ft_attrib_last_sc_in_cc(&(*n_cc)->next_in))
			return (1);
	}
	else if ((*n_cc)->close_key)
	{
		printf("101SH: syntax error near unexpected token `SC IN CC'\n");
		return (1);
	}
	else if (!(*n_cc)->sc)
	{
		printf("3\n");
		if (!((*n_cc)->sc = ft_malloc_sc()))
		{
			return (1);
		}
	}
	else if ((*n_cc)->sc->close)
	{
	// A definir selon Jecombe
		printf("Jecombe apparait STP\n");
	}
	return (0);
}

int			ft_manage_word(t_seq **b_seq, char *name)
{
	t_op			*n_op;
	t_cc			*n_cc;
	t_sc			*n_sc;

	if (ft_attrib_last_nop(&(*b_seq), &n_op))
		return (1);
	if (n_op->cc)
	{
		printf("CC == %s\n", name);
		n_cc = n_op->cc;
		if (ft_attrib_last_sc_in_cc(&n_cc))
			return (1);
		if (ft_malloc_cmd(&n_cc->sc->cmd, name))
			return (1);
		printf("(*b_seq)->op->cc->sc->cmd[0] == %s\n", (*b_seq)->op->cc->sc->cmd[0]);
	}
	else
	{
	printf("SC == %s\n", name);
		if (!n_op->sc)
			if (!(n_op->sc = ft_malloc_sc()))
				return (1);
		if (ft_malloc_cmd(&n_op->sc->cmd, name))
			return (1);
	}
	return (0);
}

int			ft_attrib_last_key_in_cc(t_cc **n_cc)
{
	if ((*n_cc)->next_out)
	{
		if (!(ft_attrib_last_key_in_cc(&(*n_cc)->next_out)))
			return (1);
	}
	else if ((*n_cc)->next_in)
	{
		if (!(ft_attrib_last_key_in_cc(&(*n_cc)->next_in)))
			return (1);
	}
	else if ((*n_cc)->key != TOKEN && !(*n_cc)->sc)
	{
		printf("bash: syntax error near unexpected token `;'\n");
		return (1);
	}
	else if ((*n_cc)->open_key && !(*n_cc)->close_key)
	{
		if (!((*n_cc)->next_in = ft_malloc_cc()))
			return (1);
		(*n_cc)->next_in->parent = *n_cc;
		*n_cc = (*n_cc)->next_in;
	}
	else if ((*n_cc)->close_key || (*n_cc)->sc)
	{
		if (!((*n_cc)->next_out = ft_malloc_cc()))
			return (1);
		(*n_cc)->next_out->parent = *n_cc;
		*n_cc = (*n_cc)->next_out;
	}
	return (0);
}

int			ft_entry_reserved(t_seq **b_seq, char *name, e_token token)
{
	t_seq			*n_seq;
	t_op			*n_op;
	t_cc			*n_cc;

	if (ft_attrib_last_nop(&(*b_seq), &n_op))
		return (1);
	if (n_op->sc)
	{
		printf("VU COMME UN ARGUMENT DE LA SIMPLE COMMANDE\n");
		if (ft_malloc_cmd(&n_op->sc->cmd, name))
			return (1);
	}
	else
	{
		printf("CREATION/CONTINUITE DE LA COMPOSED COMMANDE\n");
		if (!(n_op->cc))
			if (!(n_op->cc = ft_malloc_cc()))
				return (1);
		if (n_op->cc)
			printf("N_OP->CC CREATED\n");
		n_cc = n_op->cc;
		if (ft_attrib_last_key_in_cc(&n_cc))
			return (1);
		if (n_cc->key != TOKEN && n_cc->sc)
		{
			printf("ARGUMENT DU TOKEN DANS SC, TOKEN = SC\n");
			ft_malloc_cmd(&n_cc->sc->cmd, name);
		}
		else
		{
			printf("NEW RESERVED ENTRY\n");
			n_cc->key = token;
		}
	}
	return (0);
}

int			ft_complete_entry_reserved(t_seq **b_seq, char *name, e_token token)
{
	
	return (0);
}

int			ft_attribute_token(t_seq **b_seq, char *name, e_token token)
{
	if (token == SEMI || token == AND)
	{
		printf("NEW/END SEQUENCE\n");
		if (ft_manage_seq(&(*b_seq), token))
			return (1);
	}
	else if (token >= AND_IF && token <= DLESSDASH && token != NOT)
	{
		printf("CONTROL OPERATOR\n");
		if (ft_manage_op(&(*b_seq), token))
			return (1);
	}
	else if (token >= IF && token <= CASE)
	{
		printf("ENTRY RESERVED\n");
		if (ft_entry_reserved(&(*b_seq), name, token))
			return (1);
	}
	else if (token == THEN || token == IN || token == DO)
	{
		printf("COMPLETE ENTRY RESERVED\n");
		if (ft_complete_entry_reserved(&(*b_seq), name, token))
			return (1);
	}
	else if (token >= ESAC && token <= DONE)
	{
		printf("OPEN_KEY RESERVED\n");
	}
	else if (token == ELIF && token == ELSE)
	{
		printf("CLOSE_KEY RESERVED\n");
	}
	else if (token == NOT)
	{
		printf("NOT_OPERATOR\n");
	}
	else
	{
		printf("TOKEN\n");
		if (ft_manage_word(&(*b_seq), name))
			return (1);
	}
	return (0);
}

t_seq		*ft_manage_parsing(t_lex lex)
{
	int				i;
	t_seq			*b_seq;

	b_seq = NULL;
	i = -1;
	while (lex.name[++i])
	{
		printf("------------- I == %d ------------\n", i);
		if (ft_attribute_token(&b_seq, lex.name[i], lex.token[i]))
		{
			printf("AALERTTT GEEENEEERALLLL\n");
			return (NULL);
		}
//			printf("b_seq->op->cc->key == %u\n", b_seq->op->cc->key);
	}
	return (b_seq);
}
